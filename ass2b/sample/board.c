/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
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

const struct cell default_cell = { ' ', C_RESET };

/**
 * Initalises the game board to a known safe state - that is to being an empty
 * board. The size specifies how big the board will be - use this to allocate
 * space for the board in both columns and rows.
 **/
BOOLEAN board_init(struct board* theboard, int size)
{
        int xcount, ycount;

        /* validate the board size */
        if (size < 0 || size > MAX_BOARD_SIZE)
        {
                return FALSE;
        }
        /* allocate the row pointers */
        theboard->matrix = (struct cell**)malloc(size * sizeof(struct cell*));
        /* allocate each row and then initialise each cell to the default cell
         */
        for (ycount = 0; ycount < size; ++ycount)
        {
                theboard->matrix[ycount] =
                    (struct cell*)malloc(size * sizeof(struct cell));
                for (xcount = 0; xcount < size; ++xcount)
                {
                        theboard->matrix[ycount][xcount] = default_cell;
                }
        }
        /* don't forget to store the size */
        theboard->boardsize = size;
        return TRUE;
}

/**
 * function for retrieving a value from a cell
 **/
struct cell board_get(struct board* theboard, int x, int y)
{
        return theboard->matrix[y][x];
}

/**
 * sets the cell specified to the new value
 **/
BOOLEAN board_set(struct board* theboard, int x, int y, struct cell acell)
{
        if (x >= theboard->boardsize || y >= theboard->boardsize)
        {
                return FALSE;
        }
        theboard->matrix[y][x] = acell;
        return TRUE;
}
