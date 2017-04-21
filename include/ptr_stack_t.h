#ifndef _PTR_STACK_T_H
#define _PTR_STACK_T_H

#include <containers_common.h>


#define ptr_stack_begin(P)		((P)->begin)
#define ptr_stack_end(P)		(ptr_stack_begin(P) + (P)->count)
#define ptr_stack_size(P)		((P)->count * sizeof(void *))

typedef struct _PTR_STACK_T {
	size_t count;
	size_t capacity;
	void ** begin;
} ptr_stack_t;



ptr_stack_t * ptr_stack_create();
void ptr_stack_destroy(ptr_stack_t * stack);

void ptr_stack_push(ptr_stack_t * stack, void * ptr);
void ptr_stack_pop(ptr_stack_t * stack);
void * ptr_stack_back(ptr_stack_t * stack);


void ptr_stack_debug(ptr_stack_t * stack);

#endif
