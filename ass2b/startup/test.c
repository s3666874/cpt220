#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* cleanString(char s[])
{
    int i;

    i = strlen(s)-1;

    if (s[i] == '\n')
    	s[i] = '\0';

    return s;
}

void word_list_init(struct word_list *list)
{
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

	return new;
}


void word_list_prepend(struct word_list *list, const char word[])
{
	struct word_node *new = new_node(word);

	if (list->head != NULL)
		new->next = list->head;

	list->head = new;
	list->len++;
}

void word_list_append(struct word_list *list, const char word[])
{

	struct word_node *new = new_node(word);
	struct word_node *cursor = list->head;

	if (list->head == NULL)
	{
		list->head = new;
	}
	else
	{
		while(cursor->next != NULL)
		{
			cursor = cursor->next;
		}
		
		cursor->next = new;
	}

	list->len++;
}

void display_all(struct word_list *list)
{
	int c=1;
	struct word_node *cursor = list->head;

	while(cursor != NULL)
	{
		printf("%d: %s", c, cursor->word);

		if (cursor->word == list->head->word)
			printf(" (head)");

		printf("\n");

		cursor = cursor->next;
		c++;
	}
}

char * upper(char * temp) {
	char * name = temp;
	char *s = name;

	while (*s)
	{
		*s = toupper((unsigned char) *s);
		s++;
	}

	return name;
}

/* Populating the linked list manually */
/*
int main(void)
{
	struct word_list wordlist;

	word_list_init(&wordlist);

    word_list_prepend(&wordlist, "Federick");
    printf("\n");
    
    word_list_prepend(&wordlist, "Eric");
    printf("\n");

    word_list_prepend(&wordlist, "Anny");
    printf("\n");

    word_list_prepend(&wordlist, "Peter");
    printf("\n");

	return 0;
}
*/

/* Reading from file */
/*
int main(int argc, char* argv[])
{
	char str[MAX_WORD_LEN+1];

	FILE *file;

	if (argc != 2)
    {
		printf("Invalid number of arguments\n");
		return 0;
    }


    file = fopen(argv[1], "r");

	if (file) {
		while (fgets(str, (MAX_WORD_LEN+1), file))
		{
			printf("%s\n", upper(cleanString(str)));
		}

		fclose(file);
	}
	else
	{
		printf("Bad filename\n");
		return 0;
	}

	return 1;
}
*/

/* Combining all functions */

int main(int argc, char* argv[])
{
	char str[MAX_WORD_LEN+1];
	char *copy = malloc(strlen(str)+1);
	struct word_list wordlist;

	FILE *file;

	word_list_init(&wordlist);

	if (argc != 2)
    {
		printf("Invalid number of arguments\n");
		return 0;
    }

    file = fopen(argv[1], "r");

	if (file) {
		while (fgets(str, (MAX_WORD_LEN+1), file))
		{
			copy = malloc(strlen(str)+1);
			strcpy(copy ,str);
			word_list_append(&wordlist, upper(cleanString(copy)));
		}

		fclose(file);
	}
	else
	{
		printf("Bad filename\n");
		return 0;
	}

	display_all(&wordlist);

	return 1;
}

