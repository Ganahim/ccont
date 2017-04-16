#ifndef _NODE_EXT
#define _NODE_EXT

#include <node_t.h>


extern void * node_simple_destroy_hook(node_t * node);
extern void * node_string_copy_hook(node_t * dest, node_t * src);


#endif
