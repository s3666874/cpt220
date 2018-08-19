/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "shared.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOARD_H
#define BOARD_H
/* an empty cell in the game is represented by a space as that's easier to print
 * out */
#define EMPTY_CELL ' '
/* the range of allowed board sizes */
#define MAX_BOARD_SIZE 15
#define MIN_BOARD_SIZE 5

/* the contents of each board cell - the letter and the color of the player who
 * played the letter */
struct cell
{
        int letter;
        enum color color;
};

/* we define a default cell  for the board - this is consistent with using the
 * color enum as the color is specied just to reset the colors.
 */
extern const struct cell default_cell;

/*
 * The definition of a board as a 2d matrix and a specicifation of its size.
 * This allows for dynamic memory allocation.
 */
struct board
{
        struct cell** matrix;
        int boardsize;
};

/* public functions defined for this module */
BOOLEAN board_init(struct board*, int);

struct cell board_get(struct board*, int, int);

BOOLEAN board_set(struct board*, int, int, struct cell);

#endif
