#ifndef _NODE_EXT
#define _NODE_EXT

#include <containers_common.h>
#include <node.h>
#include <string_t.h>


void * node_simple_destroy_hook(node_t * node);


node_t * string_node_create(string_t * str);
void * string_node_destroy_hook(node_t * node);
void * string_node_copy_hook(node_t * n1, node_t * n2);

#endif
