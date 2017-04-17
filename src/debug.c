#include <stdlib.h>
#include <debug.h>


long debug_malloc_count = 0;
long debug_realloc_count = 0;
long debug_free_count = 0;


void * debug_alloc(size_t n) {
	debug_malloc_count++;
	return malloc(n);
}

void * debug_realloc(void * p, size_t n) {
	if(p == NULL)
		debug_malloc_count++;
	else
		debug_realloc_count++;

	return realloc(p, n);
}

void debug_free(void * p) {
	debug_free_count++;
	free(p);
}


void debug_print_alloc_report() {
	FUNC_DEBUG("");

	fprintf(stderr, "\tmalloc count: %zu\n", debug_malloc_count);
	fprintf(stderr, "\tfree count: %zu\n", debug_free_count);
	fprintf(stderr, "\tdiff: %zu\n", debug_malloc_count - debug_free_count);

	fprintf(stderr, "\trealloc count: %zu\n", debug_realloc_count);
	fputc('\n', stderr);
}
