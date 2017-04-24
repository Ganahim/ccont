#ifndef _FUNC_STACK_T_H
#define _FUNC_STACK_T_H

#include <debug.h>
#include <containers_common.h>
#include <ptr_stack_t.h>

typedef void (*function_t)(void);
#define FUNCTION_T(PFN) ((function_t)(PFN))


#define func_stack_begin(P)		((P)->begin)
#define func_stack_end(P)			(func_stack_begin(P) + (P)->count)

typedef struct _FUNC_STACK_T {
	size_t count;
	size_t capacity;
	function_t * begin;
	void (*on_destroy)(struct _FUNC_STACK_T *);
} func_stack_t;


func_stack_t * func_stack_create();
void func_stack_destroy(func_stack_t * stack);

void func_stack_push(func_stack_t * stack, function_t func);
function_t func_stack_pop(func_stack_t * stack);
function_t func_stack_back(func_stack_t * stack);

#endif
