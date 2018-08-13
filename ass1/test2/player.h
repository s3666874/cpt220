#include "board.h"
#include "io.h"
#include <limits.h>


#ifndef PLAYER_H
	
	#define PLAYER_H

	struct game;

	#define NAMELEN 20


	struct player
	{
	        /* the player's name */
	        char name[NAMELEN + 1];
	        /* their token type */
	        enum cell token;
	        /* a pointer to the current game - this allows us to not have to pass
	         * this in as a parameter to functions that already have a pointer to
	         * the player */
	        struct game* curgame;
	};

	enum input_result init_player(struct player*, enum cell, struct game*, int);

	enum input_result take_turn(struct player*);

#endif
