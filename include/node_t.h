#ifndef _NODE_T_H
#define _NODE_T_H

#include <debug.h>
#include <stddef.h>
#include <types.h>


node_t * node_create(void * data);
void * node_destroy(node_t * node);
node_t * node_detach(node_t * node);

node_t * node_append_child(node_t * parent, node_t * child);





#ifndef NDEBUG
void node_print(node_t * node);
void _node_print(node_t * node, size_t level);
#endif

#endif
