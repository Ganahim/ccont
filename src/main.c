#include <stdio.h>
#include <string.h>

#include <node_t.h>
#include <nodelist_t.h>





int main()
{
	node_t * root = node_create("root");

	node_t * a = node_create("a");
	node_t * b = node_create("b");
	node_t * c = node_create("c");



	node_append_child(root, a);
	node_append_child(root, b);
	node_append_child(root, c);


	node_print(root);
	node_destroy(root);
	return 0;
}
