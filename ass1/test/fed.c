#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* cleanString(char s[])
{
    int i;

    i = strlen(s)-1;
    if ( s[i] == '\n')
    s[i] = '\0';

    return s;
}

void read_rest_of_line(void)
{
    int ch;
    /* read each char in the input buffer until we run out of chars to read
     */
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
            ;
    /* clear the error status on the stdin FILE pointer */
    clearerr(stdin);
}

int main(void)
{
    int tuna = 19;
    char str[3];
    char *ptr;
    long ret=0;

/*
    printf("tuna: %d\n", tuna);
    printf("&tuna: %p\n", &tuna);
    printf("*&tuna: %d\n", *&tuna);
	printf("tuna: %d\n", tuna);

    *&tuna = 23;
    printf("tuna: %d\n", tuna);
*/
    
    printf("Please enter something: ");
    fgets(str, 3, stdin);

    if (str[strlen(str) - 1] != '\n')
    {
        read_rest_of_line();
    }
    else
    {
        ret = strtol(cleanString(str), &ptr, 10);
    }

    printf("%ld\n", ret);

    return 0;
}
