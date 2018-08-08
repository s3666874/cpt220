/*
*	File		: linkedlist.c
*	Author		: Federick Kwok
*	Purpose		: To demonstrate and understand how linked list work in C
*	Remarks		: This is a clone of the code from zentut.com (http://www.zentut.com/c-tutorial/c-linked-list/)
*/
#include <stdio.h>
#include <stdlib.h>


/* The struct def of a node */
typedef struct node 
{
	int data;
	struct node* next;
} node;

typedef void (*callback)(node* data);


void node_init(node *node)
{
	node = NULL;
}


/* 
	Creating a new node 
	Initialize the data and the next field

	Return the newly created node
*/
node* create(int data, node* next)
{
	node* new_node = (node*) malloc(sizeof(node));

	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		return 0;
	}

	new_node->data = data;
	new_node->next = next;

	return new_node;
}


/* 
	Add an element to the start of list by
	1. pointing the next pointer of the new node to the head pointer 
	2. point the head pointer to the new node
 */
node* prepend(node* head, int data)
{
	node* new_node = create(data, head);
	head = new_node;

	return head;
}


/* Adding a new node to the end of the list */
node* append(node* head, int data)
{
	node *cursor = head;
	node* new_node = create(data, NULL);
	
	if (head == NULL)
	{
		head = new_node;
	}
	else
	{
		while(cursor->next != NULL)
			cursor = cursor->next;

		cursor->next = new_node;
	}

	return head;
}

node* append2(node* head, int data)
{
	/* go to the last node */
	node *cursor = head;

	/* create the new node */
	node* new_node = create(data, NULL);

	/* return NULL if the head is empty */
	if (head == NULL)
		return NULL;

	/* traverse until the cursor (next) is NULL */
	while(cursor->next != NULL)
		cursor = cursor->next;

	/* set the next node to be the new node */
	cursor->next = new_node;

	return head;
}


/* Adding a node after a particular node in the list */
node* insert_after(node *head, int data, node* prev)
{
	/* find the prev node, starting from the first node (head) */
	node *cursor = head;

	if (head == NULL || prev == NULL)
		return NULL;

	while(cursor != prev)
	{
		cursor = cursor->next;
	}

	if (cursor != NULL)
	{
		node* new_node = create(data, cursor->next);
		cursor->next = new_node;
		return head;
	}
	else
	{
		return NULL;
	}
}


/* Adding a node before a particular node in the list */
node* insert_before(node *head, int data, node* nxt)
{
	/* find the prev node, starting from the first node */
	node *cursor = head;

	/* Do nothing if either the current head of the list or the node we are putting the new node in front of is empty */
	if (nxt == NULL || head == NULL)
	{
		return NULL;
	}

	/* If we want to put the new node in front of the first node. Just call prepend() */
	if (head == nxt)
	{
		head = prepend(head, data);
		return head;
	}

	while(cursor != NULL)
	{
		if (cursor->next == nxt)
			break;

		cursor = cursor->next;
	}

	if (cursor != NULL)
	{
		node* new_node = create(data,cursor->next);
		cursor->next = new_node;
		return head;
	}
	else
	{
		return NULL;
	}
}


/* traverse the list to get the data at each element */
void traverse(node* head, callback f)
{
	node* cursor = head;

	while(cursor != NULL)
	{
		f(cursor);
		cursor = cursor->next;
	}
}


/* remove the first node from the list */
node* remove_front(node* head)
{
	node *front = head;

	if (head == NULL)
		return NULL;

	head = head->next;
	front->next = NULL;

	/* is this the last ndoe in the list */
	if (front == head)
		head = NULL;

	free(front);

	return head;
}



/* remove the last node in the list */
node* remove_back(node* head)
{
	node *cursor = head;
	node *back = NULL;

	if (head == NULL)
		return NULL;

	while(cursor->next != NULL)
	{
		back = cursor;
		cursor = cursor->next;
	}

	if (back != NULL)
		back->next = NULL;

	/* if this is the last node in the list */
	if (cursor == head)
		head = NULL;

	free(cursor);

	return head;
}


/* remove any node in the list */
node* remove_any(node* head, node* nd)
{
	/* if the node the be removed is in the middle */
	node* cursor = head;

	if (nd == NULL)
		return NULL;

	/* if the node to be removed is the first node then just call remove_front() */
	if (nd == head)
		return remove_front(head);

	/* if the node to be removed is the last node then just call remove_back() */
	if (nd->next == NULL)
		return remove_back(head);

	while(cursor != NULL)
	{
		if (cursor->next == nd)
			break;

		cursor = cursor->next;
	}

	if (cursor != NULL)
	{
		node* tmp = cursor->next;
		cursor->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}

	return head;
}


