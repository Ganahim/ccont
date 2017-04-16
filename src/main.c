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



void * string_node_destructor(node_t * node) {
	assert(node != NULL);
	FUNC_DEBUG("destroying %s", string_begin((string_t *)node->data));

	string_delete((string_t *)node->data);
	return NULL;
}

void * string_copy_hook(node_t * n1, node_t *n2) {
	assert(n1 != NULL);
	assert(n2 != NULL);
	FUNC_DEBUG("");

	string_t * src = n2->data;
	n1->data = string_substr(src, 0, src->size);
	return NULL;
}




int main()
{
	

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
