#ifndef _CONTAINER_TYPES_H
#define _CONTAINER_TYPES_H

#include <stddef.h>

#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif




struct _NODE_T;
struct _NODELIST_T;


typedef void * (*node_callback_t)(struct _NODE_T *);
typedef void * (*node_copy_hook_t)(struct _NODE_T * dest, struct _NODE_T * src);
typedef void * (*nodelist_callback_t)(struct _NODELIST_T *);
typedef void * (*node_action_t)(struct _NODE_T *, void *);
typedef void * (*node_traverse_action_t)(struct _NODE_T *, void *, size_t level);
typedef int (*node_search_predicate_t)(struct _NODE_T *, void *);



typedef struct _NODE_T {
	struct _NODE_T * prev;
	struct _NODE_T * next;
	struct _NODE_T * parent;
	struct _NODELIST_T * children;
	void * data;
	node_callback_t destroy_hook;
	node_callback_t copy_hook;
} node_t;




typedef struct _NODELIST_T {
	node_t rend;
	node_t end;
	nodelist_callback_t destroy_hook;	// NOTE: rethink
} nodelist_t;

#define nodelist_begin(P)		((P)->rend.next)
#define nodelist_rbegin(P)		((P)->end.prev)
#define nodelist_end(P)			(&(P)->end)
#define nodelist_rend(P)		(&(P)->rend)
#define nodelist_parent(P)		((P)->end.parent)


#endif
