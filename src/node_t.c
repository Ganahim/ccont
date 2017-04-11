#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <node_t.h>
#include <nodelist_t.h>


// extern nodelist_t * nodelist_create();
// extern void * nodelist_destroy(nodelist_t * list);
// extern void link_nodes(node_t * p1, node_t * p2);
// extern void nodelist_push_back(nodelist_t * list, node_t * node);





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
	node->prev = NULL;
	node->next = NULL;
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






/* Same as above, but add to front */
node_t * node_affix_child(node_t * parent, node_t * child) {
	assert(parent != NULL);
	assert(child != NULL);

	nodelist_push_front(parent->children, child);
	child->parent = parent;
	return child;
}


/* Attach node2 before node1, taking the place of node1 and increasing the length of the list.
	node1 must be in a nodelist.
*/
node_t * node_attach_before(node_t * node1, node_t * node2) {
	assert(node1 != NULL);
	assert(node2 != NULL);

	link_nodes(node1->prev, node2);
	link_nodes(node2, node1);
	node2->parent = node1->parent;

	return node2;
}



/* Shallow copy */
node_t * node_copy(node_t * node) {
	assert(node != NULL);

	node_t * p = ALLOC(sizeof(node_t));
	memcpy(p, node, sizeof(node_t));
	return p;
}


void node_swap(node_t * a, node_t * b) {
	assert(a != NULL);
	assert(b != NULL);
	assert(a->parent != NULL);
	assert(b->parent != NULL);

	node_t * a_parent = a->parent;
	node_t * b_parent = b->parent;

	node_t * b_next = b->next;
	node_attach_before(a->next, node_detach(b))->parent = a_parent;
	node_attach_before(b_next, node_detach(a))->parent = b_parent;


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
