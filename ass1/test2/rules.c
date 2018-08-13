#include "rules.h"
#include "game.h"
#include "player.h"

BOOLEAN is_winner(const struct player* curplayer)
{
        return FALSE;
}

BOOLEAN move_is_valid(const struct player* curplayer,
                      const struct coordinate* curmove)
{
        return TRUE;
}

BOOLEAN apply_move(board theboard, const struct coordinate* themove,
                   enum cell token)
{
        return FALSE;
}
