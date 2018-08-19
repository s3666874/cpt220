/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "tile_list.h"

/******************************************************************************
 * the tile list module manages the tile list which might behave like a tile map
 * (mapping between a letter and a score) or it might be a list which that can
 * be added to or deleted from (such as a tile deck or tile hand). You are
 *required to create the functions for this list.
 *****************************************************************************/

/**
 * global error score
 **/
const struct score_count error_score = { { EOF, EOF }, EOF };

/**
 * initialises the tile list to hold the number of tiles specified.
 **/
struct tile_list* tl_init(struct tile_list* newmap, int num_tiles)
{
        assert(num_tiles > 0);
        /* allocate space for the tiles */
        newmap->tiles = (struct tile*)malloc(sizeof(struct tile) * num_tiles);
        if (!newmap->tiles)
        {
                return NULL;
        }
        /* initialise the tiles to 0 and the count to 0 */
        memset(newmap->tiles, 0, sizeof(struct tile) * num_tiles);
        newmap->num_tiles = 0;
        newmap->total_tiles = num_tiles;
        return newmap;
}

/**
 * in some places, the tile list pointer needs to be malloced and so we
 * allocate space for the list structure itself here
 **/
struct tile_list* tl_make(int num_tiles)
{
        struct tile_list* newlist;
        /* allocate space for the list structure */
        newlist = (struct tile_list*)malloc(sizeof(struct tile_list));
        if (!newlist)
        {
                error_print("malloc: %s\n", strerror(errno));
                return NULL;
        }
        /* init work already implemented in tl_init() */
        if (!tl_init(newlist, num_tiles))
        {
                return NULL;
        }
        return newlist;
}

/**
 * performs a linear search to file the letter specified. Your implementation
 * could be a lot more efficient than this.
 **/
static struct tile* find_letter(const struct tile_list* themap,
                                const char letter)
{
        int count;
        for (count = 0; count < themap->num_tiles; ++count)
        {
                if (themap->tiles[count].letter == letter)
                {
                        return &themap->tiles[count];
                }
        }
        return NULL;
}

/**
 * adds a tile to the tile list. Please note that this function allows for
 * duplicate data to be added, such as the same tile being added twice.
 **/
BOOLEAN tl_add(struct tile_list* tilelist, const struct tile atile)
{
        if (tilelist->num_tiles >= tilelist->total_tiles)
        {
                return FALSE;
        }
        tilelist->tiles[tilelist->num_tiles++] = atile;
        return TRUE;
}

/**
 * searches the tile list for the tile that needs to be added and if it
 * already exists, just change the score to be what was passed in. If it does
 * not exist, add it at the end.
 **/
BOOLEAN tl_set(struct tile_list* map, const struct tile score)
{
        /* search for the tile */
        struct tile* old_val = find_letter(map, score.letter);
        /* if found, update the score for that tile */
        if (old_val != NULL)
        {
                old_val->score = score.score;
                return TRUE;
        }
        /* test that there is space for this tile */
        if (map->num_tiles == map->total_tiles)
        {
                return FALSE;
        }
        /* if there is space, add it at the end */
        map->tiles[map->num_tiles++] = score;
        return TRUE;
}

/**
 * gets the score for the letter specified
 **/
int tl_get(struct tile_list* map, const char letter)
{
        /* find the tile */
        struct tile* score = find_letter(map, letter);
        /* if it is missing, return -1 */
        if (score == NULL)
        {
                return EOF;
        }
        /* otherwise return the score */
        return score->score;
}

/**
 * private (as not in the header) enumeration that represents that parts of
 * a score for use with the tokenisation and processing of the tilestring
 * below
 **/
enum delimcount
{
        DC_LETTER,
        DC_NUMBER,
        DC_COUNT,
        DC_INVALID
};

/**
 * creates a tile and count of how many of that tile should exist in the system
 **/
struct score_count new_score_count(const char tilestring[])
{
        const char* delim = ",";
        enum delimcount curdelim;
        struct score_count thescore = { { EOF, EOF }, EOF };
        /* tokenize the tilestring */
        char** parts = tokenize(tilestring, delim, NUM_TILE_TOKENS);
        char letter;

