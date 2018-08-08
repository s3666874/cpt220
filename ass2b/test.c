#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct matrix
{
    int ** array;
    unsigned width, height;
};

char * cleanString(char s[])
{
    int i;

    i = strlen(s)-1;
    if ( s[i] == '\n')
    s[i] = '\0';

    return s;
}

int main(int argc, char* argv[])
{
/*
	unsigned seed;

	sscanf(argv[1], "%d", &seed);

	srand(seed);

	printf("%u\n", seed);
	printf("%d\n", rand());
*/

	char a[10];

	printf("enter: ");
	fgets(a, 5, stdin);

	printf("%lu\n", strlen(a));
	printf("%s", a);
	printf("[%c]\n", a[4]);
	printf("[%c]\n", a[5]);
	printf("[%c]\n", a[6]);

/*
	unsigned seed;

	if (argc != 3 && argc != 4)
	{
		printf("Invalid number of arguments\n");
		return EXIT_FAILURE;
	}

	printf("Welcome to Scrabble\n");
	printf("-------------------\n");

	if (argc == 4)
	{		
		sscanf(argv[3], "%d", &seed);
	}
	else
	{
		seed = time(NULL);
		
	}

	srand(seed);

	printf("Using seed: %u\n", seed);
*/
	return EXIT_SUCCESS;
}

