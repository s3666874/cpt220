/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"

/*****************************************************************************
 * board.c and board.h form the board module. You need to provide functions
 * that manage the game board: allocate the board, set and get the contents of
 * the cells for the board and free the board when exiting the game
 ****************************************************************************/
struct board init_board(int boardsize)
{
		int i,j;
		struct board theboard;

		theboard.boardsize = boardsize;
		theboard.matrix = malloc(boardsize * sizeof(struct cell));

		for (i=0; i < boardsize; ++i)
		{
				theboard.matrix[i] = malloc(boardsize * sizeof(struct cell));

				for (j=0; j < boardsize; ++j)
				{
						theboard.matrix[i][j].letter = 'A';
				}
		}

		return theboard;
}
