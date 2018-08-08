#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fed(int * num)
{
	*num = 3;
}

char * strdup(const char * word)
{
	char * new;
	new = (char *) malloc((strlen(word) + 1) * sizeof(char));

	if (!new)
	{
		perror("strdup");
		return NULL;
	}

	strcpy(new, word);
	return new;
}

int main(void)
{
/*
	int a = 2;
	int *p;

	p = &a;

	*p = 23;

	printf("a: %d\n", a);
	printf("*p: %d\n", *p);
	printf("&a: %p\n", (void *) &a);
	printf("p: %p\n", (void *) p);
*/

/*
	char * name = strdup("Fed");

	printf("%s\n", name);
	free(name);
*/


	int i = 10;
    int j = 20;
    int *ptr = &i;        
    printf("*ptr: %d\n", *ptr);
  
    
    ptr = &j;
    printf("*ptr: %d\n", *ptr);
  
    
    *ptr = 100;
    printf("*ptr: %d\n", *ptr);

    printf("j: %d\n", j);

	return 0;
}
