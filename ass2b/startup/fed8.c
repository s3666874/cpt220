#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#define MAX_TILES 10

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

struct tile new_tile(int letter, int score)
{
	struct tile temp;

	temp.letter = letter;
	temp.score = score;

	return temp;
}

void remove_tile(struct tile_list *tilemap, int howmany)
{
	int i,j=0;

	for (i=howmany; i<MAX_TILES; i++)
	{
		tilemap->tiles[j] = tilemap->tiles[i];
		j++;
	}
}

void print_tiles(struct tile_list *tilemap)
{
	int i;

	for (i=0; i<MAX_TILES; i++)
	{
		printf("%c [%d]\n", tilemap->tiles[i].letter, i);
	}
}

int main(void)
{
	struct tile_list tilemap;
	struct tile *temp = malloc(MAX_TILES * sizeof(struct tile));

	temp[0] = new_tile('A', 0);
	temp[1] = new_tile('B', 0);
	temp[2] = new_tile('C', 0);
	temp[3] = new_tile('D', 0);
	temp[4] = new_tile('E', 0);
	temp[5] = new_tile('F', 0);
	temp[6] = new_tile('G', 0);
	temp[7] = new_tile('H', 0);
	temp[8] = new_tile('I', 0);
	temp[9] = new_tile('J', 0);

	tilemap.tiles = temp;
	tilemap.num_tiles = 0;
	tilemap.total_tiles = MAX_TILES;

	print_tiles(&tilemap);
	remove_tile(&tilemap, 2);
	printf("\n");
	print_tiles(&tilemap);
}

