#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <string_t.h>

#define MAX(A, B)			((A) > (B) ? (A) : (B))
#define MIN(A, B)			((A) < (B) ? (A) : (B))
#define ABSDIFF(A, B)	(MAX(A, B) - MIN(A, B))




string_t * string_create(const char * str) {
	assert(str != NULL);

	string_t * s = ALLOC(sizeof(string_t));
	memset(s, 0, sizeof(string_t));

	s->size = strlen(str);
	s->capacity = 1;

	while(s->capacity < MAX(MIN_CAPACITY, s->size+2)) {
		s->capacity <<= 1;
	}

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

	s->capacity = 1;
	while(s->capacity < MAX(MIN_CAPACITY, s->size+2)) {
		s->capacity <<= 1;
	}

	s->begin = ALLOC(s->capacity);
	s->begin++;


	*string_end(s) = 0;

	return s;
}


void string_destroy(string_t * s) {
	assert(s != NULL);
	FREE(--s->begin);
}



void string_resize(string_t * s, size_t n, char fill) {
	assert(s != NULL);

	if(n > s->size) {
		while(n > string_unused(s))
			string_upscale(s);

		memset(string_end(s), fill, (n - s->size));
	}
	else {
		while((((s->capacity >> 1) - 2) >= n) && ((s->capacity >> 1) >= MIN_CAPACITY))
			string_downscale(s);
	}

	s->size = n;
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

	// Upscale as much as needed to accommodate sz
	while(len > string_unused(s)) {
		string_upscale(s);
	}

	memcpy(string_end(s), sz, len);
	s->size += len;
	*string_end(s) = 0;

	return s;
}


string_t * string_append_sz_n(string_t * s, const char * sz, size_t n) {
	assert(s != NULL);
	assert(sz != NULL);

	char * z = memchr(sz, 0, n);
	size_t len = (z == NULL ? n : (z - sz));


	while(len > string_unused(s)) {
		string_upscale(s);
	}

	memcpy(string_end(s), sz, n);
	s->size += len;
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


string_t * string_insert(string_t * dest, size_t index, string_t * src) {
	assert(dest != NULL);

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


/* Internals */

// Scale up capacity
void string_upscale(string_t * s) {
	assert(s != NULL);

	s->capacity <<= 1;
	s->begin--;
	s->begin = REALLOC(s->begin, s->capacity);
	s->begin++;
}

void string_downscale(string_t * s) {
	assert(s != NULL);
	assert(s->capacity >= MIN_CAPACITY);

	s->capacity >>= 1;
	s->begin--;
	s->begin = REALLOC(s->begin, s->capacity);
	s->begin++;
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



#undef MIN
#undef MAX
