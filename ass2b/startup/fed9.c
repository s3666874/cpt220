#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

enum direction
{
    DIR_HORIZONTAL,
    DIR_VERTICAL
};

struct move
{
    int x, y;
    enum direction dir;
};

void read_rest_of_line(void)
{
    int ch;
    while (ch = getc(stdin), ch != '\n' && ch != EOF)
            ;
    clearerr(stdin);
}

char* cleanString(char s[])
{
    int i;

    i = strlen(s)-1;

    if ( s[i] == '\n')
        s[i] = '\0';

    return s;
}

long int getint(char* str)
{
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10);

    return ret;
}

int get_string_from_keyboard(const char prompt[], char *output, int len)
{
    char *str = malloc((len+1) * sizeof(char));

    printf("%s", prompt);

    if (fgets(str, (len+1), stdin) == NULL)
        return 0;

    if (strlen(str) == 1 && str[0] == '\n')
        return 0;

    if (str[strlen(str) - 1] != '\n')
        read_rest_of_line();

    strcpy(output, cleanString(str));

    free(str);
    return 1;
}

int is_valid_move()
{
    return 0;
}


int main(void)
{
    int c=1;
    char *token;
	char prompt[1000];
    struct move themove;
    const char s[2] = ":";

    char *word = malloc(6 * sizeof(char));
    char *location = malloc(7 * sizeof(char));

    sprintf(prompt, "Please enter a word to play, at most %d characters: ", 6);

    get_string_from_keyboard(prompt, word, 6);

    sprintf(prompt, "Please enter the starting location for the word in the format x:y:d where x and\ny are the row and column the word starts and d is the direction - either h for\nhorizontal or v for vertical: ");

    get_string_from_keyboard(prompt, location, 8);

    token = strtok(location, s);

    while(token != NULL)
    {
        if (c == 1)
        {
            themove.x = getint(token);
        }
        else if (c == 2)
        {
            themove.y = getint(token);
        }
        else if (c == 3)
        {
            if (strcmp(token, "h") == 0)
            {
                themove.dir = 0;
            }
            else
            {
                themove.dir = 1;
            }
        }

        token = strtok(NULL, s);
        c++;
    }




    printf("%s [%lu]\n", word, strlen(word));
    printf("%s [%lu]\n", location, strlen(location));
    printf("%d,%d,%d\n", themove.x, themove.y, themove.dir);

    free(word);
    free(location);

	return 0;
}

