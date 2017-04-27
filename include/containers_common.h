#ifndef _CONTAINERS_COMMON_H
#define _CONTAINERS_COMMON_H

#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif
#ifndef REALLOC
#	define REALLOC(...)	realloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif

#include <stddef.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*** Types ***/

/* Memory mgmt function pointers */
typedef void * (*pfn_alloc_t)(size_t);
typedef void * (*pfn_realloc_t)(void *, size_t);
typedef void (*pfn_free_t)(void *);

/* Pointer types for object facilities */
typedef int (*pfn_dtor_t)(void * self);
typedef int (*pfn_copy_t)(void * dest, void * src);
typedef void (*pfn_exception_handler_t)(void * self, int code);






#endif
