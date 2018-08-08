#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMARGS 2
#define LINELEN 80
#define EXTRASPACES 2

typedef enum
{
        FALSE,
        TRUE
} BOOLEAN;

enum arg_position
{
    INPUT=1, OUTPUT=2
};

FILE * gropen(char * fname)
{
    FILE * fp;
    if((fp = fopen(fname, "r")) == NULL)
    {
        perror("failed to open file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

BOOLEAN read_file(FILE * in, char * lines[][LINELEN + 1], int * num_lines)
{
    /* count of how many lines have been read in so far */
    int line_count=0;

    /* a buffer to read each line into */
    char line[LINELEN + EXTRASPACES];

    /* read each line in */
    while(fgets(line, LINELEN + EXTRASPACES, in) != NULL)
    {
        /* check there was no leftover input in the buffer */
        if(line[strlen(line)-1] != '\n')
        {
            fprintf(stderr, "Error: line is too long reading from file.\n");
            return FALSE;
        }

        /* remove the newline as it has served its purpose */
        line[strlen(line)-1]='\0';

        /* copy each line into the array where it will be stored */
        strcpy(*lines[line_count++], line);
    }

    /* store how many lines have been read */
    *num_lines = line_count;

    return TRUE;
}

BOOLEAN test(int *p)
{
	int a=12;
	*p = a;
	return TRUE;
}


int main(int argc, char* argv[])
{
    int a=0;
    int *p;

    p=&a;

/*
    FILE* in;
	char lines[BUFSIZ][LINELEN + 1];
	char *lines = malloc(sizeof(char) * (LINELEN+1));
	int line_count;

	in = gropen(argv[INPUT]);

	if (!read_file(in, lines, &line_count))
    {
    	printf("error");
    	return EXIT_FAILURE;
    }
    
    printf("%d\n", line_count);
    printf("%s\n", lines[5]);
*/

    /*test(&a);*/
    printf("Name \t Value\n");
    printf("a \t %d\n", a);
    printf("&a \t %p\n", (void *) &a);
    printf("p \t %p\n", (void *) p);
    printf("*p \t %d\n", *p);


/*
    while(fgets(line, LINELEN + EXTRASPACES, in) != NULL)
    {
    	if (line[strlen(line)-1] == '\n')
    	{
    		printf("[got newline] ");
    		line[strlen(line)-1]='\0';
    	}


    	printf("%s [%lu]\n", line, strlen(line));
    	strcpy(lines[line_count++], line);
    }

    printf("\n\n%d\n", line_count);
*/
    return EXIT_SUCCESS;
}

