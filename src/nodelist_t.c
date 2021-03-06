#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <nodelist_t.h>
#include <node_t.h>


// extern void * node_destroy(node_t * node);



nodelist_t * nodelist_create() {
	nodelist_t * list = ALLOC(sizeof(nodelist_t));
	memset(list, 0, sizeof(nodelist_t));

	link_nodes(&list->rend, &list->end);

	return list;
}

void * nodelist_destroy(nodelist_t * list) {
	assert(list != NULL);

	void * r = NULL;
	if(list->destroy_hook != NULL) {
		r = list->destroy_hook(list);
	}

	while(nodelist_end(list) != nodelist_begin(list)) {
		nodelist_pop_back(list);
	}


	FREE(list);
	return r;
}





void nodelist_push_back(nodelist_t * list, node_t * node) {
	assert(list != NULL);
	assert(node != NULL);

	link_nodes(nodelist_end(list)->prev, node);
	link_nodes(node, nodelist_end(list));
}


void nodelist_pop_back(nodelist_t * list) {
	assert(list != NULL);
	assert(nodelist_end(list) != nodelist_begin(list));

	node_t * temp = nodelist_back(list);
	link_nodes(temp->prev, nodelist_end(list));
	node_destroy(temp);
}


node_t * nodelist_back(nodelist_t * list) {
	assert(list != NULL);
	assert(nodelist_end(list) != nodelist_begin(list));

	return nodelist_end(list)->prev;
}




void nodelist_push_front(nodelist_t * list, node_t * node) {
	assert(list != NULL);
	assert(node != NULL);

	link_nodes(node, nodelist_begin(list));
	link_nodes(nodelist_rend(list), node);
}

void nodelist_pop_front(nodelist_t * list) {
	assert(list != NULL);

	node_t * temp = nodelist_front(list);
	link_nodes(nodelist_rend(list), temp->next);
	node_destroy(temp);
}

node_t * nodelist_front(nodelist_t * list) {
	assert(list != NULL);
	return nodelist_begin(list);
}




/* Append the nodes of l2 at the end of l1, changing their parents that of l1. */
nodelist_t * nodelist_join(nodelist_t * l1, nodelist_t * l2) {
	assert(l1 != NULL);
	assert(l2 != NULL);

	while(nodelist_begin(l2) != nodelist_end(l2)) {
		node_t * p = node_detach(nodelist_front(l2));
		p->parent = nodelist_parent(l1);
		nodelist_push_back(l1, p);
	}

	nodelist_destroy(l2);

	return l1;
}


/* - Return a shallow copy of list.
	- See 'node_copy_shallow()' in file 'node_t.c' for more details. */
nodelist_t * nodelist_copy(nodelist_t * src) {
	assert(src != NULL);

	nodelist_t * dest = nodelist_create();

	for(node_t * p = nodelist_begin(src); p != nodelist_end(src); p = p->next) {
		nodelist_push_back(dest, node_copy_shallow(p));
	}

	return dest;
}



nodelist_t * nodelist_copy_deep(nodelist_t * src) {
	assert(src != NULL);

	nodelist_t * dest = nodelist_create();

	for(node_t * p = nodelist_begin(src); p != nodelist_end(src); p = p->next) {
		nodelist_push_back(dest, node_copy(p));
	}

	return dest;
}



void * nodelist_foreach(nodelist_t * list, node_action_t action, void * arg) {
	assert(list != NULL);
	assert(action != NULL);

	for(node_t * p = nodelist_begin(list); p != nodelist_end(list); p = p->next) {

		void * r = action(p, arg);

		if(r != NULL)
			return r;
	}

	return NULL;
}






/* helpers */
void link_nodes(node_t * p1, node_t * p2) {
	assert(p1 != NULL);
	assert(p2 != NULL);

	p1->next = p2;
	p2->prev = p1;
}

void unlink_nodes(node_t * p1, node_t * p2) {
	assert(p1 != NULL);
	assert(p2 != NULL);
	assert((p1->next = p2) || (p2->prev == p1));

	p1->next = NULL;
	p2->prev = NULL;
}
