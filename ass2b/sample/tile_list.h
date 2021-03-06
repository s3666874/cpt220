/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "helpers.h"
#include "io.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WORDMAP_H
#define WORDMAP_H
#define AL_NUM_LETTERS 26
#define NUM_TILE_DELIMS 2
#define NUM_TILE_TOKENS 3
#define NUM_LETTERS 100
#define ONECHAR 1

/**
 * a tile is a letter and tile pair.
 **/
struct tile
{
        /* int is used for letter rather than char in order to consistently
         * use negative numbers
         */
        int letter;
        int score;
};

/**
 * score_count stores both the tile and how many times that tile should occur.
 **/
struct score_count
{
        struct tile tile;
        int count;
};

/**
 * global const variable that indicates that an error has occured.
 **/
extern const struct score_count error_score;

struct tile_list
{
        struct tile* tiles;
        int num_tiles;
        int total_tiles;
};

/* publicly available functions for this module */
struct score_count new_score_count(const char[]);
struct tile_list* tl_make(int);
struct tile_list* tl_init(struct tile_list*, int);
BOOLEAN tl_add(struct tile_list*, const struct tile);
BOOLEAN tl_fill(struct tile_list*, struct tile_list*);
void tl_shuffle(struct tile_list*);
BOOLEAN tl_remove(struct tile_list*, struct tile*, int);
int tl_count_blanks(const struct tile_list*);
BOOLEAN tl_set(struct tile_list*, const struct tile);
int tl_get(struct tile_list*, const char);
#endif
