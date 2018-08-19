/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "word_list.h"
#include "io.h"
/******************************************************************************
 * the word_list module simply keeps track of all the words in our
 * "dictionary". After loading from disk, the main purpose of this list will be
 * to check that a word exists in the dictionary. You will need to create the
 * functions for managing this list.
 *****************************************************************************/

/**
 * initialise the word list - you should ensure the elements of the wordlist
 * header struct is initialised to a known safe state
 **/
BOOLEAN wl_init(struct word_list* wordlist)
{
        assert(wordlist);
        memset(wordlist, 0, sizeof(struct word_list));
        return FALSE;
}

/**
 * function only visible inside this module for the initialisation of
 * the node struct for the word list.
 **/
static struct word_node* new_word_node(const char word[])
{
        struct word_node* new;
        char* new_word;

        /* allocate space for the node */
        new = malloc(sizeof(struct word_node));
        if (!new)
        {
                error_print("malloc: %s\n", strerror(errno));
                return NULL;
        }
        /* allocate space for the word itself */
        new_word = malloc((strlen(word) + 1) * sizeof(char));
        if (!new_word)
        {
                free(new);
                return NULL;
        }
        /* copy in the word */
        strcpy(new_word, word);
        new->word = new_word;
        new->next = NULL;
        return new;
}

/**
 * adds a word to the word list. It searches for the insertion point and then
 * inserts the word at the appropriate location in sorted order.
 **/
BOOLEAN wl_add(struct word_list* wordlist, const char newword[])
{
        struct word_node* curr, *prev = NULL;
        struct word_node* new;

        assert(wordlist);
        assert(newword);

        /* allocate space for the word node and the word itself */
        new = new_word_node(newword);

        curr = wordlist->head;
        /* insert the first word in an empty list */
        if (!curr)
        {
                wordlist->head = new;
                wordlist->len = 1;
                return TRUE;
        }
        /* find the insertioin point*/
        while (curr && strcmp(curr->word, newword) < 0)
        {
                prev = curr;
                curr = curr->next;
        }
        /* insert at the start of the list */
        if (!prev)
        {
                new->next = wordlist->head;
                wordlist->head = new;
        }
        else
        {
                /* insert elsewhere in the list. Note that if at the end, curr
                 * will be NULL
                 */
                prev->next = new;
                new->next = curr;
        }
        /* keep track of the length of the list */
        wordlist->len += 1;
        return TRUE;
}
