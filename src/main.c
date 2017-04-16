#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <debug.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>
#include <node_ext.h>


void * print_node(node_t * node, void * arg, size_t level);



int main()
{

	return 0;
}




















void * print_node(node_t * node, void * arg, size_t level) {

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", (char *)node->data);
	}

	fputc('\n', stderr);

	return NULL;
}
