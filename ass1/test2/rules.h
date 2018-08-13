#include "board.h"
#include "shared.h"

#ifndef RULES_H
	#define RULES_H

	struct game;
	struct player;

	BOOLEAN is_winner(const struct player *);

	BOOLEAN move_is_valid(const struct player *, const struct coordinate *);

	BOOLEAN valid_first_move(const struct player *, const struct coordinate *);

	BOOLEAN apply_move(board, const struct coordinate *, enum cell);
#endif
