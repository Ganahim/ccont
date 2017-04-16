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


void * print_node(node_t * node, void * arg, size_t level);



int main()
{
	node_t * root = node_create("root");
	node_t * a = node_append_child(root, node_create("a"));
	node_t * b = node_append_child(root, node_create("b"));
	node_t * c = node_append_child(root, node_create("c"));
	node_t * d = node_append_child(root, node_create("d"));
	node_t * e = node_append_child(root, node_create("e"));


	node_traverse_dflr_pre(root, print_node, NULL);
	node_destroy(root);
	return 0;
}




















void * print_node(node_t * node, void * arg, size_t level) {

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", node->data);
	}

	fputc('\n', stderr);

	return NULL;
}
