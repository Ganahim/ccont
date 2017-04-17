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





void * string_node_destroy_hook(node_t * node) {
	assert(node != NULL);
	FUNC_DEBUG("destroying '%s'", string_begin((string_t *)node->data));

	string_destroy((string_t *)node->data);
	return NULL;
}

void * string_copy_hook(node_t * n1, node_t *n2) {
	assert(n1 != NULL);
	assert(n2 != NULL);
	FUNC_DEBUG("");

	string_t * src = n2->data;
	n1->data = string_substr(src, 0, src->size);
	return NULL;
}
