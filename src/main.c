#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <debug.h>

#include <node.h>
#include <string_t.h>


void * print_node(node_t * node, void * arg, size_t level);



int main()
{
	string_t * s = string_new("abcd");

	string_resize(s, 6);



	string_debug(s);
	string_delete(s);
	return 0;
}










void * print_node(node_t * node, void * arg, size_t level) {

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", (char *)node->data);
	}

	fputc('\n', stderr);

	return NULL;
}
