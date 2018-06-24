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

/**
 * This file contains the implementation of the functions that manipulates the
 * board type
 **/

/**
 * initialise the board to be an empty board
 **/
void init_board(board aboard)
{
	int c=1;
	int r=16;

	while (r > 0)
	{
		if (r == 16)
		{
			printf("  |");
		}
		else
		{
			if (r < 10)
			{
				printf(" %d|", r);
			}
			else
			{
				printf("%d|", r);
			}
			
		}
		

		while (c < 16)
		{
			if (r == 16)
			{
				if (c < 10)
				{
					printf(" %d|", c);
				}
				else
				{
					printf("%d|", c);
				}
				
			}
			else
			{
				printf("  |");
			}
			
			c+=1;
		}

		printf("\n");

		c=1;
		while (c < 16)
		{
			printf("---");
			
			c+=1;
		}
		printf("---\n");

		r-=1;
		c=1;
	}
}
