#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <node_t.h>
#include <nodelist_t.h>
#include <node_algorithm.h>
#include <test.h>

#include <scanner.h>



int main()
{
	node_data_t d = {0, "root"};
	node_t * root = node_create(&d);


	FILE * fp = fopen("src/main.c", "rb");
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);

	char * buf = calloc(1, size + 1);
	fread(buf, 1, size, fp);

	build_source_tree(root, buf);


	node_traverse_dflr_pre(root, print_node, NULL);
	node_destroy(root);
	return 0;
}
