#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef NDEBUG

#include <assert.h>

#include <stdio.h>
#ifndef FUNC_DEBUG
#	define FUNC_DEBUG(...)	fprintf(stderr, ">> %s():", __func__); fprintf(stderr, " "__VA_ARGS__); fputc('\n', stderr);
#endif

#ifndef ALLOC
#	define ALLOC(...)			debug_alloc(__VA_ARGS__)
#endif
#ifndef REALLOC
#	define REALLOC(...)		debug_realloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)			debug_free(__VA_ARGS__)
#endif


extern long debug_malloc_count;
extern long debug_realloc_count;
extern long debug_free_count;

void * debug_alloc(size_t n);
void * debug_realloc(void * p, size_t n);
void debug_free(void * p);


void debug_print_alloc_report();

#define debug_check_diff()		assert(debug_malloc_count == debug_free_count)




#define memprint(DATA, SIZE)	fprintf(stderr, #DATA); _memprint((DATA), (SIZE))
void _memprint(void * data, size_t size);

#endif // NDEBUG end
#endif // include guard
