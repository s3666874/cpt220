/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "helpers.h"
/******************************************************************************
 * the helpers module is a great place to store functions that don't logically
 * "live" in another module.
 *****************************************************************************/

/**
 * duplicates a string to new memory using malloc. This is based on the
 * function available in c99.
 **/
char* strdup(const char orig[])
{
        /* allocates memory */
        char* copy = malloc((strlen(orig) + 1) * sizeof(char));
        if (!copy)
        {
                return NULL;
        }
        /* do the copy */
        return strcpy(copy, orig);
}

/**
 * finds how many of the specified needle char exists in the string haystack
 **/
int count_char(const char haystack[], char needle)
{
        const char* find;
        int charcount = 0;
        const char* rest;
        int len = strlen(haystack);

        rest = haystack;

        /* find the first char */
        find = strchr(rest, needle);
        /* if one is not found at all, return 0 as none where found */
        if (!find)
        {
                return 0;
        }
        /* increment the pointer so we are searching over the rest of the
         * string
         */
        rest = ++find;
        /* continue to search over the rest of the string until there are
         * no further instances of the char specified */
        while (find && find - haystack < len)
        {
                ++charcount;
                find = strchr(rest, needle);
                if (!find)
                {
                        break;
                }
                rest = ++find;
        }
        return charcount;
}

/**
 * extracts an integer from a string
 **/
BOOLEAN strtoint(const char input[], int* output)
{
        char* end;
        long lout;
        /* try to extract a long from a string */
        lout = strtol(input, &end, DECIMAL);
        /* if there is leftover data in the string this is not a valid number */
        if (*end)
        {
                error_print("Error: %s is not numeric.\n", input);
                return FALSE;
        }
        /* if the number is out of the allowed range, reject the result */
        if (lout < INT_MIN || lout > INT_MAX)
        {
                error_print("Error: %s is not within the range of an int.\n",
                            input);
                return FALSE;
        }
        /* all good so store the result */
        *output = lout;
        return TRUE;
}

/**
 * inserts a newline char at the last whitespace char before the nth
 * character (in this case linelen specifies this
 **/
char* fold(char input[], int linelen)
{
        char* end = input + strlen(input);
        char* curr = input;
        /* jump ahead by linelen chars */
        curr += linelen;
        /* search backwards until we find a whitespace char. There is a bug
         * here in that if there are no whitespace chars in prior to the start
         * of the line this function will result in an infinite loop
         */
        while (curr < end)
        {
                while (!isspace(*curr))
                {
                        curr--;
                }
                *curr++ = '\n';
                curr += linelen;
        }
        return input;
}

/**
 * does an inplace conversion to upper case of each char in word
 **/
char* strtoupper(char* word)
{
        char* iter = word;
        while (*iter)
        {
                *iter = toupper(*iter);
                ++iter;
        }
        return word;
}
/**
 * does an inplace conversion to lower case of each char in word
 **/
char* strtolower(char* word)
{
        char* iter = word;
        /* iterate over each char and convert it to lower case */
        while (*iter)
        {
                *iter = tolower(*iter);
                ++iter;
        }
        return word;
}

/**
 *  splits the string passed in into substrings at each occurence of a char in
 * delims. The expected parameter specified how many tokens are expected.
 * Please note that both the char ** return value and each of the elements held
 * in that array is also malloced. It is the responsibility of the code that
 * recieves this return value to free all the memory allocated.
 **/
char** tokenize(const char line[], const char delims[], int expected)
{
        char** token_list;
        char* tok;
        char* linecpy;
        int tokens_seen = 0;
        int count_test, delim_counter;
        int len;

        assert(expected > 0);
        /* grab the length of the string so we don't have to call it multiple
         * times
         */
        len = strlen(delims);
        /* count_test checks that the numnber of delimiters matches the number
         * expected
         */
        count_test = 0;
        for (delim_counter = 0; delim_counter < len; ++delim_counter)
        {
                int count = count_char(line, delims[delim_counter]);
                if (count > 0)
                {
                        count_test += count;
                }
        }
        /* the number of tokens is one more than the delimiters */
        ++count_test;

        if (count_test != expected)
        {
                error_print(
                    "Error: %s does not have the right number of delimiters.\n",
                    line);
                return NULL;
        }

        /* allocate the space for the array of strings */
        token_list = (char**)malloc(sizeof(char*) * (expected));
        if (!token_list)
        {
                return NULL;
        }

        /* make a copy of the line as strtok modifies the line passed into it */
        linecpy = strdup(line);
        if (!linecpy)
        {
                perror("memory allocation");
                free(token_list);
                return NULL;
        }
        /* grab the first token */
        tok = strtok(linecpy, delims);
        while (tok)
        {
                /* allocate memory and copy the string */
                char* tokcpy = strdup(tok);
                if (!tokcpy)
                {
                        free_tokens(token_list, tokens_seen);
                        return NULL;
                }
                /* insert it into the array */
                token_list[tokens_seen++] = tokcpy;
                /* get the next token */
                tok = strtok(NULL, delims);
        }
        /* free the line */
        free(linecpy);
        return token_list;
}

/**
 * frees each token allocated by the tokenize() function as well as the tokens
 * pointer itself.
 **/
void free_tokens(char** tokens, int len)
{
        int count;

        assert(len > 0);
        assert(tokens);
        /* free each token */
        for (count = 0; count < len; ++count)
        {
                free(tokens[count]);
        }
        /* free the token ponter */
        free(tokens);
}
