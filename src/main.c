#include <stdio.h>
#include <string.h>

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

	nodelist_push_front(root->children, node_create("wat"));
	nodelist_push_front(root->children, node_create("kek"));
	nodelist_push_front(root->children, node_create("lol"));


	for(node_t * p = nodelist_begin(root->children); p != nodelist_end(root->children); p = p->next) {
		if(strcmp((char *)p->data, "c") == 0) {
			node_detach(p);
			node_destroy(p);
		}
	}


	nodelist_foreach(root->children, f2, NULL);


	node_destroy(root);
	return 0;
}
