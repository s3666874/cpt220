/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "io.h"
#include "tile_list.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

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

char* cleanString(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}

enum input_result get_string_from_keyboard(const char prompt[], char *output, int len)
{
        char *str = malloc((len+1) * sizeof(char));

        printf("%s", prompt);
        
        if (fgets(str, (len+1), stdin) == NULL)
                return IR_RTM;

        if (strlen(str) == 1 && str[0] == '\n')
                return IR_RTM;

        if (str[strlen(str) - 1] != '\n')
                read_rest_of_line();

        strcpy(output, cleanString(str));

        free(str);
        return IR_SUCCESS;
}

enum input_result get_int_from_keyboard(const char prompt[], int *output, int len)
{
        char *ptr;
        long ret;
        int final;
        char *str = malloc((len+1) * sizeof(char));
        enum input_result result;

        result = get_string_from_keyboard(prompt, str, len);

        if (result == IR_SUCCESS)
        {
                ret = strtol(str, &ptr, 10);

                if (strlen(ptr) > 0)
                {
                        free(str);
                        return IR_FAILURE;
                }
                else
                {
                        if (ret >= INT_MIN && ret <= INT_MAX)
                        {
                                final = ret;
                                *output = final;

                                free(str);
                                return IR_SUCCESS;
                        }
                        else
                        {
                                free(str);
                                return IR_FAILURE;
                        }
                }
        }
        else
        {
                free(str);
                return result;
        }
}


char * upper(char * temp) {
        char * name = temp;
        char *s = name;

        while (*s)
        {
                *s = toupper((unsigned char) *s);
                s++;
        }

        return name;
}

long int getint(char* str)
{
        char *ptr;
        long ret;

        ret = strtol(str, &ptr, 10);

        return ret;
}


/**
 * loads the word list (dictionary of allowed words) into a linked list of
 * words. You should open the file then read in each line into a node in
 * the word list. Don't forget to validate each action and remove the
 * newline characters as you load the data in. Also, don't forget to validate
 * that the whole word has been read and remove the newline at the end of
 * each line.
 **/
BOOLEAN load_word_list(const char fname[], struct word_list* wordlist)
{
        char str[MAX_WORD_LEN+1];
        char *copy;

        FILE *file;

        file = fopen(fname, "r");

        if (file) {
                printf("Please wait while we load the dictionary ...\n");

                while (fgets(str, (MAX_WORD_LEN+1), file))
                {
                        copy = malloc(strlen(str)+1);
                        strcpy(copy, str);
                        word_list_add(wordlist, upper(cleanString(copy)));
                        /*free(copy);*/
                }

                /*free(copy);*/
                fclose(file);
        }
        else
        {
                printf("Bad filename\n");
                return FALSE;
        }

        return TRUE;
}

/**
 * loads the tiles and their values as well as the count of how many
 * should be created
 **/
BOOLEAN load_scores(const char fname[], struct tile_list* lettermap,
                    struct tile_list* fulllist)
{
        int i,c,t=0,t1=0;
        char *copy;
        char str[8];
        char *token;
        char letter;
        int letter_count;
        int letter_score;
        const char s[2] = ",";

        struct tile *tmp = malloc(27 * sizeof(struct tile));
        struct tile *temp = malloc(100 * sizeof(struct tile));

        FILE *file;

        file = fopen(fname, "r");

        if (file) {
                while (fgets(str, 8, file))
                {
                        copy = malloc(strlen(str)+1);
                        strcpy(copy ,str);

                        /*printf("%s\t", cleanString(copy));*/

                        token = strtok(copy, s);
                        c=1;

                        while(token != NULL)
                        {

                                if (c == 1)
                                {
                                        letter = *token;
                                }
                                else if (c == 2)
                                {
                                        letter_score = getint(token);
                                }
                                else
                                {
                                        letter_count = getint(token);

                                        for (i=0; i<letter_count; i++)
                                        {
                                                temp[t] = new_tile(letter, letter_score);
                                                /*printf("[%c][%d] ", letter, t);*/
                                                t++;
                                        }

                                        tmp[t1] = new_tile(letter, letter_score);
                                        t1++;
                                }

                                token = strtok(NULL, s);
                                c++;
                        }

                        /*printf("\n");*/
                        free(copy);
                }

                fclose(file);
        }
        else
        {
                return FALSE;
        }

        /*print_tiles(temp, 100);*/
        shuffle_tiles(temp, 100);
        /*print_tiles(temp, 100);*/

        /* Setting up lettermap */
        lettermap->num_tiles = 0;
        lettermap->total_tiles = 27;

        /* Setting up the fulllist */
        fulllist->num_tiles = 0;
        fulllist->total_tiles = 100;


        /**************************** Option 1 - Only one that works ****************************/
        lettermap->tiles = tmp;
        fulllist->tiles = temp;


        /**************************** Option 2 - We get funny characters ****************************/
        /*lettermap->tiles = tmp;
        fulllist->tiles = temp;

        free(tmp);
        free(temp);*/

        /**************************** Option 3 - Segmentation fault ****************************/
        /*memcpy(lettermap->tiles, tmp, 27 * sizeof(struct tile));
        memcpy(fulllist->tiles, temp, 100 * sizeof(struct tile));

        free(tmp);
        free(temp);*/


        /*print_tiles(fulllist->tiles, 100);*/

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
        int i,j;

        for (i=0; i<theboard->boardsize+1; i++)
        {
                if (i == 0)
                {
                        printf("    |");
                }
                else
                {
                        printf("  %d |", i);
                }

                for (j=0; j<theboard->boardsize; j++)
                {
                        if (i == 0)
                        {
                                printf("  %d |", j+1);
                        }
                        else
                        {
                                printf("    |");
                        }

                }

                printf("\n");

                PUTLINE('-', 5 * (theboard->boardsize + 1));
        }

        printf("\n");
}

/**
 * display the hand in a table. Please see the sample executable / the
 * assignment specification for the expected format of this output
 **/
void print_hand(struct tile_list* curhand)
{
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
