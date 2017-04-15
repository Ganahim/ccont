#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>
#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>
#include <resource.h>

void * print_node(node_t * node, void * arg, size_t level);





int main()
{
	init_global_resource_table();

	resource_handle_t r1 = resource_create(256);
	resource_handle_t r2 = resource_create(256);
	resource_handle_t r3 = resource_create(256);

	char * p = resource_get_data(r3);
	strcpy(p, "The quick brown fox jumped over the river.");

	for(int i = 0; i < 1000; i++) {
		resource_create(32);
	}

	printf("%s\n", (char *)resource_get_data(r3));

	// print_grt();

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
