#include <test.h>


void * print(node_t * node, void * arg, size_t level) {
	for(size_t i = 0; i < level; i++)
		printf("  ");

	printf("%s\n", (char *)node->data);

	return NULL;
}
