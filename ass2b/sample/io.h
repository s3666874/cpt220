/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"
#include "shared.h"
#include "word_list.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IO_H
#define IO_H

#define EXTRA_CHARS 2
#define SCORE_LEN 6
#define LINE_LEN 80
#define TILE_WIDTH 4
#define CELL_WIDTH 6

enum input_result
{
        IR_FAILURE,
        IR_SUCCESS,
        IR_RTM
};

extern const char *color_strings[];
struct game;
struct player;

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define SPACEWIDTH 1
#define SCOREWIDTH SCORE_LEN
#define SCOREBOARDWIDTH NAMELEN + SCOREWIDTH + 3 * SPACEWIDTH

#define PUTLINE(num, achar)                                                    \
        {                                                                      \
                int count;                                                     \
                for (count = 0; count < (int)(num); ++count)                   \
                {                                                              \
                        putchar((achar));                                      \
                }                                                              \
        }

#define CENTER(str, stream, width)                                             \
        fprintf(stream, "%*s\n", (width) - (int)(strlen(str)), str);

struct tile_list;

void read_rest_of_line(void);

BOOLEAN load_word_list(const char[], struct word_list *);

BOOLEAN load_scores(const char[], struct tile_list **, struct tile_list **);

enum input_result kbd_get_string(const char[], char[], int);

void display_board(const struct board *);

int normal_print(const char[], ...);

void print_hand(struct tile_list *);

int error_print(const char[], ...);

void print_finscores(struct game *);
#endif
