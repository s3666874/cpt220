#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

enum input_result
{
    IR_FAILURE,
    IR_SUCCESS,
    IR_RTM
};

struct game
{
	char name[23];
	int num_players;
};

void read_rest_of_line(void)
{
    int ch;
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
            ;
    clearerr(stdin);
}

char* cleanString(char s[])
{
    int i;

    i = strlen(s)-1;

    if (s[i] == '\n')
    	s[i] = '\0';

    return s;
}

enum input_result get_string_from_keyboard(const char prompt[], char *output, int len)
{
	char *str = malloc((len+1) * sizeof(char));

	printf("%s", prompt);
	
	if (fgets(str, (len+1), stdin) == NULL)
		return IR_RTM;

	if (strlen(str) == 1 && str[0] == '\n')
		return IR_RTM;

	if (str[strlen(str) - 1] != '\n')
		read_rest_of_line();

	strcpy(output, cleanString(str));

	return IR_SUCCESS;
}

enum input_result get_int_from_keyboard(const char prompt[], int *output, int len)
{
	char *ptr;
   	long ret;
   	int final;
	char *str = malloc((len+1) * sizeof(char));
	enum input_result result;

	result = get_string_from_keyboard(prompt, str, len);

	if (result == IR_SUCCESS)
	{
		ret = strtol(str, &ptr, 10);

		if (strlen(ptr) > 0)
		{
			return IR_FAILURE;
		}
		else
		{
			if (ret >= INT_MIN && ret <= INT_MAX)
			{
				final = ret;
				*output = final;

				return IR_SUCCESS;
			}
			else
			{
				return IR_FAILURE;
			}
		}
	}
	else
	{
		return result;
	}
}

void init_game(struct game *thegame)
{
	int *str = malloc((21) * sizeof(char));

	if (get_int_from_keyboard("How many? ", str, 1) == IR_SUCCESS)
	{
		thegame->num_players = *str;
	}
}



/*
int main(void)
{
	int *str = malloc((21) * sizeof(char));

	if (get_int_from_keyboard("Enter: ", str, 4) == IR_SUCCESS)
	{
		printf("%d\n", *str);
	}
	else
	{
		printf("\nUser quit\n");
	}

	return 0;
}
*/

/*
int main(void)
{
	char a[20];

	printf("enter: ");
	fgets(a, 5, stdin);

	printf("a: %s\n", a);
	printf("len: %lu\n", strlen(a));
	printf("a[0]: [%c]\n", a[0]);
	printf("a[1]: [%c]\n", a[1]);
	printf("a[2]: [%c]\n", a[2]);
	printf("a[3]: [%c]\n", a[3]);
	printf("a[4]: [%d]\n", a[4]);
	
	return 0;
}
*/


int main(void)
{
	struct game thegame;

	init_game(&thegame);

	printf("%d\n", thegame.num_players);

	return 0;
}


