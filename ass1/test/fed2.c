#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <limits.h>

enum cell
{
    C_EMPTY,
    C_RED,
    C_WHITE,
    C_INVALID
};

/* rename an array or arrays of type enum cell to be a board - note that under
* the hood it is still an array of ints and will behave accordingly */
typedef enum cell board[15][15];

int main(void)
{
    int x,y,i;

    board gameboard;

    for (x=0; x<15+1; x++)
    {
        for (y=0; y<15+1; y++)
        {
            gameboard[x-1][y-1] = C_EMPTY;
        }
    }


    printf("%d\n", gameboard[12][3]);
    printf("%d\n", gameboard[12][4]);
    printf("%d\n", gameboard[12][5]);
    printf("%d\n", gameboard[12][6]);
    printf("\n");
    
    printf("%d\n", gameboard[12][8]);
    printf("%d\n", gameboard[12][10]);
    printf("%d\n", gameboard[12][13]);
    printf("%d\n", gameboard[12][14]);
    printf("\n");


    /*
	enum cell token;

    token = C_RED;

    printf("%d\n", token);
*/
/*
    printf("%d\n", gameboard[13][10]);
    printf("%d\n", gameboard[8][9]);
*/

/*
    for (x=0; x<15+1; x++)
    {
        for (y=0; y<15+1; y++)
        {
            if (x == 0 && y == 0)
            {
                printf("  |");
            }
            else if (x == 0)
            {
                (y < 10) ? printf(" %d|", y) : printf("%d|", y);
            }
            else if (y == 0)
            {
                (x < 10) ? printf(" %d|", x) : printf("%d|", x);
            }
            else
            {
                printf("[%d,%d] |", x,y);
                printf("%d,%d|", x-1,y-1);
                
                printf("[%d,%d]|", x-1,y-1);
                printf("(%d,%d) [%d,%d] %d|", y,x,x-1,y-1,gameboard[x-1][y-1]);
            }
        }
        printf("\n");

        for (i=0; i<15+1; i++)
        {
            (x == 15) ? printf("===") : printf("---");
        }

        printf("\n");
    }
*/

    return 0;
}
