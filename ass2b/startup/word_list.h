/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "shared.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WORD_LIST_H
#define WORD_LIST_H

/* the longest word supported by this program */
#define MAX_WORD_LEN 15

/**
 * linked node that points to the next node and holds the char pointer for
 * the word
 **/
struct word_node
{
        const char* word;
        struct word_node *next;
};

/**
 * list header structure. holds a pointer to the head node and the length
 * of the list, in case we need that.
 **/
struct word_list
{
        struct word_node *head;
        int len;
};

/* publicly callable functions from this module */
void word_list_init(struct word_list *);

void word_list_add(struct word_list *, const char []);

void display_all(struct word_list *);
#endif
