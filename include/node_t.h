#ifndef _NODE_T_H
#define _NODE_T_H

#include <debug.h>
#include <types.h>


node_t * node_create(void * data);
void * node_destroy(node_t * node);


#endif
