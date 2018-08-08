/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "tile_list.h"
#include <time.h>

/******************************************************************************
 * the tile list module manages the tile list which might behave like a tile map
 * (mapping between a letter and a score) or it might be a list which that can
 * be added to or deleted from (such as a tile deck or tile hand). You are
 *required to create the functions for this list.
 *****************************************************************************/

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


