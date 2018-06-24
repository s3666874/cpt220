#include "test.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/* Add the NUL character to the end of a string */
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

void printPlayer (struct player player)
{
    
    printf("Player ID: %d\n", player.id);
    printf("Player Name: %s\n", player.name);
    printf("Player age: %d\n", player.age);
    printf("\n");
    

    /*printf("Player Name: %s\n", player.name);*/
}

int getToken()
{

    srand((unsigned) time(NULL));
        
    return rand()%2;
}

/**
 * The main function - the main entry point into your program
 **/
int main(void)
{       
    char str[3];
    char *ptr;
    long ret=0;

    char playerName1[21];
    char playerName2[21];

    struct player player1;
    struct player player2;

    printf("Welcome to Gomoku\n================\n1) play the game\n2) quit\n");

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
        fgets(playerName1, 20, stdin);

        printf("Please enter the name of player 2: ");
        fgets(playerName2, 20, stdin);

        player1.id = 123;
        player1.age = 23;
        strcpy(player1.name, cleanString(playerName1));

        player2.id = 321;
        player2.age = 12;
        strcpy(player2.name, cleanString(playerName2));

        printPlayer(player1);
        printPlayer(player2);
        

        /*init_board(board);*/

    }

    /* quit the game */
    if (ret == 2)
    {
            printf("Thank you for playing\n");
    }

    return 0;
}


