#include <limits.h>

#ifndef TEST_PLAYER_H

    #define TEST_PLAYER_H
    /* forwards declaration of the game struct so we can pointers to game passed in
     * as parameters in this module */
    /* struct game; */

    /* the maximum length of a player's name */
    #define NAMELEN 20

    /* the player struct - represents a player in the game */
    struct player
    {
        /* the player's name */
        char name[NAMELEN + 1];
        /* their token type */
        enum cell token;
        /* a pointer to the current game - this allows us to not have to pass
         * this in as a parameter to functions that already have a pointer to
         * the player */
        struct game* curgame;
    };

#endif