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
        /* the name of the player */
        char name[NAMELEN + 1];
        /* the player's score */
        int score;
        /* the color of each token played by this player */
        enum color color;
        /* the hand for the player */
        struct tile_list hand;
        /* a pointer to the game data for this game */
        struct game* thegame;
};

/* public functions callable from this module */
struct player* new_players(int, struct game*, enum input_result*);

enum input_result init_player(struct player*, int, enum color, struct game*);

enum input_result take_turn(struct player*, BOOLEAN);

void shuffle_players(struct player*, int);

void player_sort(struct player*, int,
                 int (*)(const struct player*, const struct player*));

int player_cmp(const struct player*, const struct player*);

int player_shuffle_cmp(const struct player*, const struct player*);

enum color get_next_available_color();

void free_players(struct player*, int);

void print_players(struct player*, int);

BOOLEAN is_letter_in_player_hand(int, struct player *);

#endif
