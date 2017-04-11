#include <stdio.h>
#include <string.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>

size_t count = 0;

void * destroy_hook(node_t * node) {
	// printf(">> Destroying '%s'\n", (char *)node->data);
}

void * f1(node_t * node, void * arg, size_t level) {
	node_append_child(node, node_create("1"))->destroy_hook = destroy_hook;
	node_append_child(node, node_create("2"))->destroy_hook = destroy_hook;
	node_append_child(node, node_create("3"))->destroy_hook = destroy_hook;
	count++;
	return NULL;
}

void * f2(node_t * node, void * arg, size_t level) {
	node_append_child(node, node_create("a"))->destroy_hook = destroy_hook;
	node_append_child(node, node_create("b"))->destroy_hook = destroy_hook;
	node_append_child(node, node_create("c"))->destroy_hook = destroy_hook;
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

	node_t * a = node_append_child(root, node_create("a"));
	node_t * b = node_append_child(root, node_create("b"));
	node_t * c = node_append_child(root, node_create("c"));

	node_swap(a, c);
	node_swap(a, c);

	// swap a & c
	// node_t * p = b->next;
	// node_attach_before(a->next, node_detach(b));
	// node_attach_before(p, node_detach(a));




	node_traverse_dflr_pre(root, print, NULL);
	node_destroy(root);
	return 0;
}
