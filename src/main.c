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



int main()
{
	node_t * root = node_create("root");

	node_t * a = node_append_child(root, node_create("a"));
	node_t * b = node_append_child(root, node_create("b"));
	node_t * c = node_append_child(root, node_create("c"));
	node_t * d = node_append_child(root, node_create("d"));
	node_t * e = node_append_child(root, node_create("e"));
	node_t * f = node_append_child(root, node_create("f"));
	node_t * g = node_append_child(root, node_create("g"));


	nodelist_t * l1 = node_detach_range(e, g->next);
	node_t * root2 = node_create("root2");
	nodelist_join(root2->children, l1);
	node_append_child(a, root2);
	node_t * x = node_copy(root);




	node_traverse_dflr_pre(root, print_node, NULL);
	putchar('\n');
	node_traverse_dflr_pre(x, print_node, NULL);


	node_destroy(root);
	node_destroy(x);
	return 0;
}
