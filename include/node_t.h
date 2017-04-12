#ifndef _NODE_T_H
#define _NODE_T_H

#include <debug.h>
#include <stddef.h>
#include <types.h>


node_t * node_create(void * data);
void * node_destroy(node_t * node);
node_t * node_detach(node_t * node);


node_t * node_append_child(node_t * parent, node_t * child);
node_t * node_affix_child(node_t * parent, node_t * child);
node_t * node_attach_before(node_t * node1, node_t * node2);
node_t * node_attach_after(node_t * node1, node_t * node2);



node_t * node_copy(node_t * a);
void node_swap(node_t * a, node_t * b);


node_t * node_find_root(node_t * node);

//
// #ifndef NDEBUG
// void node_print(node_t * node);
// void _node_print(node_t * node, size_t level);
// #endif

#endif
