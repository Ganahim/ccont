#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <string_t.h>


/* The absolute minimum capacity of the underlying buffer.
	The capacity will not go under this, even if it could. */
#define START_CAPACITY 64


/* Quick convenience macros */
#define MAX(A, B)			((A) > (B) ? (A) : (B))
#define MIN(A, B)			((A) < (B) ? (A) : (B))
#define ABSDIFF(A, B)	(MAX(A, B) - MIN(A, B))


/* Compute minimum capacity for a given amount of bytes */
static size_t compute_min_capacity(size_t size) {
	size_t n = START_CAPACITY;
	while(n < size) {
		n <<= 1;
	}
	return n;
}


string_t * string_create(const char * str) {
	assert(str != NULL);

	string_t * s = ALLOC(sizeof(string_t));
	memset(s, 0, sizeof(string_t));

	s->size = strlen(str);
	s->capacity = compute_min_capacity(s->size + 2);

	s->begin = ALLOC(s->capacity);
	s->begin++;
	memcpy(string_begin(s), str, s->size);

	*string_end(s) = 0;
	*string_rend(s) = 0;

	return s;
}


string_t * string_create_empty() {
	string_t * s = ALLOC(sizeof(string_t));
	memset(s, 0, sizeof(string_t));

	s->capacity = compute_min_capacity(s->size + 2);

	s->begin = ALLOC(s->capacity);
	s->begin++;


	*string_end(s) = 0;

	return s;
}


void string_destroy(string_t * s) {
	assert(s != NULL);
	FREE(--s->begin);
	FREE(s);
}


string_t * string_copy(string_t * src) {
	assert(src != NULL);
	return string_create(string_begin(src));
}



void string_change_capacity(string_t * s, size_t n) {
	assert(s != NULL);

	s->capacity = n;
	s->begin--;
	s->begin = REALLOC(s->begin, s->capacity);
	s->begin++;
}


void string_resize(string_t * s, size_t n, char fill) {
	assert(s != NULL);

	size_t oldsize = s->size;

	s->size = n;
	size_t cap_needed = compute_min_capacity(s->size + 2);

	if(s->capacity != cap_needed) {
		string_change_capacity(s, cap_needed);
	}

	if(s->size > oldsize) {
		memset(string_begin(s) + oldsize, fill, s->size - oldsize);
	}

	*string_end(s) = 0;
}


string_t * string_append(string_t * dest, string_t * src) {
	assert(dest != NULL);
	assert(src != NULL);

	return string_append_sz(dest, string_begin(src));
}


string_t * string_append_sz(string_t * s, const char * sz) {
	assert(s != NULL);
	assert(sz != NULL);

	size_t len = strlen(sz);
	size_t oldsize = s->size;

	string_resize(s, s->size + len, 0);
	memcpy(string_begin(s) + oldsize, sz, len);
	*string_end(s) = 0;

	return s;
}


string_t * string_append_sz_n(string_t * s, const char * sz, size_t n) {
	assert(s != NULL);
	assert(sz != NULL);

	char * z = memchr(sz, 0, n);
	size_t len = (z == NULL ? n : (z - sz));

	size_t oldsize = s->size;
	string_resize(s, s->size + len, 0);

	memcpy(string_begin(s) + oldsize, sz, n);
	*string_end(s) = 0;

	return s;
}



string_t * string_substr(const string_t * s, size_t index, size_t len) {
	assert(s != NULL);
	assert((index + len) <= s->size);

	string_t * d = string_create_empty();
	string_resize(d, len, 0);

	memcpy(string_begin(d), (string_begin(s) + index), len);
	return d;
}



string_t * string_erase(string_t * s, size_t index, size_t len) {
	assert(s != NULL);
	assert((index + len) <= s->size);

	size_t endsize = (s->size - (index + len));
	memmove((string_begin(s) + index), (string_begin(s) + (index + len)), endsize);
	string_resize(s, (s->size - len), 0);

	return s;
}


/* Insert string 'src' into 'dest' starting from position 'index'. */
string_t * string_insert(string_t * dest, size_t index, string_t * src) {
	assert(dest != NULL);
	assert(src != NULL);

	size_t endsize = dest->size - index;

	string_resize(dest, dest->size + src->size, ' ');
	memmove(
		string_begin(dest) + index + src->size,
		string_begin(dest) + index,
		endsize
	);

	memcpy(string_begin(dest) + index, string_begin(src), src->size);

	return dest;
}



string_t * string_insert_sz(string_t * dest, size_t index, const char * src) {
	assert(dest != NULL);
	assert(src != NULL);

	size_t srcsize = strlen(src);
	size_t endsize = dest->size - index;

	string_resize(dest, dest->size + srcsize, ' ');
	memmove(
		string_begin(dest) + index + srcsize,
		string_begin(dest) + index,
		endsize
	);

	memcpy(string_begin(dest) + index, src, srcsize);

	return dest;
}


/* debug */
#ifndef NDEBUG

void string_debug(string_t * s) {
	assert(s != NULL);
	FUNC_DEBUG("\"%s\"", string_begin(s));

	fprintf(stderr, "\tbegin: %p ('%c')\n", string_begin(s), string_front(s));
	fprintf(stderr, "\tend: %p\n", string_end(s));
	fprintf(stderr, "\trbegin: %p ('%c')\n", string_rbegin(s), string_back(s));
	fprintf(stderr, "\trend: %p\n", string_rend(s));
	fprintf(stderr, "\tsize: %zu\n", s->size);
	fprintf(stderr, "\tcapacity: %zu\n", s->capacity);
	fprintf(stderr, "\treserved: %zu\n", string_reserved(s));
	fprintf(stderr, "\tunused: %zu\n", string_unused(s));

	fputc('\n', stderr);
}

#endif



/* Shouldn't need these anywhere else */
#undef MIN
#undef MAX
#undef ABSDIFF
#undef START_CAPACITY
