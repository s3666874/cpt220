/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "shared.h"
#include <string.h>

/**
 * This file defines the board datatype which is just a 2-dimensional array. You
 * should define any functions (the prototype does in this file and the
 * implementation goes into the board.c file.
 **/

#ifndef BOARD_H /*include guard for the board module - ensures that this       \
                   module is only included once in any .c file */
#define BOARD_H
/* the gomoku board is a 15 x 15 cell board */
#define BOARDHEIGHT 15
#define BOARDWIDTH BOARDHEIGHT

/* how many token types in the system */
#define NUM_TOKEN_TYPES 4
/* a cell on the board */
enum cell
{
        C_EMPTY,
        C_RED,
        C_WHITE,
        C_INVALID
};

/* rename an array or arrays of type enum cell to be a board - note that under
 * the hood it is still an array of ints and will behave accordingly */
typedef enum cell board[BOARDHEIGHT][BOARDWIDTH];

/* a type name for a single row of the game board */
typedef enum cell row[BOARDWIDTH];

/* pointer to a row - basically what C degrades the 2d array to */
typedef row* boardref;

/* public functions advertised for this module */

void init_board(board);

BOOLEAN set_cell(board, int, int, enum cell);

enum cell* get_cell(board, int, int);

#endif /* include guard for the board module */
