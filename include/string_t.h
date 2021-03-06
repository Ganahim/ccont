#ifndef _STRING_T_H
#define _STRING_T_H

#include <stddef.h>
#include <containers_common.h>

/*	NOTE:
	- Capacity 		== size of raw buffer in bytes
	- Size 			== number of bytes currently in use
	- Reserved		== maximum amount of usable space with current capacity (capacity - 2).
*/


/* Direct pointer access macros.
	Any pointer returned from one of the following
	macros may be invalidated by calls to any function
	that modifies the underlying string_t object. */
#define string_begin(P)			((P)->begin)
#define string_end(P)			((P)->begin + (P)->size)
#define string_rbegin(P)		(string_end(P) - 1)
#define string_rend(P)			(string_begin(P) - 1)

/* Return first and last characters, respectively. */
#define string_front(P)			(*string_begin(P))
#define string_back(P)			(*string_rbegin(P))
#define dummy


typedef struct _STRING_T {
	char * begin;
	size_t size;
	size_t capacity;
} string_t;




string_t * string_create(const char * str);
string_t * string_create_empty();
void string_destroy(string_t * s);

string_t * string_copy(string_t * src);


void string_change_capacity(string_t * s, size_t n);
void string_resize(string_t * s, size_t n, char fill);

string_t * string_append(string_t * dest, string_t * src);
string_t * string_append_sz(string_t * s, const char * sz);
string_t * string_append_sz_n(string_t * s, const char * sz, size_t n);
string_t * string_substr(const string_t * s, size_t index, size_t len);


string_t * string_erase(string_t * s, size_t index, size_t len);
string_t * string_insert(string_t * dest, size_t index, string_t * src);
string_t * string_insert_sz(string_t * dest, size_t index, const char * src);




/* Internals */
#define string_reserved(P)		((P)->capacity - 2)
#define string_unused(P)		(string_reserved(P) - (P)->size)
#define string_alloc_addr(P)	(string_begin(P) - 1)


/* Debug */
#ifndef NDEBUG
#	include <stdio.h>
	void string_debug(string_t * s);
#endif
#endif // include guard end
