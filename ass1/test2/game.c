#include "game.h"

enum input_result init_game(struct game* newgame)
{
        int count;
        int token;
        int curplayer;

        /* select random tokens */
        token = rand() % NUM_PLAYERS + 1;

        /* initialise the board */
        init_board(newgame->gameboard);
        
        /* initialise the players */
        for (count = 0; count < NUM_PLAYERS; ++count)
        {
                /* select a valid token for each player */
                ++token;
                if (token == C_INVALID)
                {
                        token = C_RED;
                }

                /* call init_player to do the initialisation of the players.
                 * Please note that as this is a function that calls i/o
                 * functions it returns a enum indicating success / failure or
                 * request to quit the game  */
                if (init_player(&newgame->players[count], token, newgame,
                                count + 1) == IR_RTM)
                {
                        return IR_RTM;
                }
        }

        /* select the play order of the players */
        curplayer = rand() % NUM_PLAYERS;

        newgame->current = &newgame->players[curplayer];
        
        curplayer = (curplayer + 1 % NUM_PLAYERS);
        
        newgame->other = &newgame->players[curplayer % NUM_PLAYERS];
        
        return IR_SUCCESS;
}

void play_game(void)
{
        /* the game struct that holds the data on the game state */
        struct game curgame;

        /* init the game struct */
        if (init_game(&curgame) == IR_RTM)
        {
                normal_print("the game has been quit!\n");
                return;
        }

        display_board(curgame.gameboard);
}

void swap_players(struct player** first, struct player** second)
{
}

enum input_result first_round(struct game* thegame)
{
        return IR_FAILURE;
}

