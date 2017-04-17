#ifndef _NODE_EXT
#define _NODE_EXT

#include <containers_common.h>
#include <node.h>
#include <string_t.h>


extern void * node_simple_destroy_hook(node_t * node);
extern void * node_string_copy_hook(node_t * dest, node_t * src);


void * string_node_destroy_hook(node_t * node);
void * string_copy_hook(node_t * n1, node_t *n2);

#endif
