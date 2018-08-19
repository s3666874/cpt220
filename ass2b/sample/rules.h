/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include <string.h>
#include "board.h"
#include "word_list.h"
#include "helpers.h"
#include "shared.h"
#include "tile_list.h"

#ifndef RULES_H
#define RULES_H
#define NUM_LOC_PARTS 3

/**
 * enumeration that describes that token parts for a move entered.
 **/
enum loc_part
{
        LP_COL,    /* column */
        LP_ROW,    /* row */
        LP_DIR,    /*direction*/
        LP_INVALID /* this is not a valid move */
};

/* forwards declarations in order to avoid recursive includes */
struct player;
struct game;

/**
 * possible directions - horizontal or vertical
 **/
enum direction
{
        DIR_HORIZONTAL,
        DIR_VERTICAL
};

/**
 * holds the details on a move - the horizontal and vertical coordinates and
 * the direction.
 **/
struct move
{
        int x, y;
        enum direction dir;
};

/**
 * publicly available functions from this module
 **/
BOOLEAN is_valid_move(struct player *, char[], const char[], struct move *,
                      BOOLEAN);
int calculate_score(struct player *);
void apply_move(struct player *, const struct move *, const char[]);
BOOLEAN can_make(const char[], const struct board *, const struct tile_list *,
                 const struct move *, BOOLEAN);
BOOLEAN isvertical(const char[]);
#endif
