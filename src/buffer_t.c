#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <buffer_t.h>
#include <util.h>



buffer_t * buffer_create(size_t size, size_t minCapacity) {
	buffer_t * buf = ALLOC(sizeof(buffer_t));
	memset(buf, 0, sizeof(buffer_t));

	buf->min_capacity = minCapacity;
	buf->capacity = compute_capacity(size, buf->min_capacity);
	buf->begin = ALLOC(buf->capacity);
	buf->size = size;
	return buf;
}

void buffer_destroy(buffer_t * buf) {
	FREE(buf->begin);
	FREE(buf);
}

void buffer_resize(buffer_t * buf, size_t size) {
	size_t n = compute_capacity(sizeof(buffer_t) + size, buf->min_capacity);
	if(buf->capacity != n) {
		buf->capacity = n;
		buf->begin = REALLOC(buf->begin, buf->capacity);
	}

	buf->size = size;
}



void buffer_debug(buffer_t * buf) {
	assert(buf != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\tbegin: %p\n", buffer_begin(buf));
	fprintf(stderr, "\tend: %p\n", buffer_end(buf));
	fprintf(stderr, "\tdiff: %zd\n", buffer_end(buf) - buffer_begin(buf));
	fprintf(stderr, "\tsize: %zu\n", buf->size);
	fprintf(stderr, "\tcapacity: %zu\n", buf->capacity);

	fputc('\n', stderr);
}
