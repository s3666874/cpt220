#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#define BOARD_SIZE 10
#define PUTLINE(CH, N)                                                 \
{                                                                      \
        int count;                                                     \
        for (count = 0; count < (N); ++count)                          \
        {                                                              \
                putchar(CH);                                           \
        }                                                              \
        putchar('\n');                                                 \
}

typedef enum
{
    FALSE,
    TRUE
} BOOLEAN;

enum color
{
    C_RED,
    C_GREEN,
    C_YELLOW,
    C_BLUE,
    C_MAGENTA,
    C_CYAN,
    C_RESET,
    C_INVALID
};

struct cell
{
    int letter;
    enum color color;
};

struct board
{
    struct cell** matrix;
    int boardsize;
};

struct game
{
	struct board theboard;
	int num_players;
};

struct board init_board(int boardsize)
{
	int i,j;
	struct board theboard;

	theboard.matrix = malloc(boardsize * sizeof(struct cell));

	for (i=0; i < boardsize; ++i)
	{
		theboard.matrix[i] = malloc(boardsize * sizeof(struct cell));

		for (j=0; j < boardsize; ++j)
		{
			theboard.matrix[i][j].letter = 'A';
		}
	}

	return theboard;
}

void print_board()
{
	int i,j;

	for (i=0; i<BOARD_SIZE+1; i++)
	{
		if (i == 0)
		{
			printf("    |");
		}
		else
		{
			printf("  %d |", i);
		}

		for (j=0; j<BOARD_SIZE; j++)
		{
			if (i == 0)
			{
				printf("  %d |", j+1);
			}
			else
			{
				printf("    |");
			}
			
		}
		printf("\n");

		PUTLINE('-', 5 * (BOARD_SIZE + 1));
	}

	printf("\n");
}

int main(void)
{
	struct game thegame;
	struct board theboard;

	theboard = init_board(BOARD_SIZE);

	thegame.theboard = theboard;

	print_board();

	/*printf("%c\n", thegame.theboard.matrix[4][5].letter);*/

	return 0;
}
