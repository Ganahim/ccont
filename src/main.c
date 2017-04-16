#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <debug.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>
#include <node_ext.h>


void * print_node(node_t * node, void * arg, size_t level);


void * f1(node_t * node, void * arg, size_t level) {
	assert(node != NULL);
	assert(node->data != NULL);

	size_t n = strlen((char *)node->data) + 1;

	char * src = (char *)node->data;
	char * d1 = malloc(n);
	char * d2 = malloc(n);

	strcpy(d1, src);
	strcpy(d2, src);

	for(size_t i = 0; i < (n-1); i++) {
		d1[i]--;
		d2[i]++;
	}

	node_t * n1 = node_create(d1);
	n1->destroy_hook = node_simple_destroy_hook;
	node_append_child(node, n1);

	node_t * n2 = node_create(d2);
	n2->destroy_hook = node_simple_destroy_hook;
	node_append_child(node, n2);

	return NULL;
}

char * make_str(const char * s) {
	char * d = malloc(strlen(s)+1);
	return strcpy(d, s);
}

int main()
{
	node_t * root = node_create("root");
	node_t * a = node_append_child(root, node_create("a"));
	node_t * b = node_append_child(root, node_create(make_str("b")));
	b->copy_hook = (node_callback_t) node_string_copy_hook;
	b->destroy_hook = (node_callback_t) node_simple_destroy_hook;

	node_t * c = node_append_child(root, node_create("c"));
	node_t * d = node_append_child(root, node_create("d"));
	node_t * e = node_append_child(root, node_create("e"));
	node_traverse_dflr_post(root, f1, NULL);


	node_t * root2 = node_copy_deep(root);
	((char *)b->data)[0] = 'X';




	node_traverse_dflr_pre(root, print_node, NULL); putchar('\n');
	node_traverse_dflr_pre(root2, print_node, NULL);
	node_destroy(root);
	node_destroy(root2);
	return 0;
}




















void * print_node(node_t * node, void * arg, size_t level) {

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", node->data);
	}

	fputc('\n', stderr);

	return NULL;
}
