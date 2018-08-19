/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "io.h"
#include "tile_list.h"
#include "game.h"

/******************************************************************************
 * the io module should contain the logic for all io functions, both for
 * loading from a file and output to the screen / input from the keyboard. Some
 * functions have been provided here to give you a start.
 *****************************************************************************/

/**
 * array that contains the color strings for each color available in the
 * game
 **/
const char* color_strings[] = { COLOR_RED,   COLOR_GREEN,   COLOR_YELLOW,
                                COLOR_BLUE,  COLOR_MAGENTA, COLOR_CYAN,
                                COLOR_RESET, NULL };

/**
 *  clears the buffer when there is a buffer overflow of input
 **/
void read_rest_of_line(void)
{
        int ch;
        while (ch = getc(stdin), ch != '\n' && ch != EOF)
                ;
        clearerr(stdin);
}

/**
 * tests whether the string passed in ends with a newline character
 **/
static BOOLEAN has_nl(const char line[])
{
        return line[strlen(line) - 1] == '\n';
}

/**
 * removes the last char from the string - often the newline character
 **/
static void remove_nl(char line[])
{
        line[strlen(line) - 1] = 0;
}

/**
 * loads the word list (dictionary of allowed words) into a linked list of
 * words. You should open the file then read in each line into a node in
 * the word list. Don't forget to validate each action and remove the
 * newline characters as you load the data in.
 **/
BOOLEAN load_word_list(const char fname[], struct word_list* wordlist)
{
        FILE* reader;
        char line[MAX_WORD_LEN + EXTRA_CHARS];
        int lineno = 0;

        /* initialise the word list to a safe state */
        wl_init(wordlist);
        /* open the file */
        reader = fopen(fname, "r");
        if (!reader)
        {
                error_print("%s: %s\n", "fopen", strerror(errno));
                return FALSE;
        }
        /* read each line */
        while (!feof(reader))
        {
                ++lineno;
                if (fgets(line, MAX_WORD_LEN + EXTRA_CHARS, reader) == NULL)
                {
                        /* check for errors */
                        if (!feof(reader))
                        {
                                error_print("Error: %s\n", strerror(errno));
                        }
                        break;
                }
                /* check for lines longer than expected */
                if (!has_nl(line))
                {
                        error_print("Error: line is too long: %d\n", lineno);
                        error_print("%s\n", line);
                        return FALSE;
                }
                /* trim off the newline char */
                remove_nl(line);
                /* add the line to the word list */
                if (!wl_add(wordlist, strtoupper(line)))
                {
                        return FALSE;
                }
        }
        return TRUE;
}

/**
 * loads the tiles and their values as well as the count of how many
 * should be created
 **/
BOOLEAN load_scores(const char fname[], struct tile_list** lettermap,
                    struct tile_list** fulllist)
{
        FILE* reader;
        char line[SCORE_LEN + EXTRA_CHARS];
        int lineno = 0;
        int tilecount;

        /* allocate space for the tile map which will be looked up for the
         * scores */
        /* +1 tile is for the blank */
        *lettermap = tl_make(AL_NUM_LETTERS + 1);
        if (!*lettermap)
        {
                return FALSE;
        }
        /* the full list is all tiles in the game - according to the rules that
         * is 100 tiles including 2 blank tiles */
        *fulllist = tl_make(NUM_LETTERS);
        if (!*fulllist)
        {
                return FALSE;
        }
        /* open the tiles file */
        reader = fopen(fname, "r");
        if (!reader)
        {
                error_print("Error: %s\n", strerror(errno));
                return FALSE;
        }
        /* read each line from the file */
        while (!feof(reader))
        {
                struct score_count newscore;
                ++lineno;
                /* read in each line and if there is an error and it's not
                 * the end of the file, display an error and exit
                 */
                if (fgets(line, SCORE_LEN + EXTRA_CHARS, reader) == NULL)
                {
                        if (!feof(reader))
                        {
                                error_print("Error: %s\n", strerror(errno));
                        }
                        break;
                }
                /* check if the line ends in a newline char - if not, there
                 * is buffer overflow
                 */
                if (!has_nl(line))
                {
                        error_print("Error: line %d is too long in %s.\n",
                                    lineno, fname);
                }
                /* delete the last char which is a newline char */
                remove_nl(line);
                /* create a score based on the line */
                newscore = new_score_count(line);
                if (newscore.count == error_score.count)
                {
                        error_print(
                            "Error: there was an invalid tile read in.\n");
                        return FALSE;
                }
                /* add the tile to the tile map */
                if (!tl_set(*lettermap, newscore.tile))
                {
                        error_print("Error: there are too many tiles "
                                    "to be read in.\n");
                        return FALSE;
                }
                /* also add this tile to the tile deck as many times as
                 * specified by the tile count element
                 */
                for (tilecount = 0; tilecount < newscore.count; ++tilecount)
                {
                        if (!tl_add(*fulllist, newscore.tile))
                        {
                                error_print("Error: tl_add failed!\n");
                                return FALSE;
                        }
                }
        }
        /* shuffle the tiles */
        tl_shuffle(*fulllist);
        return TRUE;
}

/**
 * displays the board with its current contents. As the cells of the board
 * contain both a char and a color, you need to display the char in the color
 * indicated by the color element of the cell. You must use the provided
 * color_strings array to retrieve the color codes to display the strings
 * in the right color.
 **/
void display_board(const struct board* theboard)
{
}

/**
 * display the hand in a table. Please see the sample executable / the
 * assignment specification for the expected format of this output
 **/
void print_hand(struct tile_list* curhand)
{
}

/**
 * prints out a prompt and reads in a string of at most linelen chars plus the
 *\n\0 chars appended by fgets.
 * You don't have to implement this but it was part of my solution.
 * */
enum input_result kbd_get_string(const char prompt[], char line[], int linelen)
{
        return IR_FAILURE;
}

/**
 * prints out text to stdout
 **/
int normal_print(const char format[], ...)
{
        int charcount;
        va_list arglist;
        /* extract the argument list */
        va_start(arglist, format);
        /* send to output */
        charcount = vprintf(format, arglist);
        /* all done */
        va_end(arglist);
        return charcount;
}

/**
 * prints output to stderr
 **/
int error_print(const char format[], ...)
{
        va_list arglist;
        int charcount = 0;
        /* grab the arguments */
        va_start(arglist, format);
        /* send them to stderr */
        charcount += vfprintf(stderr, format, arglist);
        /* all done */
        va_end(arglist);
        return charcount;
}

/**
 * prints out the final scores for each player to stdout, sorted from highest
 * scoring player to lowest scoring player
 **/
void print_finscores(struct game* thegame)
{
}
