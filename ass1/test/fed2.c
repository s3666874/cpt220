#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <limits.h>

char * cleanString(char s[])
{
    int i;

    i = strlen(s)-1;
    if ( s[i] == '\n')
    s[i] = '\0';

    return s;
}

int main(void)
{
	char player1[21];

	char *player1_pointer;

    printf("Please enter the name of player 1: ");
    fgets(cleanString(player1), 20, stdin);

    player1_pointer = &player1[21];

    printf("%p\n", player1_pointer);

    return 0;
}
