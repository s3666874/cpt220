/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "game.h"
#include "string.h"
#include "time.h"

/**
 * this file contains the implementation of functions for the management of the
 * game
 **/

int getToken()
{

    srand((unsigned) time(NULL));

   	return rand()%2;
}

char * cleanString(char s[])
{
    int i;

    i = strlen(s)-1;
    if ( s[i] == '\n')
    s[i] = '\0';

    return s;
}


/**
 * initialises the game to a starting state. 
 *
 * You should select a random token for one player and ensure the second player has a different token. 
 *
 * You should call init_player() passing in the address of the player, its token, and a pointer to this game. 
 *
 * Finally you should initialise the pointers to each player ensuring that a random player is selected to play the game. 
 *
 * You should also ensure the board is coorectly initialised through a call to init_board().
 **/
enum input_result init_game(struct game* newgame)
{

	char player1_name[21];
	char player2_name[21];

	struct player player1;
	struct player player2;

	struct player *player1_pointer;
	struct player *player2_pointer;

	int thisToken = getToken();


	/* Player 1 */
    printf("Please enter the name of player 1: ");
    fgets(player1_name, 20, stdin);

    strcpy(player1.name, cleanString(player1_name));

    player1.token = (thisToken == 1) ? C_RED : C_WHITE;

    player1_pointer = &player1;
    init_player(player1_pointer, player1.token, newgame, 1);


    /* Player 2 */
    printf("Please enter the name of player 2: ");
    fgets(player2_name, 20, stdin);

    strcpy(player2.name, cleanString(player2_name));

    player2.token = (thisToken == 1) ? C_WHITE : C_RED;

    player2_pointer = &player2;
    init_player(player2_pointer, player2.token, newgame, 2);

    newgame->current = (thisToken == 1) ? player1_pointer : player2_pointer;
    newgame->other = (thisToken == 1) ? player2_pointer : player1_pointer;
    
    

	/* Initialize gameboard 
	init_board();

	display_board(newgame.gameboard);
*/

	
/*
    newgame.current = &newgame.players[0];
    newgame.other = &newgame.players[1];

    strcpy(newgame.players[0].name, player1);
    newgame.players[0].token = C_RED;
    
    strcpy(newgame.players[1].name, player2);
    newgame.players[1].token = C_WHITE;


    init_board();
*/
    return IR_FAILURE;
}

/**
 * manages the main game loop - calls init_game to initialise the game and
 * then loops and calls take_turn for the current player and swaps players until
 * a player has won the game
 **/
void play_game(void)
{
        /* the game struct that holds the data on the game state */
        struct game curgame;

        /* init the game struct */
        init_game(&curgame);

        printf("%s plays first.\n\n", curgame.current->name);

        display_board(curgame.gameboard);

        
        /*
        curgame.current = &curgame.players[0];
        curgame.other = &curgame.players[1];

        strcpy(curgame.players[0].name, player1);
        curgame.players[0].token = C_RED;
        
        strcpy(curgame.players[1].name, player2);
        curgame.players[1].token = C_WHITE;  
*/
        /* the main game loop */
        /* swap the game pointers */
}

/**
 * swaps the two player pointers for the two players playing the current game
 * (it's a way for us to swap who the current player is). Please note that an
 * implementation that swaps values rather than pointers will not get full marks
 * for this. This function is only worth a few marks but the intellectual
 * content understanding is very important and thus it is worth substantially
 * more than a few lines of code are worth elsewhere in this assignment.
 **/
void swap_players(struct player** first, struct player** second)
{
}

/**
 * implements the rules for the first round of the game, the so-called
 * swap2 rules. Please see the assignment specification and game rules for
 * further details.
 **/
enum input_result first_round(struct game* thegame)
{
        return IR_FAILURE;
}
