#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <util.h>




data_t * _pack_data(data_t * d1, ...) {
	assert(d1 != NULL);

	va_list ap;
	va_start(ap, d1);

	size_t size = d1->size;

	data_t * p = va_arg(ap, data_t *);
	while(p != NULL) {
		size += p->size;
		p = va_arg(ap, data_t *);
	}

	va_end(ap);

	va_list ap2;
	va_start(ap2, d1);

	data_t * buf = malloc(sizeof(data_t) + size);
	buf->size = size;
	buf->data = (buf + 1);


	char * p2 = buf->data;

	p = d1;
	while(p != NULL) {
		memcpy(p2, p->data, p->size);
		p2 += p->size;
		p = va_arg(ap2, data_t *);
	}

	va_end(ap2);

	return buf;
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
