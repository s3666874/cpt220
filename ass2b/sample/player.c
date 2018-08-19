/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "player.h"
#include "game.h"

/******************************************************************************
 * the player module manages the player struct. There are required functions
 * provided such as new_players(), init_player(), take_turn(),
 * shuffle_players(), player_sort() and some comparison functions for players.
 * You should add additional functions for managing of players if you need to.
 *****************************************************************************/

/**
 * allocates a players array of the size specified. It allocates a random color
 * for each player and then calls init_player() on each player, passing in the
 * required arguments
 **/
struct player* new_players(int num_players, struct game* thegame,
                           enum input_result* status)
{
        int count;
        /* enum created for this function so we can randomly select colours
         * for each player */
        struct colour_allocation
        {
                BOOLEAN allocated;
                enum color color;
        } colors[] = { { FALSE, C_RED },
                       { FALSE, C_GREEN },
                       { FALSE, C_YELLOW },
                       { FALSE, C_BLUE },
                       { FALSE, C_MAGENTA },
                       { FALSE, C_CYAN } };
        /* create the players array */
        thegame->players =
            (struct player*)malloc(sizeof(struct player) * num_players);
        if (!thegame->players)
        {
                error_print("malloc: %s\n", strerror(errno));
                return NULL;
        }

        /* initialise each player */
        for (count = 0; count < num_players; ++count)
        {
                enum color selected_colour = C_INVALID;
                /* select random colors - roll a dice until the dice gives us
                 * a color that has not been selected for another player */
                do
                {
                        int colselect = rand() % MAX_PLAYERS;
                        if (!colors[colselect].allocated)
                        {
                                colors[colselect].allocated = TRUE;
                                selected_colour = colors[colselect].color;
                        }
                } while (selected_colour == C_INVALID);
                /* initialise each player and if it fails, just return NULL
                 * from here
                 */
                /* status is returned via a parameter so we know when we
                 * returned whether io succeded. */
                init_player(&thegame->players[count], count + 1,
                            selected_colour, thegame);
        }
        thegame->num_players = num_players;
        return thegame->players;
}

/**
 * Initialise the data for a player. this includes prompting for the name
 * of a player, and filling the starting hand for the using from the tile
 * deck, as well as setting the color and the game pointer and set the score to
 * 0.
 **/
enum input_result init_player(struct player* curplayer, int playernum,
                              enum color color, struct game* thegame)
{
        char name[NAMELEN + EXTRA_CHARS];
        enum input_result result;
        char prompt[LINE_LEN + 1];

        /* initialise some struct members */
        curplayer->thegame = thegame;
        curplayer->color = color;
        curplayer->score = 0;
        /* prompt for and read the name of a player */
        sprintf(prompt, "Please enter the name of player %d: ", playernum);
        while (result = kbd_get_string(prompt, name, NAMELEN + EXTRA_CHARS),
               result == IR_FAILURE)
                ;
        if (result == IR_RTM)
        {
                return IR_RTM;
        }
        strcpy(curplayer->name, name);
        /* initialise and load the hand for the player */
        if (!tl_init(&curplayer->hand, HANDSIZE))
        {
                return IR_FAILURE;
        }
        if (!tl_fill(thegame->tiledeck, &curplayer->hand))
        {
                return IR_FAILURE;
        }
        return IR_SUCCESS;
}

/**
 * This is the function that implements each player turn. Firstly, the word to
 * player is prompted for - the word cannot be any longer than the width of
 * the board, of course. Display the board, prompt for the coordinates of
 * the move in the form of x:y:d where x and y are the starting coordinates of
 * the word and d is the dimension of the word - either h or v (case
 * insensitive). It must be apparent from the prompt the name and color of the
 * player who is taking the current turn.
 *
 * Next, use the functions implemented in the rules module to validate
 * and apply the changes to the board.
 **/
enum input_result take_turn(struct player* curplayer, BOOLEAN isfirst)
{
        /* you'll need to allocate and free this on every turne */
        /*char* word;*/
        return IR_SUCCESS;
}

/**
 * shuffle the player so they are ordered in a different order to the order
 * they were entered as part of initialisation
 **/
void shuffle_players(struct player players[], int num_players)
{
        int count;
        for (count = 0; count < num_players; ++count)
        {
                /* swap the players if their position is not the same (otherwise
                 * there's no point) */
                int newpos = rand() % num_players;
                if (newpos != count)
                {
                        struct player temp = players[newpos];
                        players[newpos] = players[count];
                        players[count] = temp;
                }
        }
}

/**
 * sorts the players in the player list in some order
 **/
void player_sort(struct player* players, int num_players,
                 int (*cmp)(const struct player*, const struct player*))
{
}

/**
 * when finalising the scores, players are sorted by score from top to bottom
 * to print out at the end of a game
 **/
int player_cmp(const struct player* first, const struct player* second)
{
        return EOF;
}

/**
 * in the random shuffle, we randomly "sort" elements according to the result
 * returned from rand()
 **/
int player_shuffle_cmp(const struct player* first, const struct player* second)
{
        return EOF;
}
