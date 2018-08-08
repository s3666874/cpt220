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

struct player
{
	int age;
	char name[22];
	struct game* thegame;
};

struct game
{
	struct player* players;
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

    if ( s[i] == '\n')
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


/**
 * Initialise the data for a player. this includes prompting for the name
 * of a player, and filling the starting hand for the using from the tile
 * deck, as well as setting the color and the game pointer and set the score to
 * 0.
 **/
void init_player(struct player* curplayer, int playernum, struct game* thegame)
{
	char *str = malloc((21) * sizeof(char));
	char prompt[1000];

	sprintf(prompt, "Enter the name of player %d: ", (playernum+1));

	get_string_from_keyboard(prompt, str, 21);

	strcpy(curplayer->name, str);
	curplayer->age = 23;
	curplayer->thegame = thegame;
}

/**
 * allocates a players array of the size specified. It allocates a random color
 * for each player and then calls init_player() on each player, passing in the
 * required arguments
 **/
struct player* new_players(int num_players, struct game* thegame)
{
	int i;
	struct player *players = malloc(num_players * sizeof(struct player));

	for (i=0; i<num_players; i++)
	{
		init_player(&players[i], i, thegame);
	}

	return players;
}

void init_game(struct game *thegame)
{
	int *str = malloc((21) * sizeof(char));

	if (get_int_from_keyboard("How many? ", str, 1) == IR_SUCCESS)
	{
		thegame->num_players = *str;
		thegame->players = new_players(*str, thegame);
	}
}


int main(void)
{
	struct game thegame;

	init_game(&thegame);

	printf("%d\n", thegame.num_players);
	printf("%s\n", thegame.players[0].name);
	printf("%s\n", thegame.players[1].name);
	printf("%s\n", thegame.players[2].name);
	printf("%s\n", thegame.players[3].name);

	return 0;
}

