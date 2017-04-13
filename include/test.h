#ifndef _TEST_H
#define _TEST_H

#include <node_t.h>


typedef struct _NODE_DATA_T {
	int token_id;

	union {
		long long data_int;
		long double data_float;
		void * data_vp;
	};
} node_data_t;


node_t * build_source_tree(const char * source_code);


#endif
