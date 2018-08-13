/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "io.h"
#include <limits.h>

/**
 * this file has the implementation functions for input / output. All ouput
 * should happen from this module so that it would be easy to rewrite output to
 * another format, such as a gui application.
 **/

/**
 * The values for the various game tokens as strings. These are in the same
 * order as the cell enumeration. In other works the 0th element is for empty,
 * the first is red and the second is white. The NULL pointer on the end is for
 * the C_INVALID constant
 **/
const char* game_tokens[NUM_TOKEN_TYPES] = {
        " ", REDCOLOR "x" RESETCOLOR, WHITECOLOR "o" RESETCOLOR, NULL
};

const char* color_strings[NUM_TOKEN_TYPES] = {
        "Empty", REDCOLOR "red" RESETCOLOR, WHITECOLOR "white" RESETCOLOR, NULL
};

/**
 * the read rest of line function - clears the buffer when there is buffer
 *  overflow
 **/
void read_rest_of_line(void)
{
        int ch;
        /* read each char in the input buffer until we run out of chars to read
         */
        while (ch = getc(stdin), ch != '\n' && ch != EOF)
                ;
        /* clear the error status on the stdin FILE pointer */
        clearerr(stdin);
}

/**
 * function to add the NUL character at the end of a string
 **/
char* cleanString(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}

/**
 * reads a string of input from the keyboard using fgets, displaying the prompt
 * specified first. This function also handles any buffer overflows
 **/
enum input_result get_string_from_keyboard(const char prompt[], char (*output)[], int len)
{
        char str[22];

        /* display the prompt */
        printf("%s", prompt);
        fgets(str, 21, stdin);

        if (strlen(str) == 1)
        {
                return IR_FAILURE;
        }

        if (str[strlen(str) - 1] != '\n')
        {
                read_rest_of_line();
        }
        else
        {
                strcpy(*output, cleanString(str));
        }

        /* get input from the keyboard - if the user pressed ctrl-d, return an
         * indication of this */
        return IR_SUCCESS;
}

/**
 * reads an int from the keyboard: firstly calls get_string_from_keyboard() and
 * then processes the string we get back. If the user had pressed ctrl-d or
 * <enter> on a new line then we just return IR_RTM. Otherwise we call strtol()
 * on the result. If there is leftover data in the string after processing the
 * numeric content then we reject the input and return IR_FAILURE. Next we check
 * if the number parsed is witin the range for an integer (as opposed to a long.
 * If it is within the allowed range we return IR_SUCCESS and otherwise
 * IR_FAILURE.
 **/
enum input_result get_int_from_keyboard(const char prompt[], int* output)
{
        char str[3];
        char *ptr;
        long ret=0;

        printf("%s", prompt);
        fgets(str, 3, stdin);

        if (str[strlen(str) - 1] != '\n')
        {
                read_rest_of_line();
        }
        else
        {
                ret = strtol(cleanString(str), &ptr, 10);
        }

        if (ret == 1)
        {
                return IR_SUCCESS;
        }
        else if (ret == 2)
        {
                return IR_RTM;
        }
        else
        {
                return IR_FAILURE;
        }
}

/**
 * displays the main menu
 **/
void display_menu(void)
{
        /* the menu items */
        char* menu_items[] = { "play the game", "quit" };
        int count;
        /* display the heading */
        char* heading = "\nWelcome to Gomoku";
        puts(heading);
        PUTLINE('=', strlen(heading));
        /* display each menu item */
        for (count = 0; count < NUM_MENU_ITEMS; ++count)
        {
                printf("%d) %s\n", count + 1, menu_items[count]);
        }
}

/**
 * prints the heading of the board
 **/
static void print_heading(void)
{
        int count;
        for (count = 0; count < BOARDWIDTH; ++count)
        {
                printf("%2d|", count + 1);
        }
        putchar('\n');
        PUTLINE('-', (BOARDWIDTH + 1) * 3);
}

/**
 * displays the game board including heading, etc.
 **/
void display_board(board theboard)
{
        int y, x;
        /* print the heading for the board */
        printf("\n");
        printf("  |");
        print_heading();
        /* for each row of the board */
        for (y = 0; y < BOARDHEIGHT; ++y)
        {
                /* print the row number */
                printf("%-2d", BOARDHEIGHT - y);
                /* print the values of each cell in the row */
                for (x = 0; x < BOARDWIDTH; ++x)
                {
                        printf("| %s", game_tokens[theboard[y][x]]);
                }
                printf("|\n");
                /* print the line under each row */
                if (y < BOARDHEIGHT - 1)
                {
                        PUTLINE('-', 3 * (BOARDWIDTH + 1));
                }
                else
                {
                        PUTLINE('=', 3 * (BOARDWIDTH + 1));
                }
        }
}

/**
 * displays the menu prompt the user for their choice
 **/
enum menu_choice get_menu_choice(void)
{
        int output;
        enum input_result result;

        display_menu();
        
        result = get_int_from_keyboard("Please enter your choice: ", &output);
        
        if (result == IR_RTM)
        {
                return MC_QUIT;
        }
        else if (result == IR_FAILURE)
        {
                return EOF;
        }
        else if (result == IR_SUCCESS)
        {
                return MC_PLAY_GAME;
        }

        return output - 1;
}

/**
 * print function provided to be able to print from outside this module
 **/
int error_print(const char* format, ...)
{
        /* the number of chars printed by this function */
        int charsprinted;
        va_list argvec;
        /* marshall the output for sending to vprintf */
        va_start(argvec, format);
        /* change the color to red and print the Error preambe for an error
         * message */
        charsprinted = fprintf(stderr, REDCOLOR "Error: ");
        /* print the output required by the user */
        charsprinted += vfprintf(stderr, format, argvec);
        /* reset back to the default colour */
        charsprinted += fprintf(stderr, RESETCOLOR);
        /* stop using the stdarg library */
        va_end(argvec);
        return charsprinted;
}

/**
 * print normal output - this function literally just calls printf.
 **/
int normal_print(const char* format, ...)
{
        int charsprinted;
        va_list argvec;
        va_start(argvec, format);
        charsprinted = vprintf(format, argvec);
        va_end(argvec);
        return charsprinted;
}
