/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "board.h"
#include "io.h"

/**
 * This file contains the implementation of the functions that manipulates the
 * board type
 **/

/**
 * initialise the board to be an empty board
 **/
void init_board(board aboard)
{
        memset(aboard, 0, sizeof(enum cell) * BOARDWIDTH * BOARDHEIGHT);
}

/**
 * set the value in a cell to the contents value specified
 **/
BOOLEAN set_cell(board aboard, int x, int y, enum cell contents)
{
        if (x >= BOARDWIDTH || y >= BOARDHEIGHT || x < 0 || y < 0)
        {
                return FALSE;
        }
        aboard[y][x] = contents;
        return TRUE;
}

/**
 * gets the value stored in a cell. Note that I am returning a pointer for when
 * an invalid request is sents - int that case we should return NULL
 **/
enum cell* get_cell(board aboard, int x, int y)
{
        if (x >= BOARDWIDTH || y >= BOARDHEIGHT || x < 0 || y < 0)
        {
                return NULL;
        }
        return &aboard[y][x];
}
