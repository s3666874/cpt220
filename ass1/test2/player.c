#include "player.h"
#include "game.h"


enum input_result init_player(struct player* curplayer, enum cell token,
                              struct game* thegame, int playernum)
{
        char name[NAMELEN + EXTRACHARS];
        char prompt[LINELEN + 1];
        enum input_result result;

        /* associate the game with this player */
        curplayer->curgame = thegame;
        /* associate the token with the player */
        curplayer->token = token;
        /* prompt the user for their name */
        sprintf(prompt, "Please enter the name for player %d: ", playernum);
        while (result =
                   get_string_from_keyboard(prompt, name, NAMELEN + EXTRACHARS),
               result == IR_FAILURE)
                ;
        /* copy the name read from the keyboard into the player struct */
        strcpy(curplayer->name, name);
        return IR_SUCCESS;
}


enum input_result take_turn(struct player* curplayer)
{
        return IR_FAILURE;
}