        /* iterate over the tokens */
        for (curdelim = 0; curdelim < DC_INVALID; ++curdelim)
        {
                switch (curdelim)
                {
                        case DC_LETTER:
                                /* store the letter from the string */
                                if (strlen(parts[DC_LETTER]) != ONECHAR)
                                {
                                        error_print("token too long: %s\n",
                                                    parts[DC_LETTER]);
                                        free_tokens(parts, NUM_TILE_TOKENS);
                                        return error_score;
                                }
                                letter = *parts[DC_LETTER];
                                /* validate the the tile is an upper case letter
                                 * or a space (blank) */
                                if ((!isalpha(letter) || !isupper(letter)) &&
                                    letter != SPACE)
                                {
                                        return error_score;
                                }
                                thescore.tile.letter = letter;
                                break;
                        case DC_NUMBER:
                                /* convert to int the score for this tile */
                                if (!strtoint(parts[DC_NUMBER],
                                              &thescore.tile.score))
                                {
                                        free_tokens(parts, NUM_TILE_TOKENS);
                                        return error_score;
                                }
                                break;
                        case DC_COUNT:

                                /* extract the count of how many of this tile
                                 * should exist in the system
                                 */
                                if (!strtoint(parts[DC_COUNT], &thescore.count))
                                {
                                        free_tokens(parts, NUM_TILE_TOKENS);
                                        return error_score;
                                }
                                break;
                        default:
                                /* any other value is an error, so we handle
                                 * them */
                                error_print("Error: too many delimiters\n");
                                free_tokens(parts, NUM_TILE_TOKENS);
                                return error_score;
                }
        }
        /* free the tokens as we are done with them */
        free_tokens(parts, NUM_TILE_TOKENS);
        return thescore;
}

/**
 * convenience function for swapping tiles for shuffling / sorting
 **/
static void swap_tiles(struct tile* first, struct tile* second)
{
        struct tile temp = *first;
        *first = *first;
        *first = *second;
        *second = temp;
}

/**
 * randomises the tile list specified. This is designed to be used with
 * the tile deck
 **/
void tl_shuffle(struct tile_list* tilelist)
{
        int count;
        /* iterate through the first half of the tile list and
         * randomly swap with another tile in the tile list */
        for (count = 0; count < tilelist->num_tiles / 2; ++count)
        {
                int newloc = rand() % tilelist->num_tiles;
                if (newloc != count)
                {
                        swap_tiles(tilelist->tiles + count,
                                   tilelist->tiles + newloc);
                }
        }
}

/**
 * removes the tile at the specified index and if retval is not NULL then
 * store the tile there.
 **/
BOOLEAN tl_remove(struct tile_list* tilelist, struct tile* retval, int index)
{
        int count;
        /* check that the specified index is within the range of a valid index
         */
        if (index >= tilelist->num_tiles || index < 0)
        {
                return FALSE;
        }
        /* if retval is not NULL, store the value into that memory */
        if (retval)
        {
                *retval = tilelist->tiles[index];
        }
        /* shuffle all the elements forward */
        for (count = index; count < tilelist->num_tiles - 1; ++count)
        {
                tilelist->tiles[count] = tilelist->tiles[count + 1];
        }
        /* reducce the count of tiles */
        tilelist->num_tiles--;
        return TRUE;
}

/**
 * performs a linear search over the tile list and if it is found, return the
 * index of the location where the element is located and if it is not found,
 * return -1
 **/
int tl_find(struct tile_list* tilelist, int needle)
{
        int count;
        for (count = 0; count < tilelist->num_tiles; ++count)
        {
                if (tilelist->tiles[count].letter == needle)
                {
                        return count;
                }
        }
        return EOF;
}

/**
 * takes the top tile from the fulllist and adds it to the hand until the hand
 * is full.
 **/
BOOLEAN tl_fill(struct tile_list* fulllist, struct tile_list* hand)
{
        /* how far is the hand from being full ? */
        int num_needed = hand->total_tiles - hand->num_tiles;
        int num_dealt;
        /* delete each needed tile from the full list and add to the hand */
        for (num_dealt = 0; num_dealt < num_needed; ++num_dealt)
        {
                struct tile copy;
                if (fulllist->num_tiles == 0)
                {
                        return FALSE;
                }
                if (tl_remove(fulllist, &copy, 0))
                {
                        tl_add(hand, copy);
                }
        }
        return TRUE;
}

/**
 * counts how many blank tiles are in a tile list (normally a player's hand
 **/
int tl_count_blanks(const struct tile_list* list)
{
        int num_blanks = 0;
        int count;
        /* iterate over the tile list. If this is a blank add one to the blank
         * count */
        for (count = 0; count < list->num_tiles; ++count)
        {
                if (list->tiles[count].letter == SPACE)
                {
                        num_blanks++;
                }
        }
        return num_blanks;
}

/**
 * frees the tiles array for this tile list
 **/
void tl_free(struct tile_list* tilelist)
{
        free(tilelist->tiles);
}
