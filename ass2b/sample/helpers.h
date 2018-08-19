/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "shared.h"
#include <limits.h>
#include <ctype.h>
#include <assert.h>

#ifndef HELPERS_H
#define HELPERS_H
#define DECIMAL 10
/**
 * public functions callable from this module
 **/
char* strdup(const char*);
int count_char(const char[], char);
char* fold(char*, int);
BOOLEAN strtoint(const char[], int*);
char** tokenize(const char[], const char[], int);
char* strtoupper(char*);
char* strtolower(char*);
void free_tokens(char**, int);
#endif
