/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "scrabble.h"

/******************************************************************************
 * the scrabble module contains the main function and any helper functions to
 * kick start the program and clean up at the end.
 *****************************************************************************/
int main(int argc, char* argv[])
{
        char* dict_file, *scores_file;
        struct word_list wordlist;
        unsigned seed;
        /* validate command line argments */
        if (argc < MIN_ARGS || argc > MAX_ARGS)
        {
                display_usage();
                return EXIT_FAILURE;
        }
        dict_file = argv[ARG_DICTIONARY];
        scores_file = argv[ARG_SCORE];
        /* display a welcome message */
        normal_print("Welcome to Scrabble\n");
        PUTLINE(strlen("Welcome to Scrabble"), '-');
        putchar('\n');
        /* extract the seed */
        if (argc == MAX_ARGS)
        {
                /* if the seed has been provided by the user, extract the
                 * number from the string provided - please note that I am not
                 * using strtoint as we need a long int */
                char* end;
                seed = strtol(argv[ARG_SEED], &end, DECIMAL);
                if (*end)
                {
                        error_print("the seed provided is not valid.\n");
                        display_usage();
                        return EXIT_FAILURE;
                }
        }
        else
        {
                /* generate the seed for the current second */
                seed = time(NULL);
        }
        /* start the random number generator */
        srand(seed);
        normal_print("using seed %u\n", seed);
        /* load the dictionary file */

        normal_print("Please wait while we load the dictionary ...\n");
        if (!load_word_list(dict_file, &wordlist))
        {
                return EXIT_FAILURE;
        }
        normal_print("%d words have been loaded.\n", wordlist.len);
        /* play the game :) */
        play_game(&wordlist, scores_file);
        return EXIT_SUCCESS;
}

/**
 * display instructions to the user of the program in how to use it.
 **/
void display_usage(void)
{
        error_print("Error: invalid command-line arguments provided.\n");
        error_print("You need to call this program as: \n");
        error_print("\n\t./scrabble <dictionary> <scorefile> [<seed>]\n\n");
        error_print(
            "the dictionary file and the scorefile may have any name. \n");
        error_print("We only validate for the position of the argument and its "
                    "contents.\n");
        error_print("We do not validate the file name or its location.\n");
        error_print("The seed is optional but if used should be the seed "
                    "from a previous run of the program.\n");
}
