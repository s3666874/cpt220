/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "player.h"
#include "game.h"
#include <time.h>

/******************************************************************************
 * the player module manages the player struct. There are required functions
 * provided such as new_players(), init_player(), take_turn(),
 * shuffle_players(), player_sort() and some comparison functions for players.
 * You should add additional functions for managing of players if you need to.
 *****************************************************************************/

BOOLEAN is_color_available(int used_colors[], enum color curcolor)
{
		int i;

		for (i=0; i<6; i++)
		{
				if (curcolor == used_colors[i])
				{
						return FALSE;
						break;
				}
		}

		return TRUE;
}

enum color get_next_available_color(int used_colors[])
{
		enum color color;

		srand(time(NULL));

		while (color = rand() % 8, color == C_INVALID || !is_color_available(used_colors, color))
				;

		return color;
}


/**
 * allocates a players array of the size specified. It allocates a random color
 * for each player and then calls init_player() on each player, passing in the
 * required arguments
 **/
struct player* new_players(int num_players, struct game* thegame,
                           enum input_result* status)
{
        int i;
        enum color color;
        int used_colors[6];
		struct player *players = malloc(num_players * sizeof(struct player));

		srand(time(NULL));

		for (i=0; i<num_players; i++)
		{
				color = get_next_available_color(used_colors);
				init_player(&players[i], i, color, thegame);
				used_colors[i] = color;
		}

		/* Shuffle players */
		shuffle_players(players, num_players);

		/*free(players);*/
		return players;
}

/**
 * Initialise the data for a player. this includes prompting for the name
 * of a player, and filling the starting hand for the using from the tile
 * deck, as well as setting the color and the game pointer and set the score to
 * 0.
 **/
enum input_result init_player(struct player* curplayer, int playernum,
                              enum color color, struct game* thegame)
{
        char *str = malloc((21) * sizeof(char));
		char prompt[1000];

		sprintf(prompt, "Please enter the name of player %d: ", (playernum+1));

		get_string_from_keyboard(prompt, str, 21);

		strcpy(curplayer->name, str);

		curplayer->score = 0;
		curplayer->color = color;
		curplayer->thegame = thegame;

		free(str);
        return IR_SUCCESS;
}

/**
 * This is the function that implements each player turn. Firstly, the word to
 * player is prompted for - the word cannot be any longer than the width of
 * the board, of course. Display the board, prompt for the coordinates of
 * the move in the form of x:y:d where x and y are the starting coordinates of
 * the word and d is the dimension of the word - either h or v (case
 * insensitive). It must be apparent from the prompt the name and color of the
 * player who is taking the current turn.
 *
 * Next, use the functions implemented in the rules module to validate
 * and apply the changes to the board.
 **/
enum input_result take_turn(struct player* curplayer, BOOLEAN isfirst)
{
		char a[20];
		const struct board *theboard;

		theboard = &curplayer->thegame->theboard;

		display_board(theboard);

		printf("It is %s's turn, their current score is %d, and their current hand is:\n", curplayer->name, curplayer->score);
		fgets(a, 19, stdin);


        /* you'll need to allocate and free this on every turne */
        return IR_SUCCESS;
}


void swap (struct player *a, struct player *b)
{
        struct player temp = *a;
        *a = *b;
        *b = temp;
}

/**
 * shuffle the player so they are ordered in a different order to the order
 * they were entered as part of initialisation
 **/
void shuffle_players(struct player players[], int num_players)
{
		int i,j;
		struct player temp;

		srand(time(NULL));

		for (i=num_players-1; i>0; i--)
		{
				j = rand() % (i+1);

				temp = players[i];
		        players[i] = players[j];
		        players[j] = temp;
		}
}

/**
 * sorts the players in the player list in some order
 **/
void player_sort(struct player* players, int num_players,
                 int (*cmp)(const struct player*, const struct player*))
{
}

/**
 * when finalising the scores, players are sorted by score from top to bottom
 * to print out at the end of a game
 **/
int player_cmp(const struct player* first, const struct player* second)
{
        return EOF;
}

/**
 * in the random shuffle, we randomly "sort" elements according to the result
 * returned from rand()
 **/
int player_shuffle_cmp(const struct player* first, const struct player* second)
{
        return EOF;
}

void print_players(struct player *players, int num_players)
{
		int i;

		printf("\n");
		
		for (i=0; i<num_players; i++)
        {
                printf("Player %d\n", i+1);
                printf("%s\n", players[i].name);
                printf("%d\n", players[i].color);
                printf("\n");
        }
}



