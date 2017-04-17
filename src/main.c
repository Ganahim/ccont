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


size_t compute_min_capacity(size_t size) {
	size_t n = 1;
	while(n < size) {
		n <<= 1;
	}

	return n;
}



int main()
{
	printf("%zu\n", compute_min_capacity(65));

	debug_check_diff();
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
