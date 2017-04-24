#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <func_stack_t.h>

#define MIN_FUNC_STACK_CAPACITY 256

func_stack_t * func_stack_create() {
	func_stack_t * stack = ALLOC(sizeof(func_stack_t));
	memset(stack, 0, sizeof(func_stack_t));

	stack->capacity = MIN_FUNC_STACK_CAPACITY;
	stack->begin = ALLOC(stack->capacity);
	return stack;
}

void func_stack_destroy(func_stack_t * stack) {
	assert(stack != NULL);

	if(stack->on_destroy != NULL) {
		stack->on_destroy(stack);
	}

	FREE(stack->begin);
	FREE(stack);
}

void func_stack_push(func_stack_t * stack, function_t func) {
	assert(stack != NULL);
	assert(func != NULL);

	size_t capNeeded = compute_capacity((stack->count + 1) * sizeof(function_t), MIN_FUNC_STACK_CAPACITY);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

	*func_stack_end(stack) = func;
	stack->count++;
}

function_t func_stack_pop(func_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);

	function_t f = func_stack_back(stack);
	stack->count--;

	size_t capNeeded = compute_capacity(stack->count * sizeof(function_t), MIN_FUNC_STACK_CAPACITY);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
	}

	return f;
}

function_t func_stack_back(func_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);
	return *(func_stack_end(stack) - 1);
}
