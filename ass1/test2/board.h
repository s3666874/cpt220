#include "shared.h"
#include <string.h>


#ifndef BOARD_H

	#define BOARD_H
	
	#define BOARDHEIGHT 15
	#define BOARDWIDTH BOARDHEIGHT
	#define NUM_TOKEN_TYPES 4

	enum cell
	{
	        C_EMPTY,
	        C_RED,
	        C_WHITE,
	        C_INVALID
	};

	typedef enum cell board[BOARDHEIGHT][BOARDWIDTH];
	typedef enum cell row[BOARDWIDTH];

	typedef row* boardref;


	void init_board(board);

	BOOLEAN set_cell(board, int, int, enum cell);

	enum cell* get_cell(board, int, int);
#endif
