#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/**
 * The main function - the main entry point into your program
 **/
 /*
int main(void)
{       
        int a;
        char b[20];

        printf("Enter a number: \n");
        while (fgets(b, 1, stdin) != NULL)
        {
                printf("you entered %s\n", b);        
        }
        
        return 0;
}
*/

char * cleanString(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}

int main()
{
        char str[21];
        char *ptr;
        int i;
        long ret;

        printf("Enter a number: ");
        fgets(str, 20, stdin);

/*
        i = strlen(str)-1;
        if ( str[i] == '\n')
        str[i] = '\0';
*/
        ret = strtol(cleanString(str), &ptr, 10);

        printf("This is your number: %ld\n", ret);
        return 0;
}




/*
int main () {
        char str[30] = "whatever";
        char *ptr;
        long ret;
        int a=10;

        ret = strtol(str, &ptr, 10);

        printf("The number(unsigned long integer) is %ld\n", ret);

        if (ret > a)
        {
                printf("And it is bigger than 10\n");
        }
        else
        {
                printf("And it is smaller than 10\n");      
        }

        printf("String part is |%s|\n", ptr);

        return(0);
}
*/