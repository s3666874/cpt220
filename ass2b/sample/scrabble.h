/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "game.h"
#include "io.h"
#include "tile_list.h"
#include "word_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_ARGS 3
#define MAX_ARGS 4

enum arg
{
        ARG_DICTIONARY = 1,
        ARG_SCORE,
        ARG_SEED
};

void display_usage(void);
