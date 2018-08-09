#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

struct tile
{
	int letter;
	int score;
};

struct tile_list
{
	struct tile *tiles;
	int num_tiles;
	int total_tiles;
};

struct player
{
	char name[20];
	int age;
	int score;
	struct tile_list hand;
};

struct game
{
	int num_players;
	struct player *players;
	struct tile_list *tilemap;
	struct tile_list *tiledeck;
};

long int getint(char* str)
{
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10);

    return ret;
}

struct tile new_tile(int letter, int score)
{
	struct tile tile;

	tile.letter = letter;
	tile.score = score;

	return tile;
}

void shuffle_tiles(struct tile tiles[], int total_tiles)
{
	int i,j;
	struct tile temp;

	srand(time(NULL));

	for (i=total_tiles-1; i>0; i--)
	{
		j = rand() % (i+1);

		temp = tiles[i];
		tiles[i] = tiles[j];
		tiles[j] = temp;
	}
}

void init_tiles(struct tile_list *tiledeck)
{
	int i,c,t=0;
    char *copy;
    char str[8];
    char *token;
    char letter;
    int letter_count;
    int letter_score;
    const char s[2] = ",";

	struct tile *temp = malloc(100 * sizeof(struct tile));

	FILE *file;

	file = fopen("tiles.txt", "r");

	if (file)
	{
		while (fgets(str, 8, file))
		{
			copy = malloc(strlen(str)+1);
			strcpy(copy ,str);

			token = strtok(copy, s);
			c=1;

			while(token != NULL)
			{

				if (c == 1)
				{
					letter = *token;
				}
				else if (c == 2)
				{
					letter_score = getint(token);
				}
				else
				{
					letter_count = getint(token);

					for (i=0; i<letter_count; i++)
					{
						temp[t] = new_tile(letter, letter_score);
						/*printf("[%c][%d] ", letter, t);*/
						t++;
					}
				}

				token = strtok(NULL, s);
				c++;
			}

			/*printf("\n");*/
			free(copy);
		}

		fclose(file);
	}

	/*shuffle_tiles(temp, 100);*/

	tiledeck->tiles = temp;
	tiledeck->num_tiles = 0;
	tiledeck->total_tiles = 100;

	free(temp);
}

void init_players(struct player *players)
{
	int i;
	
	struct tile_list hand_1;
	struct tile_list hand_2;
	struct tile_list hand_3;

	struct tile *temp_1 = malloc(7 * sizeof(struct tile));
	struct tile *temp_2 = malloc(7 * sizeof(struct tile));
	struct tile *temp_3 = malloc(7 * sizeof(struct tile));

	hand_1.tiles = temp_1;
	hand_1.num_tiles = 0;
	hand_1.total_tiles = 7;

	hand_2.tiles = temp_2;
	hand_2.num_tiles = 0;
	hand_2.total_tiles = 7;

	hand_3.tiles = temp_3;
	hand_3.num_tiles = 0;
	hand_3.total_tiles = 7;

	for (i=0; i<3; i++)
	{
		if (i == 0)
		{
			strcpy(players[i].name, "Federick");
			players[i].age = 42;
			players[i].hand = hand_1;
		}
		else if (i == 1)
		{
			strcpy(players[i].name, "Anny");
			players[i].age = 45;
			players[i].hand = hand_2;
		}
		else if (i == 2)
		{
			strcpy(players[i].name, "Eric");
			players[i].age = 39;
			players[i].hand = hand_3;
		}

		players[i].score = 0;
	}

	free(temp_1);
	free(temp_2);
	free(temp_3);
}

void replace_letters(struct tile_list *tiledeck, struct tile_list *hand, int howmany)
{
	int i,j=0;

	for (i=0; i<howmany; i++)
	{
		hand->tiles[i] = tiledeck->tiles[i];
	}

	for (i=howmany; i<100; i++)
	{
		tiledeck->tiles[j] = tiledeck->tiles[i];
		j++;
	}
}

void print_players(struct player *players)
{
	int i;

	printf("\n\nPlayer 1\tPlayer 2\tPlayer 3\n");
	for (i=0; i<7; i++)
	{
		printf("[%c]\t\t[%c]\t\t[%c]\n", players[0].hand.tiles[i].letter, players[1].hand.tiles[i].letter, players[2].hand.tiles[i].letter);
	}
}

void print_tiles(struct tile_list *tiledeck)
{
	int i;

	for (i=0; i<100; i++)
	{
		printf("[%c] ", tiledeck->tiles[i].letter);

		if (i == 19 || i == 39 || i == 59 || i == 79)
			printf("\n");
	}
}


int main(void)
{
	struct game thegame;
	struct tile_list tiledeck;

	struct player *players = malloc(3 * sizeof(struct player));

	init_tiles(&tiledeck);
	init_players(players);

	thegame.num_players = 3;
	thegame.tiledeck = &tiledeck;
	thegame.players = players;

	print_tiles(&tiledeck);

	print_players(players);

	replace_letters(&tiledeck, &players[0].hand, 7);

	print_players(players);
}




