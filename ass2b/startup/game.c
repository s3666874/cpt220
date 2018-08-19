/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "game.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * the game module manages the overall game. This includes initialisation of
 * the game (initialise and load data for the game, manage the game while in
 * process (selecting the current player, allow that player to have their turn)
 * and finally, displaying scores at the end of the game (when it is quit). Some
 * of these things are managed by calling functions in other modules.
 *****************************************************************************/

/**
 * initialise the game - just like in assignment 1, you should call all the
 *functions that initialise the data structures for the game from here.
 *
 * Start by loading the score file - the implementation of that function will be
 * in io.c but you'll need to call it from here.
 *
 * You'll also need to ask for how many players are playing but the allocation
 * and initialisation of those players should be done in player.c - including
 * any user input that might involve.
 *
 * Finally, you should prompt the user for the size of the board (that will be
 * used for both width and height as the board is a square). You'll then pass
 * that value into the board module to allocate a 2-dimensional board.
 **/
enum input_result init_game(struct game* thegame, struct word_list* dictionary,
                            const char tile_file[])
{
        int *str = malloc((21) * sizeof(char));
        enum input_result status;
        enum input_result result;

        struct tile_list lettermap;
        struct tile_list fulllist;

        struct board theboard;

        BOOLEAN success = FALSE;

        /* load the scores into tilemap and tiledeck respectively */
        if (!load_scores(tile_file, &lettermap, &fulllist))
        {
                free(str);
                return IR_FAILURE;
        }

        /*print_tiles(fulllist.tiles, 100);*/

        /* assign the tilemap and tiledeck to the current game struct */
        thegame->tilemap = &lettermap;
        thegame->tiledeck = &fulllist;

        /*print_tiles(thegame->tiledeck->tiles, 100);*/

        /* grab the number of players from the user */
        while (!success)
        {
                while (result = get_int_from_keyboard("How many players should play? ", str, 1), result == IR_FAILURE)
                {
                        if (result == IR_RTM)
                                success = FALSE;
                }

                if (*str > MAX_PLAYERS)
                {
                        printf("Error: invalid number of players. Please try again.\n");
                        continue;
                }

                thegame->num_players = *str;
                thegame->allwords = dictionary;
                thegame->players = new_players(*str, thegame, &status);

                success = TRUE;
        }

        /* reset flag */
        success = FALSE;

        while (!success)
        {
                while (result = get_int_from_keyboard("How wide and high should the board be? The minimum is 5 and the maximum is 15: ", str, 2), result == IR_FAILURE)
                {
                        if (result == IR_RTM)
                                success = FALSE;
                }

                if (*str < MIN_BOARD_SIZE || *str > MAX_BOARD_SIZE)
                {
                        printf("Error: boardsize outside the allowed range. Please try again.\n");
                        continue;
                }

                theboard = init_board(*str);
                thegame->theboard = theboard;

                success = TRUE;
        }

        free(str);
        return IR_SUCCESS;
}

/**
 * The main game loop for the game. Start by initialising the game by a call to
 * init_game() then simply iterate over the players, getting each to have their
 * turn. As there has been no end of game condition specified, the game simply
 * ends when a player quits. At this time, just output the list of players
 * sorted by ther currect score. Please note that as the rules for the placing
 * of the first turn are different you will also need to keep track of whether
 * it is the first turn or not.
 **/
void play_game(struct word_list* dictionary, const char tilefile[])
{
        int i=0;
        enum input_result result;
        struct game thegame;

        BOOLEAN isfirst = TRUE;

        /* initialise the game */
        init_game(&thegame, dictionary, tilefile);

        /* iterate over the players allowing each to have their turn until
         * someone quits */
        while (result = take_turn(&thegame.players[i], isfirst), result == IR_SUCCESS || result == IR_FAILURE)
        {
                if (result == IR_SUCCESS)
                {
                        if (i == thegame.num_players-1)
                        {
                                i=0;
                        }
                        else
                        {
                                i++;
                        }

                        isfirst = FALSE;
                }
                else if (result == IR_RTM)
                {
                        break;
                }
        }

        /* finalise the scores and print them */


        /* free memory for the game */
        free_game(&thegame);
}

/**
 * Once the game is finished we need to free all memory allocated for the game
 **/
void free_game(struct game* thegame)
{
        int i;

        /* free players */
        free(thegame->players);

        /* free matrix */
        for (i=1; i <= thegame->theboard.boardsize; i++)
        {
                /*for (j=1; j <= thegame->theboard.boardsize; j++)
                {
                        free(thegame->theboard.matrix[i][j]);
                }*/

                free(thegame->theboard.matrix[i]);
        }

        /* free word_list 
        free_word_list(thegame->allwords);*/

        /* free tile_list 
        free(thegame->tilemap->tiles);
        free(thegame->tiledeck->tiles);*/
}





