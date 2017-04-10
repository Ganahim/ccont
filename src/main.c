#include <stdio.h>
#include <node_t.h>

void * f(node_t * node) {
	printf(">> %s destroyed\n", (char *)node->data);
}


int main()
{
	node_t * root = node_create("nigger");
	

	node_destroy(root);
	return 0;
}
