#ifndef _NODELIST_T_H
#define _NODELIST_T_H

#include <containers_common.h>
#include <node_types.h>


nodelist_t * nodelist_create();
void * nodelist_destroy(nodelist_t * list);

void nodelist_push_back(nodelist_t * list, node_t * node);
void nodelist_pop_back(nodelist_t * list);
node_t * nodelist_back(nodelist_t * list);

void nodelist_push_front(nodelist_t * list, node_t * node);
void nodelist_pop_front(nodelist_t * list);
node_t * nodelist_front(nodelist_t * list);


nodelist_t * nodelist_join(nodelist_t * l1, nodelist_t * l2);
nodelist_t * nodelist_copy(nodelist_t * src);
nodelist_t * nodelist_copy_deep(nodelist_t * src);


void * nodelist_foreach(nodelist_t * list, node_action_t action, void * arg);


/* helper functions */
void link_nodes(node_t * p1, node_t * p2);
void unlink_nodes(node_t * p1, node_t * p2);

#endif