/* display a node */
void display(node* n)
{
	if (n != NULL)
	{
		printf("%d\n", n->data);
	}
}


/* display the whole list */
void display_all(node* head)
{
	node *cursor = head;

	while(cursor != NULL)
	{
		printf("%d\n", cursor->data);

		cursor = cursor->next;
	}
}



/* Search for a node */
node* search(node* head, int data)
{
	node *cursor = head;

	while(cursor != NULL)
	{
		if (cursor->data == data)
			return cursor;

		cursor = cursor->next;
	}

	return NULL;
}



/* remove all the nodes from the list */
void remove_all(node *head)
{
	node *cursor, *tmp;

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


/* count how many elements in the list */
int count(node *head)
{
	node *cursor = head;
	int c = 0;

	while(cursor != NULL)
	{
		c++;
		cursor = cursor->next;
	}

	return c;
}



/* sort the linked list */
node* insertion_sort(node* head)
{
	node *x, *y, *e;

	x = head;

	while(x != NULL)
	{
		e = x;
		x = x->next;

		if (head != NULL)
		{
			if (e->data > head->data)
			{
				y = head;

				while((y->next != NULL) && (e->data > y->next->data))
				{
					y = y->next;
				}

				e->next = y->next;
				y->next = e;
			}
			else
			{
				e->next = head;
				head = e;
			}
		}
		else
		{
			e->next = NULL;
			head = e;
		}
	}

	return head;
}



/* reverse the linked list */
node* reverse(node* head)
{
	node* prev = NULL;
	node* current = head;
	node* next;

	while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	head = prev;
	return head;
}



/* display menu */
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



int main(void)
{
	int command = 0;
	int data;


	node* head = NULL;
	node* tmp = NULL;
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

			/* prepend() */
			case 1:
				printf("Please enter a number to prepend: ");
				scanf("%d", &data);
				head = prepend(head,data);
				traverse(head, disp);
				break;

			/* append() */
			case 2:
				printf("Please enter a number to append: ");
				scanf("%d", &data);
				head = append(head,data);
				traverse(head, disp);
				break;

			/* search() */
			case 3:
				printf("Please enter a number to search: ");
				scanf("%d", &data);
				tmp = search(head,data);
				if (tmp != NULL)
				{
					printf("Element with value %d found.", data);
				}
				else
				{
					printf("Element with value %d not found.", data);
				}
				break;

			/* insert_after() */
			case 4:
				printf("Please enter the element value where you want to insert after: ");
				scanf("%d", &data);
				tmp = search(head,data);
				if (tmp != NULL)
				{
					printf("Please enter the number you want to add.");
					scanf("%d", &data);
					head = insert_after(head,data,tmp);
					if (head != NULL)
						traverse(head,disp);
				}
				else
				{
					printf("Element with value %d not found.", data);
				}
				break;

			/* insert_before */
			case 5:
				printf("Please enter the element value where you want to insert before: ");
				scanf("%d", &data);
				tmp = search(head,data);
				if (tmp != NULL)
				{
					printf("Please enter the number you want to add.");
					scanf("%d", &data);
					head = insert_before(head,data,tmp);
					if (head != NULL)
						traverse(head,disp);
				}
				else
				{
					printf("Element with value %d not found.", data);
				}
				break;

			/* remove_front */
			case 6:
				head = remove_front(head);
				if (head != NULL)
					traverse(head,disp);
				break;

			/* remove_back */
			case 7:
				head = remove_back(head);
				if (head != NULL)
					traverse(head,disp);
				break;

			/* remove_any */
			case 8:
				printf("Please enter element value to remove: ");
				scanf("%d", &data);
				tmp = search(head,data);
				if (tmp != NULL)
				{
					remove_any(head,tmp);
					if (head != NULL)
						traverse(head,disp);
				}
				else
				{
					printf("Element with value %d not found.", data);
				}
				break;

			/* insertion_sort */
			case 9:
				head = insertion_sort(head);
				if (head != NULL)
					traverse(head,disp);
				break;

			/* reverse */
			case 10:
				head = reverse(head);
				if (head != NULL)
					traverse(head,disp);
				break;

			/* display_all */
			case 11:
				display_all(head);
				break;
		}
	}

	remove_all(head);
	return 0;
}




