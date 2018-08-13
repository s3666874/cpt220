/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "player.h"
#include "game.h"
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 1 /*The maximum number of matches allowed in a single string*/

/**
 * this file contains the implementation of the functions for manipulation of
 * the player type
 **/

/**
 * initialises the player passed in so that it has the token specified. You
 * should also prompt the user for this name
 **/
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
        
        while (result = get_string_from_keyboard(prompt, &name, NAMELEN + EXTRACHARS), result == IR_FAILURE)
                ;

                /* copy the name read from the keyboard into the player struct */
                strcpy(curplayer->name, name);

        return IR_SUCCESS;
}

/**
 * function to add the NUL character at the end of a string
 **/
char* cleanString2(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}

BOOLEAN match(regex_t *pexp, char *sz) {
    regmatch_t matches[MAX_MATCHES]; /*A list of the matches in the string (a list of 1)*/

    /*Compare the string to the expression*/
    /*regexec() returns 0 on match, otherwise REG_NOMATCH*/
    if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
        /*printf("\"%s\" matches characters %d - %d\n", sz, matches[0].rm_so, matches[0].rm_eo);*/
        /*printf("Matched\n");*/
        return TRUE;
    } else {
        /*printf("\"%s\" does not match\n", sz);*/
        /*printf("Does not match\n");*/
        return FALSE;
    }
}

/**
 * get input for a turn from the user, validate it as a move coordinate and if
 * it is valid, apply the move to the board. If the move is not valid then
 * display an error message but if it is valid return a IR_SUCCESS result. If a
 * user has chosen to quit the game, return IR_RTM.
 **/
enum input_result take_turn(struct player* curplayer)
{
        char input[22];
        char prompt[LINELEN + 1];
        struct coordinate themove;
        enum input_result result = IR_FAILURE;

        int rv;
        char ret[20];
        char *thetoken;
        const char s[2] = ",";
        int count = 1;

        regex_t exp; /*Our compiled expression*/

        rv = regcomp(&exp, "^[0-9]+,[0-9]+$", REG_EXTENDED);

        while (result == IR_FAILURE)
        {
                sprintf(prompt, "Enter the move for %s whose token is %s: ", curplayer->name, game_tokens[curplayer->token]);

                result = get_string_from_keyboard(prompt, &input, 20);

                strcpy(ret, cleanString2(input));

                if (match(&exp, ret))
                {
                        count=1;
                        thetoken = strtok(ret, s);

                        while(thetoken != NULL)
                        {
                                if (count == 1)
                                {
                                        themove.row = atoi(thetoken);
                                }
                                else 
                                {
                                        themove.col = atoi(thetoken);
                                }

                                /*printf("%s\n", thetoken);*/
                                thetoken = strtok(NULL, s);
                                count++;
                        }

                        /* Out of range */
                        if (themove.row == 0 || themove.row < 1 || themove.row > 15 || themove.col == 0 || themove.col < 1 || themove.col > 15)
                        {
                                printf("Out of range.\n");
                                result = IR_FAILURE;
                        }
                        else
                        {
                                /*printf("Row: %d\nCol: %d\n", themove.row, themove.col);*/
                                result = IR_SUCCESS;
                        }
                }
                else
                {
                        printf("Invalid input\n");
                        result = IR_FAILURE;
                }
        }

        regfree(&exp);

        return IR_SUCCESS;
}
