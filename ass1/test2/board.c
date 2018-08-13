#include "board.h"
#include "io.h"

void init_board(board aboard)
{
        memset(aboard, 0, sizeof(enum cell) * BOARDWIDTH * BOARDHEIGHT);
}

BOOLEAN set_cell(board aboard, int x, int y, enum cell contents)
{
        if (x >= BOARDWIDTH || y >= BOARDHEIGHT || x < 0 || y < 0)
        {
                return FALSE;
        }
        aboard[y][x] = contents;
        return TRUE;
}

enum cell* get_cell(board aboard, int x, int y)
{
        if (x >= BOARDWIDTH || y >= BOARDHEIGHT || x < 0 || y < 0)
        {
                return NULL;
        }
        return &aboard[y][x];
}

