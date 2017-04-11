#include <assert.h>
#include <node_algorithm.h>



void * node_traverse_dflr_pre(node_t * node, node_traverse_action_t action, void * arg) {
	assert(node != NULL);
	assert(action != NULL);

	return _node_traverse_dflr_pre(node, action, arg, 0);
}

void * _node_traverse_dflr_pre(node_t * node, node_traverse_action_t action, void * arg, size_t level) {
	void * r = NULL;

	r = action(node, arg, level);
	if(r != NULL)
		return r;

	for(node_t * p = nodelist_begin(node->children); p != nodelist_end(node->children); p = p->next) {
		r = _node_traverse_dflr_pre(p, action, arg, level + 1);
		if(r != NULL)
			return r;
	}

	return NULL;
}




/* Depth-first, pre-order, right-left traversal */
void * node_traverse_dfrl_pre(node_t * node, node_traverse_action_t action, void * arg) {
	assert(node != NULL);
	assert(action != NULL);

	return _node_traverse_dfrl_pre(node, action, arg, 0);
}

void * _node_traverse_dfrl_pre(node_t * node, node_traverse_action_t action, void * arg, size_t level) {
	void * r = NULL;

	r = action(node, arg, level);
	if(r != NULL)
		return r;

	for(node_t * p = nodelist_rbegin(node->children); p != nodelist_rend(node->children); p = p->prev) {
		r = _node_traverse_dfrl_pre(p, action, arg, level + 1);
		if(r != NULL)
			return r;
	}

	return NULL;
}




/* Depth-first, post-order, left-right traversal */
void * node_traverse_dflr_post(node_t * node, node_traverse_action_t action, void * arg) {
	assert(node != NULL);
	assert(action != NULL);

	return _node_traverse_dflr_post(node, action, arg, 0);
}

void * _node_traverse_dflr_post(node_t * node, node_traverse_action_t action, void * arg, size_t level) {
	void * r = NULL;

	for(node_t * p = nodelist_begin(node->children); p != nodelist_end(node->children); p = p->next) {
		r = _node_traverse_dflr_post(p, action, arg, level + 1);
		if(r != NULL)
			return r;
	}

	r = action(node, arg, level);
	if(r != NULL)
		return r;

	return NULL;
}




/* Depth-first, post-order, right-left traversal */
void * node_traverse_dfrl_post(node_t * node, node_traverse_action_t action, void * arg) {
	assert(node != NULL);
	assert(action != NULL);

	return _node_traverse_dfrl_post(node, action, arg, 0);
}

void * _node_traverse_dfrl_post(node_t * node, node_traverse_action_t action, void * arg, size_t level) {
	void * r = NULL;

	for(node_t * p = nodelist_rbegin(node->children); p != nodelist_rend(node->children); p = p->prev) {
		r = _node_traverse_dfrl_post(p, action, arg, level + 1);
		if(r != NULL)
			return r;
	}

	r = action(node, arg, level);
	if(r != NULL)
		return r;

	return NULL;
}
