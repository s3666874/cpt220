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
    struct tile* tiles;
    int num_tiles;
    int total_tiles;
};

struct game
{
	struct tile_list *tiledeck;
	int num_players;
};


char* cleanString(char s[])
{
    int i;

    i = strlen(s)-1;

    if (s[i] == '\n')
    	s[i] = '\0';

    return s;
}

struct tile new_tile(int letter, int score)
{
	struct tile tile;

	tile.letter = letter;
	tile.score = score;

	return tile;
}

long int getint(char* str)
{
	char *ptr;
	long ret;

	ret = strtol(str, &ptr, 10);

	return ret;
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

int load_scores(const char fname[], struct tile_list* fulllist)
{
	int i,c,t=0;
	char *copy;
	char str[9];
	char *token;
	char letter;
	int letter_count;
	int letter_score;
	const char s[2] = ",";

	struct tile *temp = malloc(100 * sizeof(struct tile));

	FILE *file;

	file = fopen(fname, "r");

	if (file) 
	{
		while (fgets(str, 9, file))
		{
			copy = malloc(strlen(str)+1);
			strcpy(copy ,str);

			printf("%s\t", cleanString(copy));

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
						printf("[%c][%d][%d] ", letter, letter_score, t);
						t++;
					}
				}

				token = strtok(NULL, s);
				c++;
			}

			printf("\n");
			free(copy);
		}

		fclose(file);
	}
	else
	{
		return 0;
	}

	shuffle_tiles(temp, 100);

	fulllist->tiles = temp;
	fulllist->num_tiles = 0;
	fulllist->total_tiles = 100;

	free(temp);
	return 1;
}

int init_game(struct game *thegame, const char tile_file[])
{
	int i;
	struct tile_list fulllist;

	load_scores(tile_file, &fulllist);

	thegame->tiledeck = &fulllist;
/*
	printf("\n");
	
	for (i=0; i<100; i++)
	{
		printf("%c ", thegame->tiledeck->tiles[i].letter);

		if (i == 20 || i == 40 || i == 60 || i == 80)
			printf("\n");
	}

	printf("\n");
*/
	return 0;
}


int main(int argc, char* argv[])
{
	int i;
	struct game thegame;

	if (argc != 2)
    {
		printf("Invalid number of arguments\n");
		return 0;
    }

	init_game(&thegame, argv[1]);

/*
	printf("%d ", thegame.tiledeck->num_tiles);
	printf("\n");

	for (i=0; i<100; i++)
	{
		printf("%c ", thegame.tiledeck->tiles[i].letter);

		if (i == 20 || i == 40 || i == 60 || i == 80)
			printf("\n");

	}

	printf("\n");
*/
	return 0;
}

