#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <node_ext.h>


/* A pre-defined destroy hook that checks whether 'data' is NULL, and if not, calls FREE on it. */
void * node_simple_destroy_hook(node_t * node) {
	assert(node != NULL);
	// FUNC_DEBUG("");

	if(node->data != NULL) {
		FREE(node->data);
		node->data = NULL;
	}

	return NULL;
}


/* A pre-defined copy hook for null terminated strings. */
void * node_string_copy_hook(node_t * dest, node_t * src) {
	assert(src != NULL);
	assert(dest != NULL);
	FUNC_DEBUG("");

	size_t n = strlen((char *)src->data);
	char * dest_str = ALLOC(n + 1);
	strcpy(dest_str, (char *)src->data);

	dest->data = dest_str;
	return NULL;
}
