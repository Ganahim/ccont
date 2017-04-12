#ifndef _TEST_H
#define _TEST_H

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>

void * print_node(node_t * node, void * arg, size_t level);






typedef enum {
	NODE_TYPE_TEXT,
	NODE_TYPE_BRACE,
	NODE_TYPE_SQUARE,
	NODE_TYPE_PAREN
} NODE_TYPE;

typedef struct _NODE_DATA_T {
	NODE_TYPE type;
	void * data;
} node_data_t;


void * textnode_clean(node_t * node);

void build_source_tree(node_t * root, const char * buf);

#endif
