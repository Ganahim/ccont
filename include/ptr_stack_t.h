#ifndef _PTR_STACK_T_H
#define _PTR_STACK_T_H

#include <stdalign.h>
#include <containers_common.h>


#define ptr_stack_begin(P)		((P)->begin)
#define ptr_stack_end(P)		(ptr_stack_begin(P) + (P)->count)
#define ptr_stack_index(P, N)	((P)->begin + (N))
#define ptr_stack_size(P)		((P)->count * sizeof(void *))

typedef struct _PTR_STACK_T {
	size_t count;
	size_t capacity;
	size_t min_capacity;
	pfn_dtor_t destroy_hook;
	pfn_copy_t copy_hook;
	pfn_exception_handler_t exception_handler;
	void ** begin;
} ptr_stack_t;



ptr_stack_t * ptr_stack_create(size_t count, size_t minCap);
int ptr_stack_destroy(ptr_stack_t * stack);
ptr_stack_t * ptr_stack_copy(ptr_stack_t * stack);


void ptr_stack_resize(ptr_stack_t * stack, size_t count);

void ptr_stack_push(ptr_stack_t * stack, void * ptr);
void * ptr_stack_pop(ptr_stack_t * stack);
void * ptr_stack_back(ptr_stack_t * stack);



ptr_stack_t * ptr_stack_allocate();
void ptr_stack_free(ptr_stack_t * stack);

void ptr_stack_init(ptr_stack_t * stack, size_t ptrCount, size_t minCap);
int ptr_stack_deinit(ptr_stack_t * stack);



/* Pre-defined hooks */
int ptr_stack_simple_dtor(void * vp_stack);
int ptr_stack_simple_copy(void * vp_dest, void * vp_src);


/* Debug function */
#ifndef NDEBUG
	void ptr_stack_debug(ptr_stack_t * stack);
#endif

#endif
