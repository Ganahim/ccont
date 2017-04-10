#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <node_t.h>


extern nodelist_t * nodelist_create();
extern void * nodelist_destroy(nodelist_t * list);






node_t * node_create(void * data) {
	node_t * node = ALLOC(sizeof(node_t));
	memset(node, 0, sizeof(node_t));

	node->children = nodelist_create();
	node->data = data;

	return node;
}

void * node_destroy(node_t * node) {
	assert(node != NULL);

	void * r = NULL;
	if(node->destroy_hook != NULL) {
		r = node->destroy_hook(node);
	}

	nodelist_destroy(node->children);

	FREE(node);
	return r;
}
