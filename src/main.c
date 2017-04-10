#include <stdio.h>
#include <string.h>

#include <node_t.h>
#include <nodelist_t.h>



void * f1(node_t * node, void * arg) {
	node_append_child(node, node_create("1"));
	node_append_child(node, node_create("2"));
	node_append_child(node, node_create("3"));
	return NULL;
}


void * f2(node_t * node) {
	printf("Destroying %s\n", (char *)node->data);
	return NULL;
}


int main()
{
	node_t * root = node_create("nigger");

	node_append_child(root, node_create("a"));
	node_append_child(root, node_create("b"));
	node_append_child(root, node_create("c"));

	nodelist_foreach(root->children, f1, NULL);


	node_t * x = node_create("x");
	node_append_child(root, x);
	printf("%s\n", (char *)x->parent->data);

	// node_print(root);
	node_destroy(root);
	return 0;
}
