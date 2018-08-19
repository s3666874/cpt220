/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "helpers.h"
/******************************************************************************
 * the helpers module is a great place to store functions that don't logically
 * "live" in another module.
 *****************************************************************************/

char * upper(char * temp) {
        char * name = temp;
        char *s = name;

        while (*s)
        {
                *s = toupper((unsigned char) *s);
                s++;
        }

        return name;
}

long int getint(char* str)
{
        char *ptr;
        long ret;

        ret = strtol(str, &ptr, 10);

        return ret;
}

char* cleanString(char s[])
{
        int i;

        i = strlen(s)-1;
        if ( s[i] == '\n')
        s[i] = '\0';

        return s;
}
