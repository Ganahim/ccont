#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <scanner.h>
#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>
#include <test.h>

void * print_node(node_t * node, void * arg, size_t level);
int get_nodes(node_t * node, void * vp);


int main()
{
	node_t * root = node_create("root");


	node_traverse_dflr_pre(root, print_node, NULL);
	node_destroy(root);
	return 0;
}






void * print_node(node_t * node, void * arg, size_t level) {
	assert(node != NULL);

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", node->data);
	}

	fputc('\n', stderr);

	return NULL;
}


int get_nodes(node_t * node, void * vp) {
	assert(node != NULL);
	assert(vp != NULL);
	assert(node->data != NULL);

	char * s1 = node->data;
	char * s2 = vp;

	if(strstr(s1, s2))
		return 1;


	return 0;
}
