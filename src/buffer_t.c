#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <buffer_t.h>

#define MIN_BUFFER_CAPACITY 256

buffer_t * buffer_create(size_t size) {
	size_t cap = compute_capacity(size, MIN_BUFFER_CAPACITY);
	buffer_t * buf = ALLOC(sizeof(buffer_t) + cap);
	memset(buf, 0, sizeof(buffer_t));

	buf->capacity = cap;
	buf->size = size;
	buf->begin = (char *)(buf + 1);
}

void buffer_destroy(buffer_t * buf) {
	FREE(buf);
}

void buffer_resize(buffer_t * buf, size_t size) {
	size_t n = compute_capacity(size, MIN_BUFFER_CAPACITY);
	if(buf->capacity != n) {
		buf->capacity = n;
		buf = REALLOC(buf, sizeof(buffer_t) + buf->capacity);
	}

	buf->size = size;
}



void buffer_debug(buffer_t * buf) {
	assert(buf != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\tbegin: %p\n", buffer_begin(buf));
	fprintf(stderr, "\tend: %p\n", buffer_end(buf));
	fprintf(stderr, "\tsize: %zu\n", buf->size);
	fprintf(stderr, "\tcapacity: %zu\n", buf->capacity);

	fputc('\n', stderr);
}
