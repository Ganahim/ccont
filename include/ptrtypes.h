#ifndef _PTRTYPES_H
#define _PTRTYPES_H

#include <stddef.h>

typedef void (*dealloc_t)(void *);

typedef struct _SMART_PTR_T {
	void * data;
	size_t refcount;
	dealloc_t dtor;
} smart_ptr_t;


smart_ptr_t * smart_ptr_ref(smart_ptr_t * ptr);
int smart_ptr_unref(smart_ptr_t * ptr);



smart_ptr_t * smart_alloc(size_t n);

#endif
