#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_node
{
	char word;
	struct word_node* next;
} word_node;

typedef void (*callback)(word_node* word);


word_node* create(char* word, word_node* next)
{
	word_node* new_node = (word_node*) malloc(sizeof(word_node));

	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		return 0;
	}

	new_node->word = word;
	new_node->next = next;

	return new_node;
}

word_node* prepend(word_node* head, char* word)
{
	word_node* new_node = create(word, head);
	head = new_node;

	return head;
}

void traverse(word_node* head, callback f)
{
	word_node* cursor = head;

	while(cursor != NULL)
	{
		f(cursor);
		cursor = cursor->next;
	}
}

void display(word_node* n)
{
	if (n != NULL)
	{
		printf("%s\n", n->word);
	}
}


void remove_all(word_node *head)
{
	word_node *cursor, *tmp;

	if (head != NULL)
	{
		cursor = head->next;
		head->next = NULL;

		while(cursor != NULL)
		{
			tmp = cursor->next;
			free(cursor);
			cursor = tmp;
		}
	}
}

void menu()
{
	printf("----------- C Linked List Demo -----------\n\n");
	printf("0. menu\n");
	printf("1. Prepend a node\n");
	printf("2. Append a node\n");
	printf("3. Search for a node\n");
	printf("4. Insert after a node\n");
	printf("5. Insert before a node\n");
	printf("6. Remove first node\n");
	printf("7. Remove last node\n");
	printf("8. Remove any node\n");
	printf("9. Sort the list\n");
	printf("10. Reverse the list\n");
	printf("11. Display the whole list\n");
	printf("-1. Quit\n");
}

void display_all(word_node* head)
{
	word_node *cursor = head;

	while(cursor != NULL)
	{
		printf("%s\n", cursor->word);

		cursor = cursor->next;
	}
}

int main(void)
{
	int command = 0;
	char word[22];

	word_node* head = NULL;
	callback disp = display;
	
	menu();

	while(1)
	{
		printf("\nEnter a command (0-10, -1 to quit): ");
		scanf("%d", &command);

		if (command == -1)
			break;

		switch(command)
		{
			case 0:
				menu();
				break;

			case 1:
				printf("Please enter a word to prepend: ");
				scanf("%s", word);

	        	head = prepend(head,word);

				traverse(head, disp);
				
				break;

			case 11:
				display_all(head);
				break;
		}
	}

	remove_all(head);
	return 0;
}

