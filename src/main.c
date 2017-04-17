#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <debug.h>

#include <node.h>
#include <string_t.h>


void * print_node(node_t * node, void * arg, size_t level);





int main()
{
	string_t * s = string_create("asdf");
	// node_t * proto = node_create("asd");
	//
	//
	//
	// node_destroy(proto);

	string_destroy(s);
	debug_print_alloc_report();
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
