#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <node_t.h>


extern nodelist_t * nodelist_create();
extern void * nodelist_destroy(nodelist_t * list);
extern void link_nodes(node_t * p1, node_t * p2);
extern void nodelist_push_back(nodelist_t * list, node_t * node);





node_t * node_create(void * data) {
	node_t * node = ALLOC(sizeof(node_t));
	memset(node, 0, sizeof(node_t));

	node->children = nodelist_create();
	node->data = data;

	return node;
}


/* Destroy node, freeing it's resources and those of it's descendants */
void * node_destroy(node_t * node) {
	assert(node != NULL);
	// FUNC_DEBUG("%s", (char *)node->data);

	void * r = NULL;
	if(node->destroy_hook != NULL) {
		r = node->destroy_hook(node);
	}

	nodelist_destroy(node->children);

	FREE(node);
	return r;
}

/* Detach node without destroying it */
node_t * node_detach(node_t * node) {
	assert(node != NULL);
	assert(node->prev != NULL);
	assert(node->next != NULL);

	link_nodes(node->prev, node->next);
	node->parent = NULL;
	return node;
}



/* Make child a subnode of parent. If successful, parent will own child and all of it's descendants. */
node_t * node_append_child(node_t * parent, node_t * child) {
	assert(parent != NULL);
	assert(child != NULL);

	nodelist_push_back(parent->children, child);
	child->parent = parent;
	return child;
}






#ifndef NDEBUG
#include <stdio.h>

void node_print(node_t * node) {
	assert(node != NULL);
	_node_print(node, 0);
}

void _node_print(node_t * node, size_t level) {
	assert(node != NULL);

	for(size_t i = 0; i < level; i++)
		printf("  ");

	printf("%s\n", (char *)node->data);

	for(node_t * p = nodelist_begin(node->children); p != nodelist_end(node->children); p = p->next) {
		_node_print(p, level + 1);
	}
}
#endif
