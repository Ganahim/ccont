#ifndef _UTIL_H
#define _UTIL_H

#include <stddef.h>
#include <containers_common.h>


size_t compute_capacity(size_t size, size_t min);



#define memcat(...)		_memcat(__VA_ARGS__, NULL, 0)
void * _memcat(void * dest, void * p1, size_t n1, ...);


#define mempluck(...)	_mempluck(__VA_ARGS__, NULL, 0)
void * _mempluck(void * src, void * p1, size_t n1, ...);



#define va_alloc(...)		_va_alloc(__VA_ARGS__, NULL, 0);
void * _va_alloc(void ** p1, size_t n1, ...);


#define vfree(...)		_vfree(__VA_ARGS__, NULL);
void _vfree(void * p1, ...);




typedef struct _KVPAIR_T {
	char * key;
	char * value;
} kvpair_t;

kvpair_t * kvpair_create(const char * key, const char * value);

#endif
