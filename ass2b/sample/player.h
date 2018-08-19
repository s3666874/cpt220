/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"
#include "io.h"
#include "rules.h"
#include "tile_list.h"
#include <string.h>
#ifndef PLAYER_H
#define PLAYER_H

/* the maximum number of players for the game */
#define MAX_PLAYERS 6
#define HANDSIZE 7
#define NAMELEN 20
#define LOCATION_STRING_MAX 7

struct game;

struct player
{
        char name[NAMELEN + 1];
        int score;
        enum color color;
        struct tile_list hand;
        struct game* thegame;
};

enum input_result init_player(struct player*, int, enum color, struct game*);
void shuffle_players(struct player*, int);
struct player* new_players(int, struct game*, enum input_result*);
void players_free(struct player*, int);
void swap_players(struct player*, struct player*);
int player_cmp(const struct player*, const struct player*);
int player_shuffle_cmp(const struct player*, const struct player*);
void player_sort(struct player*, int,
                 int (*)(const struct player*, const struct player*));
enum input_result take_turn(struct player*, BOOLEAN);
#endif
