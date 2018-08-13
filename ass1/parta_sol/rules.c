/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "rules.h"
#include "game.h"
#include "player.h"

BOOLEAN is_winner(const struct player* curplayer)
{
        return FALSE;
}

/**
 * check if a move is valid. It is valid if the cell specified is empty
 **/
BOOLEAN move_is_valid(const struct player* curplayer,
                      const struct coordinate* curmove)
{
        return TRUE;
}

/**
 * apply the move to the board - simply set the board coordinates specified by
 * themove to the toke specified.
 **/
BOOLEAN apply_move(board theboard, const struct coordinate* themove,
                   enum cell token)
{
        

        return FALSE;
}


BOOLEAN valid_first_move(const struct player * curplayer, const struct coordinate* themove)
{
		return TRUE;
}
