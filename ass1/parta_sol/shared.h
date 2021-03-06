/******************************************************************************
 * Student Name    : Federick Kwok
 * RMIT Student ID : s3666874
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SHARED_H /* include guard for this shared header file - it ensures     \
                    this header is only ever includeda maximum of one time in  \
                    each source file. */
#define SHARED_H

/**
 * definition of the BOOLEAN datatype. Remember that all counting in C begins at
 * 0!
 **/
typedef enum
{
        FALSE,
        TRUE
} BOOLEAN;

/* the coordinate struct - represents a move in the game */
struct coordinate
{
        int row;
        int col;
};

#endif /* end of include guard for shared.h */
