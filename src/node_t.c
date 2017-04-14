#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>


#ifndef NDEBUG
	int gNodeCount = 0;
	int gNodeCountPeak = 0;
#endif






node_t * node_create(void * data) {
	incNodeCount();

	node_t * node = ALLOC(sizeof(node_t));
	memset(node, 0, sizeof(node_t));

	node->children = nodelist_create();
	node->children->rend.parent = node;
	node->children->end.parent = node;
	node->data = data;

	return node;
}


/* Destroy node, freeing it's resources and those of it's descendants */
void * node_destroy(node_t * node) {
	assert(node != NULL);
	decNodeCount();

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


/* - Detach a range of nodes from their list, starting from begin and up to but not including end.
	- begin and end shall have the same parent, and begin shall appear before end in the list.
	- If either begin or end is an orphan, the behavior is undefined.
	- If the call is successful, a new list containing the specified range of nodes is returned.
	- The caller is responsible for destroying the returned list. */
nodelist_t * node_detach_range(node_t * begin, node_t * end) {
	assert(begin != NULL);
	assert(end != NULL);
	assert(begin->parent == end->parent);

	node_t * rend = begin->prev;
	nodelist_t * l = nodelist_create();

	while(rend->next != end) {
		nodelist_push_back(l, node_detach(rend->next));
	}

	return l;
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



/* Insert node2 before node1, taking the place of node1 and increasing the length of the list.
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

node_t * node_attach_after(node_t * node1, node_t * node2) {
	assert(node1);
	assert(node2);

	link_nodes(node2, node1->next);
	link_nodes(node1, node2);
	node2->parent = node1->parent;

	return node2;
}




/* - Return a shallow copy of node.
	- The 'data' member of the returned node will point to the same resource as src.
	- */
node_t * node_copy(node_t * src) {
	assert(src != NULL);
	incNodeCount();

	node_t * dest = ALLOC(sizeof(node_t));
	memset(dest, 0, sizeof(node_t));

	dest->children = nodelist_copy(src->children);
	dest->data = src->data;

	return dest;
}


void node_swap(node_t * a, node_t * b) {
	assert(a != NULL);
	assert(b != NULL);
	assert(a->parent != NULL);
	assert(b->parent != NULL);

	node_t * a_parent = a->parent;
	node_t * b_parent = b->parent;

	node_t * a_next = a->next;
	node_t * b_next = b->next;

	if(a->next == b) {
		node_attach_before(a, node_detach(b));
	}
	else if(b->next == a) {
		node_attach_before(b, node_detach(a));
	}
	else {
		node_attach_before(a, node_detach(b));
		node_attach_before(b_next, node_detach(a));
	}

	a->parent = b_parent;
	b->parent = a_parent;
}




node_t * node_find_root(node_t * node) {
	assert(node != NULL);

	node_t * p = node;
	while(p->parent != NULL)
		p = p->parent;

	return p;
}





typedef struct {
	node_search_predicate_t pred;
	void * arg;
	nodelist_t * list;
} pred_container_t;


void * _pred_wrapper(node_t * node, void * arg, size_t level) {
	assert(node != NULL);
	assert(arg != NULL);

	pred_container_t * cont = arg;

	if(cont->pred(node, cont->arg) != 0) {
		nodelist_push_back(cont->list, node_copy(node));
	}

	return NULL;
}


nodelist_t * node_search(node_t * node, node_search_predicate_t pred, void * arg) {
	assert(node != NULL);
	assert(pred != NULL);

	nodelist_t * l = nodelist_create();

	pred_container_t * cont = ALLOC(sizeof(pred_container_t));
	cont->pred = pred;
	cont->arg = arg;
	cont->list = l;

	node_traverse_dflr_pre(node, _pred_wrapper, cont);
	FREE(cont);

	return l;
}
