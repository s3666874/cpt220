/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "scrabble.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * the scrabble module contains the main function and any helper functions to
 * kick start the program and clean up at the end.
 *****************************************************************************/
int main(int argc, char* argv[])
{
        unsigned seed;
        
        struct word_list wordlist;

        /* validate command line argments */
        if (argc != 3 && argc != 4)
        {
                printf("Invalid number of arguments\n");
                return EXIT_FAILURE;
        }

        /* display a welcome message */
        printf("Welcome to Scrabble\n");
        printf("-------------------\n");

        /* extract the seed */
        if (argc == 4)
        {        
                /* if the seed has been provided by the user, extract the
                 * number from the string provided - please note that I am not
                 * using strtoint as we need a long int */
                sscanf(argv[3], "%u", &seed);
        }
        else 
        {        
                /* if the seed is not provided, generate the seed for the 
                 * current second */
                seed = time(NULL);
        }


        /* start the random number generator */
        srand(seed);

        /* output the seed being used */
        printf("Using seed %u\n", seed);

        /* load the dictionary file */
        word_list_init(&wordlist);

        if (!load_word_list(argv[1], &wordlist))
        {
                printf("Failed to load the dictionary.\n");
                return EXIT_FAILURE;
        }

        printf("%d words have been loaded.\n", wordlist.len);
        /*display_all(&wordlist);*/
        /*printf("%s\n", wordlist.head->word);*/

        /* play the game :) */
        play_game(&wordlist, argv[2]);

        /* free memory */


        return EXIT_SUCCESS;
}

