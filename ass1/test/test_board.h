#include <string.h>

#ifndef TEST_BOARD_H

	#define TEST_BOARD_H

	#define BOARDHEIGHT 15
	#define BOARDWIDTH BOARDHEIGHT

	/* a cell on the board */
	enum cell
	{
	    C_EMPTY,
	    C_RED,
	    C_WHITE,
	    C_INVALID
	};

	typedef enum cell board[BOARDHEIGHT][BOARDWIDTH];

	void init_board(board);

#endif