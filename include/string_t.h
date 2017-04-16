#ifndef _STRING_T_H
#define _STRING_T_H

#include <stddef.h>
#include <containers_common.h>

/*	NOTE:
	- Capacity 		== size of raw buffer in bytes
	- Size 			== number of bytes currently in use
	- Reserved		== maximum amount of usable space with current capacity (capacity - 2).
*/



#define MIN_CAPACITY 32

#define string_begin(P)			((P)->begin)
#define string_end(P)			((P)->begin + (P)->size)
#define string_rbegin(P)		(string_end(P) - 1)
#define string_rend(P)			(string_begin(P) - 1)

#define string_front(P)			(*string_begin(P))
#define string_back(P)			(*string_rbegin(P))
;


typedef struct _STRING_T {
	char * begin;
	size_t size;
	size_t capacity;
	char fill;
} string_t;


string_t * string_new(const char * str);
string_t * string_new_empty();
void string_delete(string_t * s);

void string_resize(string_t * s, size_t n);

string_t * string_append_sz(string_t * s, const char * sz);
string_t * string_append_sz_n(string_t * s, const char * sz, size_t n);
string_t * string_substr(const string_t * s, size_t index, size_t len);




/* Internals */
#define string_reserved(P)		((P)->capacity - 2)
#define string_unused(P)		(string_reserved(P) - (P)->size)
#define string_alloc_addr(P)	(string_begin(P) - 1)

void string_upscale(string_t * s);
void string_downscale(string_t * s);



/* Debug */
#ifndef NDEBUG
#	include <stdio.h>
	void string_debug(string_t * s);
#endif
#endif // include guard end
