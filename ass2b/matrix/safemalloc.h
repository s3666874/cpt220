#include "bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* provide line numbers to safe_malloc through a macro */
#define safemalloc(size) safe_malloc(size, __LINE__)
#define safecalloc(nmem, size) safe_calloc(nmem, size, __LINE__)
#define safeptrmalloc(memory, size) safe_ptr_malloc(memory, size, __LINE__)
#define saferealloc(memory, size) safe_realloc(memory, size, __LINE__)

void * safe_malloc(size_t, unsigned long );
void * safe_calloc(size_t, size_t, unsigned long);
void safe_ptr_malloc(void**, size_t, unsigned long);
void * safe_realloc(void*, size_t, unsigned long);



