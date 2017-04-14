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
int get_nodes(node_t * node, void * vp);




int main()
{
	init_global_resource_table();

	resource_handle_t r1 = resource_create(256);
	resource_handle_t r2 = resource_create(256);
	resource_handle_t r3 = resource_create(256);

	FUNC_DEBUG("r1 == %zu", r1);
	resource_t * p1 = resource_get(r1);

	strcpy(p1->data, "Hello, world!");


	printf("%s\n", (char *)resource_get(r1)->data);

	return 0;
}






void * print_node(node_t * node, void * arg, size_t level) {
	assert(node != NULL);

	for(size_t i = 0; i < level; i++)
		fprintf(stderr, "   ");

	if(node->data != NULL) {
		fprintf(stderr, "%s", node->data);
	}

	fputc('\n', stderr);

	return NULL;
}


int get_nodes(node_t * node, void * vp) {
	assert(node != NULL);
	assert(vp != NULL);
	assert(node->data != NULL);

	char * s1 = node->data;
	char * s2 = vp;

	if(strstr(s1, s2))
		return 1;


	return 0;
}
