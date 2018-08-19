/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "game.h"
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
        enum input_result result;
        char line[LINE_LEN + EXTRA_CHARS];
        int num_players;
        BOOLEAN success = FALSE;

        /* zero out the game struct */
        memset(thegame, 0, sizeof(struct game));
        /* load the tiles */
        if (!load_scores(tile_file, &thegame->tilemap, &thegame->tiledeck))
        {
                error_print("Error: loading of scores failed.\n");
                return IR_FAILURE;
        }
        /* store the dictionary pointer */
        thegame->allwords = dictionary;
        /* get the number of players to play */
        while (!success)
        {
                /* get input */
                while (result = kbd_get_string("How many players should play? ",
                                               line, LINE_LEN + EXTRA_CHARS),
                       result == IR_FAILURE)
                        ;
                /* convert to int */
                if (!strtoint(line, &num_players))
                {
                        continue;
                }
                /* validate the value requested is within the allowed range */
                if (num_players <= 0 || num_players > MAX_PLAYERS)
                {
                        error_print(
                            "invalid number of players. Please try again.\n\n");
                        continue;
                }
                /* allocate the players - if allocation of the players fails,
                 * display an error
                 */
                if (thegame->players =
                        new_players(num_players, thegame, &result),
                    result == IR_FAILURE)
                {
                        error_print("allocation of players failed.\n");
                        return IR_FAILURE;
                }
                /* shuffle the players so that they are in a rangom order */
                shuffle_players(thegame->players, thegame->num_players);
                success = TRUE;
        }
        success = FALSE;
        /* get the board size from the user */
        while (!success)
        {
                int boardsize;
                char prompt[LINE_LEN + 1];
                sprintf(prompt, "How wide and high should the "
                                "board be? The minimum is %d and "
                                "the maximum is %d: ",
                        MIN_BOARD_SIZE, MAX_BOARD_SIZE);
                fold(prompt, LINE_LEN + 1);
                while (result =
                           kbd_get_string(prompt, line, LINE_LEN + EXTRA_CHARS),
                       result == IR_FAILURE)
                        ;
                if (result == IR_RTM)
                {
                        /*return IR_RTM;*/
                        success = FALSE;
                }
                if (!strtoint(line, &boardsize))
                {
                        continue;
                }
                if (boardsize < MIN_BOARD_SIZE || boardsize > MAX_BOARD_SIZE)
                {
                        error_print("Error: boardsize outside the allowed "
                                    "range. Please tray again. \n");
                        continue;
                }
                /* initialise the board to the size requested */
                if (!board_init(&thegame->theboard, boardsize))
                {
                        /*return FALSE;*/
                        success = FALSE;
                }
                success = TRUE;
        }
        return result;
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
        struct game thegame;
        /* initialise the game */
        if (init_game(&thegame, dictionary, tilefile) != IR_SUCCESS)
        {
                free_game(&thegame);
                return;
        }
}

/**
 * Once the game is finished we need to free all memory allocated for the game
 **/
void free_game(struct game* thegame)
{
}
