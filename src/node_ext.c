#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <node_ext.h>


/* A pre-defined destroy hook that checks whether 'data' is NULL, and if not, calls FREE on it. */
void * node_simple_destroy_hook(node_t * node) {
	assert(node != NULL);

	if(node->data != NULL) {
		FREE(node->data);
		node->data = NULL;
	}

	return NULL;
}






node_t * string_node_create(const char * str) {
	assert(str != NULL);

	node_t * p = node_create(string_create(str));
	p->copy_hook = NODE_CALLBACK_T(string_node_copy_hook);
	p->destroy_hook = string_node_destroy_hook;

	return p;
}

void * string_node_destroy_hook(node_t * node) {
	assert(node != NULL);
	string_destroy((string_t *)node->data);
	return NULL;
}

void * string_node_copy_hook(node_t * n1, node_t * n2) {
	assert(n1 != NULL);
	assert(n2 != NULL);

	n1->data = string_copy(n2->data);
	return NULL;
}
