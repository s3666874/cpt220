#include "test_board.h"


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
