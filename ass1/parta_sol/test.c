#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

enum input_result
{
        /* the i/o operation failed - this is often due to buffer overflow */
        IR_FAILURE,
        /* the i/o operation succeeded */
        IR_SUCCESS,
        /* there was a request to return to the main menu such as when quitting
           the game */
        IR_RTM
};

char* cleanString(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}

int main(void)
{
	char str[8];
	enum input_result result = IR_FAILURE;

	while(result == IR_FAILURE)
	{
		printf("Enter something: ");
		fgets(str, 7, stdin);

		if (strncmp(cleanString(str), "fed", 3) == 0)
		{
			result = IR_SUCCESS;
		}
		else
		{
			result = IR_FAILURE;
		}
	}

	printf("Found\n");
	return 0;
}


