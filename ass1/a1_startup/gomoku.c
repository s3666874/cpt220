/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "gomoku.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


/* Helper function for removing the last newline and adding a NUL character */
char * cleanString(char s[])
{
    int i;

    i = strlen(s)-1;
    if ( s[i] == '\n')
    s[i] = '\0';

    return s;
}

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
 * The main function - the main entry point into your program
 **/
int main(void)
{
    /* you should treat the comments in this function as a hint on how to 
     * get started. You should start by getting a menu working that behaves
     * the same as the sample executable. 
     */
    /* initialise the random number generator for your program */
    /* display the menu continuously until the user decided to quit the
     * program
     */
            /* display the menu and get the choice from the user */
                    /* based on the choice the user made you should:
                     */
                            /* play the game */
                            /* quit the program */
    
    char str[3];
    char *ptr;
    long ret=0;

    char player1[21];
    char player2[21];

    /* Display the initial welcome menu with options */
    printf("Welcome to Gomoku\n================\n1) play the game\n2) quit\n");

    /* if the input is not either 1 or 2 then it is invalid then we display the appropriate message */
    do
    {
        printf("Enter your selection: ");
        fgets(str, 3, stdin);
        
        if (str[strlen(str) - 1] != '\n')
        {
            read_rest_of_line();
        }
        else
        {
            ret = strtol(cleanString(str), &ptr, 10);
        }

    } while (ret != 1 && ret != 2);

    /* play the game */
    if (ret == 1)
    {
        printf("Please enter the name of player 1: ");
        fgets(player1, 20, stdin);

        printf("Please enter the name of player 2: ");
        fgets(player2, 20, stdin);

        /* printf("%s will be playing %s\n", cleanString(player1), cleanString(player2)); */
        init_board();
    }

    if (ret == 2)
        printf("Thank you for playing\n");

    return 1;
}
