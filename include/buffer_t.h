#ifndef _BUFFER_T_H
#define _BUFFER_T_H

#include <stddef.h>
#include <containers_common.h>



#define buffer_begin(P)			((void *)(P)->begin)
#define buffer_end(P)			((void *)((P)->begin + (P)->size))

typedef struct _BUFFER_T {
	size_t size;
	size_t capacity;
	char * begin;
} buffer_t;


buffer_t * buffer_create(size_t size);
void buffer_destroy(buffer_t * buf);
void buffer_resize(buffer_t * buf, size_t size);


void buffer_debug(buffer_t * buf);

#endif
