#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <scanner.h>
#include <test.h>












void * node_clean(node_t * node) {
	assert(node != NULL);

	node_data_t * p = node->data;
	free(p->data);
	free(p);
	return NULL;
}


void build_source_tree(node_t * root, const char * buf) {
	YY_BUFFER_STATE handle = yy_scan_string(buf);
	int t = 0;
	node_t * p = root;


	while((t = yylex()) != 0) {
		switch(t) {
			case '{': {
				node_data_t * d = malloc(sizeof(node_data_t));
				d->type = NODE_TYPE_BRACE;
				d->data = NULL;
				p = node_append_child(p, node_create(d));
				p->destroy_hook = node_clean;
				break;
			}

			// case '}': {
			// 	p = p->parent;
			// 	break;
			// }

			case '(': {
				node_data_t * d = malloc(sizeof(node_data_t));
				d->type = NODE_TYPE_PAREN;
				d->data = NULL;
				p = node_append_child(p, node_create(d));
				p->destroy_hook = node_clean;
				break;
			}

			// case ')': {
			// 	p = p->parent;
			// 	break;
			// }


			case '[': {
				node_data_t * d = malloc(sizeof(node_data_t));
				d->type = NODE_TYPE_SQUARE;
				d->data = NULL;
				p = node_append_child(p, node_create(d));
				p->destroy_hook = node_clean;
				break;
			}

			// case ']': {
			// 	p = p->parent;
			// 	break;
			// }

			case '}':
			case ')':
			case ']':
				p = p->parent;
				break;

			default: {
				node_data_t * d = malloc(sizeof(node_data_t));
				d->type = NODE_TYPE_TEXT;
				d->data = malloc(yyleng+1);
				memcpy(d->data, yytext, yyleng+1);

				node_t * x = node_create(d);
				x->destroy_hook = node_clean;
				node_append_child(p, x);
				break;
			}
		}
	}

	yy_delete_buffer(handle);
}




void * print_node(node_t * node, void * arg, size_t level) {
	assert(node != NULL);
	assert(node->data != NULL);

	node_data_t * d = node->data;

	if(d->type == NODE_TYPE_TEXT) {
		for(size_t i = 0; i < level; i++)
			printf("   ");

		printf("%s\n", (char *)d->data);
	}

	return NULL;
}
