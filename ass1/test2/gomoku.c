#include "gomoku.h"

int main(void)
{

	BOOLEAN quit = FALSE;

    /* initialise the random number generator for your program */
    srand(time(NULL));

    /* display the menu continuously until the user decided to quit the
     * program
     */
    while (!quit)
    {
        enum menu_choice choice;

        /* display the menu and get the choice from the user */
        choice = get_menu_choice();

        switch (choice)
        {
            /* based on the choice the user made you should:
             */
            case MC_PLAY_GAME:
                /* play the game */
                play_game();
                break;

            case MC_QUIT:
                /* quit the program */
                printf("Thank you for playing\n");
                quit = TRUE;
                break;

            default:
                error_print("invalid menu item selected\n");
                break;
        }
    }
    return EXIT_SUCCESS;
}
