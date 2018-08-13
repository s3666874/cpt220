#include "board.h"
#include "player.h"
#include "rules.h"
#include "io.h"

#ifndef GAME_H

		#define GAME_H
		#define NUM_PLAYERS 2

		struct game
		{
		        struct player players[NUM_PLAYERS];
		        struct player* current, *other;
		        board gameboard;
		};

		enum input_result init_game(struct game*);

		void play_game(void);

		enum input_result first_round(struct game*);

		void swap_players(struct player**, struct player**);

#endif
