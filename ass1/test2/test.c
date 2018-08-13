#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef enum
{
	summer, autumn, winter, spring
} season;

void printPhrase(season s);

int main(void)
{
/*
	int a = 1025;
	int *p;
	p = &a;

	printf("Address: %p, Value: %d\n", p, *p);
	printf("Address: %p, Value: %d\n", p+1, *(p+1));

	char *p0;
	p0 = (char*)p;

	printf("Address: %p, Value: %d\n", p0, *p0);
	printf("Address: %p, Value: %d\n", p0+1, *(p0+1));
*/

	/*printPhrase(3);*/
	srand(time(NULL));

	int count;
	int token;

	token = rand() % 2 + 1;

	 for (count = 0; count < 2; ++count)
	 {
	 	++token;
	 	printf("Count: %d, Token: %d\n", count, token);
	 }

	return 0;
}


void printPhrase(season s)
{
	if (s == summer)
		printf("Its summer\n");
	else if (s == autumn)
		printf("Its autumn\n");
	else if (s == winter)
		printf("Its winter\n");
	else if (s == spring)
		printf("Its spring\n");
}