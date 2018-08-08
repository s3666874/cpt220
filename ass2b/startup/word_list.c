/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "word_list.h"
#include "io.h"


void word_list_init(struct word_list *list)
{
		assert(list != NULL);

		list->head = NULL;
		list->len = 0;
}

struct word_node *new_node(const char word[])
{
		struct word_node *new = (struct word_node *) malloc(sizeof(struct word_node));

		if (!new)
		{
				perror("malloc");
				return NULL;
		}

		new->word = word;
		new->next = NULL;

		/*free(new);*/
		return new;
}


void word_list_add(struct word_list *list, const char word[])
{
		struct word_node *new = new_node(word);
		struct word_node *cursor = list->head;

		if (cursor == NULL)
		{
				list->head = new;
		}
		else
		{
				while(cursor->next != NULL)
						cursor = cursor->next;
			
				cursor->next = new;
		}

		list->len++;
}

void display_all(struct word_list *list)
{
		struct word_node *cursor = list->head;

		while(cursor != NULL)
		{
				printf("%s\n", cursor->word);

				cursor = cursor->next;
		}
}




/******************************************************************************
 * the word_list module simply keeps track of all the words in our
 * "dictionary". After loading from disk, the main purpose of this list will be
 * to check that a word exists in the dictionary. You will need to create the
 * functions for managing this list.
 *****************************************************************************/

