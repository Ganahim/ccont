#include <stdio.h>
#include <string.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>

size_t count = 0;

void * f1(node_t * node, void * arg, size_t level) {
	node_append_child(node, node_create("1"));
	node_append_child(node, node_create("2"));
	node_append_child(node, node_create("3"));
	count++;
	return NULL;
}

void * f2(node_t * node, void * arg, size_t level) {
	node_append_child(node, node_create("a"));
	node_append_child(node, node_create("b"));
	node_append_child(node, node_create("c"));
	count++;
	return NULL;
}

void * print(node_t * node, void * arg, size_t level) {
	for(size_t i = 0; i < level; i++)
		printf("  ");

	printf("%s\n", (char *)node->data);

	return NULL;
}


int main()
{
	node_t * root = node_create("root");


	node_traverse_dfrl_post(root, f2, NULL);
	node_traverse_dfrl_post(root, f1, NULL);
	node_traverse_dfrl_post(root, f2, NULL);
	node_traverse_dfrl_post(root, f1, NULL);
	node_traverse_dfrl_post(root, f2, NULL);
	node_traverse_dfrl_post(root, f1, NULL);
	node_traverse_dfrl_post(root, f2, NULL);
	node_traverse_dfrl_post(root, f1, NULL);

	// node_traverse_dflr_pre(root, print, NULL);

	printf("callbacks done: %zu\n", count);
	node_destroy(root);
	return 0;
}
