#ifndef _NODE_ALGORITHM_H
#define _NODE_ALGORITHM_H

#include <types.h>
#include <node_t.h>
#include <nodelist_t.h>



#define NODE_TRAVERSE_DF 	0b000000
#define NODE_TRAVERSE_BF 	0b000001
#define NODE_TRAVERSE_PRE	0b000000
#define NODE_TRAVERSE_POST	0b000010
#define NODE_TRAVERSE_


void * node_traverse(node_t * node, node_traverse_action_t action, void * arg, size_t flags);


/* Depth-first, pre-order, left-right traversal */
void * node_traverse_dflr_pre(node_t * node, node_traverse_action_t action, void * arg);
void * _node_traverse_dflr_pre(node_t * node, node_traverse_action_t action, void * arg, size_t level);


/* Depth-first, pre-order, right-left traversal */
void * node_traverse_dfrl_pre(node_t * node, node_traverse_action_t action, void * arg);
void * _node_traverse_dfrl_pre(node_t * node, node_traverse_action_t action, void * arg, size_t level);


/* Depth-first, post-order, left-right traversal */
void * node_traverse_dflr_post(node_t * node, node_traverse_action_t action, void * arg);
void * _node_traverse_dflr_post(node_t * node, node_traverse_action_t action, void * arg, size_t level);


/* Depth-first, post-order, right-left traversal */
void * node_traverse_dfrl_post(node_t * node, node_traverse_action_t action, void * arg);
void * _node_traverse_dfrl_post(node_t * node, node_traverse_action_t action, void * arg, size_t level);


// TODO: breadth first algos

#endif
