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






node_t * string_node_create(string_t * str) {
	assert(str != NULL);

	node_t * p = node_create(str);
	p->copy_hook = NODE_CALLBACK_T(string_node_copy_hook);
	p->destroy_hook = string_node_destroy_hook;

	return p;
}

void * string_node_destroy_hook(node_t * node) {
	assert(node != NULL);
	FUNC_DEBUG("destroying '%s'", string_begin((string_t *)node->data));

	string_destroy((string_t *)node->data);
	return NULL;
}

void * string_node_copy_hook(node_t * n1, node_t * n2) {
	assert(n1 != NULL);
	assert(n2 != NULL);
	FUNC_DEBUG("");

	string_t * src = n2->data;
	n1->data = string_substr(src, 0, src->size);
	return NULL;
}
