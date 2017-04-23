#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <buffer_t.h>
#include <func_stack_t.h>


func_stack_t * func_stack_create() {
	func_stack_t * stack = ALLOC(sizeof(func_stack_t));
	memset(stack, 0, sizeof(func_stack_t));
	stack->buffer = buffer_create(256);
	return stack;
}

void func_stack_destroy(func_stack_t * stack) {
	assert(stack != NULL);
	buffer_destroy(stack->buffer);
	FREE(stack);
}

void func_stack_push(func_stack_t * stack, function_t func) {
	assert(stack != NULL);
	assert(func != NULL);

	size_t sizeNeeded = (stack->count + 1) * sizeof(function_t);
	buffer_resize(stack->buffer, sizeNeeded);

	*func_stack_end(stack) = func;
	stack->count++;
}

function_t func_stack_pop(func_stack_t * stack) {
	assert(stack != NULL);

	function_t f = func_stack_back(stack);
	stack->count--;

	size_t sizeNeeded = (stack->count) * sizeof(function_t);
	buffer_resize(stack->buffer, sizeNeeded);

	return f;
}

function_t func_stack_back(func_stack_t * stack) {
	assert(stack != NULL);
	return *(func_stack_end(stack) - 1);
}


void func_stack_debug(func_stack_t * stack) {
	assert(stack != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\tbegin: %p\n", func_stack_begin(stack));
	fprintf(stderr, "\tend: %p\n", func_stack_end(stack));
	fprintf(stderr, "\tcount: %zu\n", stack->count);
	fprintf(stderr, "\tsize: %zu\n", stack->buffer->size);
	fprintf(stderr, "\tcapacity: %zu\n", stack->buffer->capacity);

	fputc('\n', stderr);
}
