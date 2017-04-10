#include <stdio.h>

#include <node_t.h>
#include <nodelist_t.h>



void * f(node_t * node) {
	printf(">> %s destroyed\n", (char *)node->data);
}


void * f2(node_t * node, void * arg) {
	printf("%s\n", (char *)node->data);
	return NULL;
}


int main()
{
	node_t * root = node_create("nigger");

	nodelist_push_back(root->children, node_create("a"));
	nodelist_push_back(root->children, node_create("b"));
	nodelist_push_back(root->children, node_create("c"));


	nodelist_foreach(root->children, f2, NULL);
	// for(node_t * p = nodelist_begin(root->children); p != nodelist_end(root->children); p = p->next) {
	// 	printf("%s\n", (char *)p->data);
	// }


	node_destroy(root);
	return 0;
}
