#include "test_board.h"
#include "test_player.h"

#ifndef TEST_GAME_H

	#define TEST_GAME_H
	#define NUM_PLAYERS 2

	/**
	 * the game struct defines the information about the game state that is passed
	 *to the various functions that are part of the implementation of a game.
	 **/
	struct game
	{
	    struct player players[NUM_PLAYERS];
	    board gameboard;
	    struct player* current, *other;
	};

#endif