#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include <debug.h>
#include <node.h>
#include <string_t.h>

void * print_string_node(node_t * node, void * arg, size_t level);
void * f1(node_t * node, void * arg, size_t level);
void * f2(node_t * node, void * arg, size_t level);





int main()
{
	node_t * root = string_node_create("root");

	

	node_destroy(root);
	debug_check_diff();
	return 0;
}



void * print_string_node(node_t * node, void * arg, size_t level) {
	assert(node != NULL);

	for(size_t i = 0; i < level; i++) {
		fprintf(stderr, "   ");
	}

	fprintf(stderr, "%s", string_begin((string_t *)node->data));
	fputc('\n', stderr);
	return NULL;
}



void * f1(node_t * node, void * arg, size_t level) {
	node_append_child(node, string_node_create("a"));
	node_append_child(node, string_node_create("b"));
	node_append_child(node, string_node_create("c"));
	return NULL;
}

void * f2(node_t * node, void * arg, size_t level) {
	node_append_child(node, string_node_create("1"));
	node_append_child(node, string_node_create("2"));
	node_append_child(node, string_node_create("3"));

	for(node_t * p = nodelist_begin(node->children); p != nodelist_end(node->children); p = p->next) {
		string_insert((string_t *)p->data, 0, (string_t *)node->data);
	}
	return NULL;
}
