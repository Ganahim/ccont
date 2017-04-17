#ifndef _NODE_T_H
#define _NODE_T_H

#include <debug.h>
#include <stddef.h>
#include <node_types.h>


node_t * node_create(void * data);
void * node_destroy(node_t * node);
node_t * node_detach(node_t * node);
nodelist_t * node_detach_range(node_t * begin, node_t * end);


node_t * node_append_child(node_t * parent, node_t * child);
node_t * node_affix_child(node_t * parent, node_t * child);
node_t * node_attach_before(node_t * node1, node_t * node2);
node_t * node_attach_after(node_t * node1, node_t * node2);


node_t * node_copy_shallow(node_t * src);
node_t * node_copy(node_t * src);
void node_swap(node_t * a, node_t * b);
node_t * node_find_root(node_t * node);
nodelist_t * node_search(node_t * node, node_search_predicate_t pred, void * arg);




#ifndef NDEBUG
	extern int gNodeCount;
	extern int gNodeCountPeak;
#	define incNodeCount()	{ gNodeCount++; gNodeCountPeak++; }
#	define decNodeCount()	{ gNodeCount--; }
#else
#	define incNodeCount()
#	define decNodeCount()
#endif

#endif
