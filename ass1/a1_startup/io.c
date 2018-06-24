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

void display_board(board gameboard)
{

    /*printf("%d\n", gameboard[0][0]);*/


    int x,y,i;

    for (x=0; x<BOARDWIDTH+1; x++)
    {
        for (y=0; y<BOARDHEIGHT+1; y++)
        {
            if (x == 0 && y == 0)
            {
                printf("  |");
            }
            else if (x == 0)
            {
                (y < 10) ? printf(" %d|", y) : printf("%d|", y);
            }
            else if (y == 0)
            {
                (x < 10) ? printf(" %d|", x) : printf("%d|", x);
            }
            else
            {
                /*printf("[%d,%d] |", x,y);*/
                /*printf("%d,%d|", x-1,y-1);*/
                /*printf("[%d,%d] [%d,%d] %d|", x,y,x-1,y-1,gameboard[x-1][y-1]);*/
                /*printf(" %s|", game_tokens[gameboard[x-1][y-1]]);*/

                printf("  |");
            }
        }
        printf("\n");

        for (i=0; i<15+1; i++)
        {
            (x == 15) ? printf("===") : printf("---");
        }

        printf("\n");
    }
}


