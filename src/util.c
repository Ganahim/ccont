#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdalign.h>
#include <util.h>

#include <debug.h>


size_t compute_capacity(size_t size, size_t min) {
	size_t n = (min > 0 ? min : 1);
	while(n < size) {
		n <<= 1;
	}

	return n;
}


/* Concatenate an arbitrary number of memory blocks into
	the memory region pointed by dest. Arguments are
	given in pairs, where the first argument of each pair
	is a pointer, and the second an unsigned integer indicating
	the number of bytes to copy from said pointer into dest.

	A null pointer provided in place of a pointer, followed
	by a non-zero byte count, indicates that the region should
	be padded with zeroes instead.

	The end of the argument list is indicated by 'NULL, 0'.
*/
void * _memcat(void * dest, void * p1, size_t n1, ...) {
	assert(dest != NULL);

	char * d = dest;
	void * p = p1;
	size_t n = n1;

	va_list ap;
	va_start(ap, n1);

	while(!((p == NULL) && (n == 0))) {
		if(p == NULL)
			memset(d, 0, n);
		else
			memcpy(d, p, n);

		d += n;
		p = va_arg(ap, void *);
		n = va_arg(ap, size_t);
	}

	va_end(ap);
	return dest;
}


void * _mempluck(void * src, void * p1, size_t n1, ...) {
	assert(src != NULL);

	char * s = src;
	void * p = p1;
	size_t n = n1;

	va_list ap;
	va_start(ap, n1);

	while(!((p == NULL) && (n == 0))) {
		if(p != NULL)
			memcpy(p, s, n);

		s += n;
		p = va_arg(ap, void *);
		n = va_arg(ap, size_t);
	}

	va_end(ap);
	return s;
}






/* Allocate nN bytes of memory for each pointer *pN.

-	The function calculates the total size needed
	and uses this in a single call to malloc(), setting
	each supplied pointer to an appropriate address in
	the returned memory block.

-	Returns the start address for the allocated buffer,
	which is equal to the address given to the first pointer
	argument, and can be freed using free().

-	The arguments are supplied in pairs of void ** and size_t,
	and the argument list must end with the end markers 'NULL, 0'.
	A macro is provided in 'util.h' which takes care of this automatically.
 */
void * _va_alloc(void ** p1, size_t n1, ...) {
	assert(p1 != NULL);

	void ** p = p1;
	size_t n = n1;
	size_t total = 0;
	va_list ap;


	/* Count total number of bytes needed */
	va_start(ap, n1);
	while(p != NULL) {
		total += n;

		p = va_arg(ap, void **);
		n = va_arg(ap, size_t);
	}
	va_end(ap);


	/* Allocate enough space for all pointers */
	size_t cap = compute_capacity(total, _Alignof(max_align_t));
	char * buf = aligned_alloc(_Alignof(max_align_t), cap); //malloc(cap);

	/* Loop vars */
	p = p1;
	n = n1;
	size_t curPos = 0;
	va_list ap2;


	/* Assign a portion of buf to each pointer */
	va_start(ap2, n1);
	while(p != NULL) {
		*p = (void *)(buf + curPos);
		curPos += n;
		p = va_arg(ap2, void **);
		n = va_arg(ap2, size_t);
	}
	va_end(ap2);

	return *p1;
}


void _vfree(void * p1, ...) {
	assert(p1 != NULL);

	va_list ap;
	va_start(ap, p1);

	void * p = p1;
	while(p != NULL) {
		free(p);
		p = va_arg(ap, void *);
	}

	va_end(ap);
}



/* Utilizes va_alloc() to dynamically allocate a structure holding a
 	key-value pair.
*/
kvpair_t * kvpair_create(const char * key, const char * value) {
	assert(key != NULL);
	assert(value != NULL);

	kvpair_t * pair;
	char * p1, * p2;

	va_alloc(
		(void **)&pair, sizeof(kvpair_t),
		(void **)&p1, strlen(key) + 1,
		(void **)&p2, strlen(value) + 1
	);

	strcpy(p1, key);
	strcpy(p2, value);

	pair->key = p1;
	pair->value = p2;

	return pair;
}
