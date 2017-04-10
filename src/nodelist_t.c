#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <nodelist_t.h>


extern void * node_destroy(node_t * node);



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
	link_nodes(temp->prev, temp->next);
	node_destroy(temp);
}


node_t * nodelist_back(nodelist_t * list) {
	assert(list != NULL);
	assert(nodelist_end(list) != nodelist_begin(list));

	return nodelist_end(list)->prev;
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
