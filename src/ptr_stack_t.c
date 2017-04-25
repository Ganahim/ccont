#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdarg.h>

#include <debug.h>
#include <ptr_stack_t.h>
#include <util.h>

#define PTR_STACK_DEFAULT_CAPACITY 256


ptr_stack_t * ptr_stack_create(size_t count, size_t minCap) {
	ptr_stack_t * stack = ALLOC(sizeof(ptr_stack_t));
	memset(stack, 0, sizeof(ptr_stack_t));

	stack->min_capacity = minCap;
	stack->capacity = compute_capacity(count * sizeof(void *), stack->min_capacity);
	stack->begin = ALLOC(stack->capacity);

	return stack;
}

void ptr_stack_destroy(ptr_stack_t * stack) {
	assert(stack != NULL);

	FREE(stack->begin);
	FREE(stack);
}

void ptr_stack_push(ptr_stack_t * stack, void * ptr) {
	assert(stack != NULL);

	size_t sizeNeeded = ptr_stack_size(stack) + sizeof(void *);
	size_t capNeeded = compute_capacity(sizeNeeded, stack->min_capacity);

	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

	*ptr_stack_end(stack) = ptr;
	stack->count++;
}

void ptr_stack_pop(ptr_stack_t * stack) {
	assert(stack != NULL);

	stack->count--;

	size_t capNeeded = compute_capacity(ptr_stack_size(stack), stack->min_capacity);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}
}

void * ptr_stack_back(ptr_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);

	return *(ptr_stack_end(stack) - 1);
}




void _ptr_stack_vpush(ptr_stack_t * stack, void * p1, ...) {
	assert(stack != NULL);
	assert(p1 != NULL);

	va_list ap;
	va_start(ap, p1);

	void * p = p1;
	while(p != NULL) {
		ptr_stack_push(stack, p);
		p = va_arg(ap, void *);
	}

	va_end(ap);
}




#ifndef NDEBUG
#include <stdio.h>

void ptr_stack_debug(ptr_stack_t * stack) {
	assert(stack != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\tbegin: %p\n", stack->begin);
	fprintf(stderr, "\tend: %p\n", ptr_stack_end(stack));
	fprintf(stderr, "\tcount: %zu\n", stack->count);
	fprintf(stderr, "\tsize: %zu\n", ptr_stack_size(stack));
	fprintf(stderr, "\tcapacity: %zu\n", stack->capacity);

	fputc('\n', stderr);

	// for(void ** p = ptr_stack_begin(stack); p != ptr_stack_end(stack); p++) {
	// 	fprintf(stderr, "\t%s\n", (char *)*p);
	// }

	fputc('\n', stderr);
}


#endif
