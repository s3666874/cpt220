#include "board.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IO_H
	#define IO_H

	enum input_result
	{
        /* the i/o operation failed - this is often due to buffer overflow */
        IR_FAILURE,
        /* the i/o operation succeeded */
        IR_SUCCESS,
        /* there was a request to return to the main menu such as when quitting
           the game */
        IR_RTM
	};

	#define LINELEN 80
	#define EXTRACHARS 2
	#define DECIMAL 10
	#define CHARLEN 1

	#define NUM_MENU_ITEMS 2

	#define REDCOLOR "\033[0;31m"
	#define WHITECOLOR "\033[37;1m"
	#define RESETCOLOR "\033[0;0m"

	#define MAXCLRLEN 5

	#define PUTLINE(CH, N)                                                     \
        {                                                                      \
                int count;                                                     \
                for (count = 0; count < (N); ++count)                          \
                {                                                              \
                        putchar(CH);                                           \
                }                                                              \
                putchar('\n');                                                 \
        }

    enum menu_choice
	{
        MC_PLAY_GAME,
        MC_QUIT,
        MC_INVALID
	};

	extern const char* game_tokens[];

	extern const char* color_strings[];

	void read_rest_of_line(void);

	enum input_result get_string_from_keyboard(const char[], char[], int);

	enum input_result get_int_from_keyboard(const char[], int*);

	void display_menu(void);

	enum menu_choice get_menu_choice(void);

	int error_print(const char*, ...);

	int normal_print(const char*, ...);

	void display_board(board);

#endif
