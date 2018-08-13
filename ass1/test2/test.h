#ifndef TEST_H

		#define TEST_H
		#define NUM_PLAYERS 2

		struct game
		{
		        struct player players[NUM_PLAYERS];
		        struct player* current, *other;
		        board gameboard;
		};

		enum input_result init_game(struct game*);

		void play_game(void);

#endif
