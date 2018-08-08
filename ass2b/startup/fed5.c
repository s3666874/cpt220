#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

struct player
{
	char name[30];
	int age;
};

struct game
{
	struct player* players;
	int num_players;
};

int init_player(struct player* curplayer, int playernum)
{
	if (playernum == 0)
	{
		strcpy(curplayer->name, "Federick");
		curplayer->age = 42;
	}
	else if (playernum == 1)
	{
		strcpy(curplayer->name, "Anny");
		curplayer->age = 44;
	}
	else if (playernum == 2)
	{
		strcpy(curplayer->name, "Eric");
		curplayer->age = 38;
	}
	else if (playernum == 3)
	{
		strcpy(curplayer->name, "Peter");
		curplayer->age = 75;
	}
	else if (playernum == 4)
	{
		strcpy(curplayer->name, "Shelly");
		curplayer->age = 72;
	}
	else if (playernum == 5)
	{
		strcpy(curplayer->name, "Sunshine");
		curplayer->age = 32;
	}

    return 1;
}

struct player* new_players(int num_players, struct game* thegame)
{
	int i;
	struct player *players = malloc(num_players * sizeof(struct player));

	for (i=0; i<num_players; i++)
	{
		init_player(&players[i], i);
	}

	return players;
}

void show_players(struct game *thegame)
{
	int i;

	for (i=0; i<thegame->num_players; i++)
	{
		printf("%s\n", thegame->players[i].name);
		printf("%d\n", thegame->players[i].age);
		printf("\n");
	}
}

void swap (struct player *a, struct player *b)
{
	struct player temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle_players(struct game *thegame, int n)
{
	int i,j;
	struct player temp;

    srand(time(NULL));

    for (i=n-1; i>0; i--)
    {
        j = rand() % (i+1);

        temp = thegame->players[i];
        thegame->players[i] = thegame->players[j];
        thegame->players[j] = temp;
        
        /*swap(&thegame->players[i], &thegame->players[j]);*/
    }
}


int main(void)
{
	struct game thegame;

	thegame.num_players = 6;
	thegame.players = new_players(6, &thegame);

	/* swap(&thegame.players[0], &thegame.players[1]) */

	shuffle_players(&thegame, 6);
	show_players(&thegame);


}

