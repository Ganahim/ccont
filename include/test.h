#ifndef _TEST_H
#define _TEST_H

#define gprintf(...)		printf("\e[92m"); printf(__VA_ARGS__); printf("\e[0m")
#define rprintf(...)		printf("\e[91m"); printf(__VA_ARGS__); printf("\e[0m")

#include <stddef.h>
#include <node_t.h>




typedef struct _NODE_DATA_T {
	int token_id;

	union {
		long long data_int;
		double data_float;
		void * data_vp;
	};

#ifndef NDEBUG
	char repr[64];
#endif
} node_data_t;





node_t * build_source_tree(const char * source_code);
void * node_destructor(node_t * node);
void * textnode_destructor(node_t * node);
void * print_source_tree(node_t * node, void * arg, size_t level);




extern int symbols[];
#endif
