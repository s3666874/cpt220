#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST_H
#define TEST_H

#define MAX_WORD_LEN 15

struct word_node
{
	const char* word;
	struct word_node *next;
};

struct word_list
{
	struct word_node *head;
	int len;
};


void word_list_init(struct word_list *);

void word_list_prepend(struct word_list *, const char []);

void word_list_append(struct word_list *, const char []);

void display_all(struct word_list *);

char * upper(char *);

#endif

