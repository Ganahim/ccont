#ifndef _DEBUG_H
#define _DEBUG_H

#include <assert.h>

#ifndef NDEBUG
#	include <stdio.h>
#	define FUNC_DEBUG(...)	fprintf(stderr, ">> %s():", __func__); fprintf(stderr, " "__VA_ARGS__); fputc('\n', stderr);
#endif



extern long debug_malloc_count;
extern long debug_realloc_count;
extern long debug_free_count;

void * debug_alloc(size_t n);
void * debug_realloc(void * p, size_t n);
void debug_free(void * p);


void debug_print_alloc_report();

#define debug_check_diff()		assert(debug_malloc_count == debug_free_count)



#endif
