#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdarg.h>

#include <debug.h>
#include <ptr_stack_t.h>
#include <util.h>

// #define PTR_STACK_DEFAULT_CAPACITY 256
#define NSIZEOF(N, TYPE)	((N) * sizeof(TYPE))


ptr_stack_t * ptr_stack_create(size_t count, size_t minCap) {
	ptr_stack_t * stack = ALLOC(sizeof(ptr_stack_t));
	memset(stack, 0, sizeof(ptr_stack_t));

	stack->min_capacity = minCap;
	stack->count = count;
	stack->capacity = compute_capacity(stack->count * sizeof(void *), stack->min_capacity);
	stack->begin = ALLOC(stack->capacity);

	return stack;
}

int ptr_stack_destroy(ptr_stack_t * stack) {
	assert(stack != NULL);

	int r = 0;
	if(stack->destroy_hook != NULL) {
		r = stack->destroy_hook(stack);
		if(r < 0) {
			assert(stack->exception_handler != NULL);	// The user is responsible for defining an error handler if the provided hook can potentially return a negative value
			stack->exception_handler(stack, r);
		}
	}

	FREE(stack->begin);
	FREE(stack);
	return r;
}


void ptr_stack_resize(ptr_stack_t * stack, size_t count) {
	assert(stack != NULL);

	stack->count = count;
	size_t sizeNeeded = stack->count * sizeof(void *);
	size_t capNeeded = compute_capacity(sizeNeeded, stack->min_capacity);

	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

}



void ptr_stack_push(ptr_stack_t * stack, void * ptr) {
	assert(stack != NULL);

	size_t sizeNeeded = ptr_stack_size(stack) + sizeof(void *);					// No. of bytes needed after adding one ptr
	size_t capNeeded = compute_capacity(sizeNeeded, stack->min_capacity);	// Calculate nearest power of two that accommodates the requested size

	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

	*ptr_stack_end(stack) = ptr;
	stack->count++;
}

void * ptr_stack_pop(ptr_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);

	void * r = ptr_stack_back(stack);
	stack->count--;

	size_t capNeeded = compute_capacity(ptr_stack_size(stack), stack->min_capacity);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

	return r;
}

void * ptr_stack_back(ptr_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);

	return *(ptr_stack_end(stack) - 1);
}


ptr_stack_t * ptr_stack_copy(ptr_stack_t * src) {
	assert(src != NULL);

	ptr_stack_t * dest = ptr_stack_create(0, src->min_capacity);
	dest->destroy_hook = src->destroy_hook;
	dest->copy_hook = src->copy_hook;

	/* Use a user provided copy function if supplied */
	if(src->copy_hook != NULL) {
		int r = src->copy_hook(dest, src);
		if(r < 0) {
			assert(src->exception_handler != NULL);	// The user is responsible for defining an error handler if the provided hook can potentially return a negative value
			src->exception_handler(src, r);
			return NULL;
		}

		return dest;
	}
	/* Default to shallow copy, ie. simply copy the pointers and not their contents */
	else {
		ptr_stack_resize(dest, src->count);
		memcpy(ptr_stack_begin(dest), ptr_stack_begin(src), ptr_stack_size(src));
		return dest;
	}
}




/* The following functions are intended to provide flexibility
	in case a more granular approach to creation/destruction is desired.

	ptr_stack_allocate and ptr_stack_init split the functionality of
	ptr_stack_create, so that one can initialize a ptr_stack_t object
	that was not allocated on the heap. Similarly, ptr_stack_deinit and
	ptr_stack_free split the functionality of ptr_stack_destroy.
*/
ptr_stack_t * ptr_stack_allocate() {
	ptr_stack_t * stack = ALLOC(sizeof(ptr_stack_t));
	memset(stack, 0, sizeof(ptr_stack_t));
	return stack;
}

void ptr_stack_init(ptr_stack_t * stack, size_t ptrCount, size_t minCap) {
	assert(stack != NULL);

	stack->min_capacity = minCap;
	stack->count = ptrCount;
	stack->capacity = compute_capacity(stack->count * sizeof(void *), stack->min_capacity);
	stack->begin = ALLOC(stack->capacity);
}


int ptr_stack_deinit(ptr_stack_t * stack) {
	assert(stack != NULL);

	int r = 0;
	if(stack->destroy_hook != NULL) {
		r = stack->destroy_hook(stack);
		if(r < 0) {
			assert(stack->exception_handler != NULL);
			stack->exception_handler(stack, r);
		}
	}

	FREE(stack->begin);
	return r;
}

void ptr_stack_free(ptr_stack_t * stack) {
	assert(stack != NULL);
	FREE(stack);
}









int ptr_stack_simple_dtor(void * vp_stack) {
	assert(vp_stack != NULL);
	ptr_stack_t * stack = vp_stack;

	for(void ** p = ptr_stack_begin(stack); p != ptr_stack_end(stack); p++) {
		FREE(*p);
	}

	return 0;
}

int ptr_stack_simple_copy(void * vp_dest, void * vp_src) {

}


/* Debugging stuff */
#ifndef NDEBUG
#include <debug.h>
#include <stdio.h>
#include <stdarg.h>

#define DBG_DEREF		0x1u

void ptr_stack_debug(ptr_stack_t * stack) {
	assert(stack != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\t%-12s %p\n", "begin", stack->begin);
	fprintf(stderr, "\t%-12s %p\n", "end", ptr_stack_end(stack));
	fprintf(stderr, "\t%-12s %zu\n", "count", stack->count);
	fprintf(stderr, "\t%-12s %zu\n", "size", ptr_stack_size(stack));
	fprintf(stderr, "\t%-12s %zu\n", "capacity", stack->capacity);

	fputc('\n', stderr);

	fputc('\n', stderr);
}


#endif
