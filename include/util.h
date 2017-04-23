#ifndef _UTIL_H
#define _UTIL_H

#include <stddef.h>


typedef struct {
	size_t size;
	void * data;
} data_t;


#define pack_data(...)		_pack_data(__VA_ARGS__, NULL)
data_t * _pack_data(data_t * d1, ...);




#define vfree(...)		_vfree(__VA_ARGS__, NULL);
void _vfree(void * p1, ...);

#endif
