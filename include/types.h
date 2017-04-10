#ifndef _CONTAINER_TYPES_H
#define _CONTAINER_TYPES_H


#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif




struct _NODE_T;
struct _NODELIST_T;

typedef void * (*node_callback_t)(struct _NODE_T *);



typedef struct _NODE_T {
	struct _NODE_T * prev;
	struct _NODE_T * next;
	struct _NODE_T * parent;
	struct _NODELIST_T * children;
	void * data;
	node_callback_t destroy_hook;
} node_t;




typedef struct _NODELIST_T {
	node_t rend;
	node_t end;
	node_callback_t destroy_hook;
} nodelist_t;


#endif
