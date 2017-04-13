#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <test.h>
#include <scanner.h>


node_t * build_source_tree(const char * source_code) {
	assert(source_code != NULL);
	YY_BUFFER_STATE bufstate = yy_scan_string(source_code);


	int t;					// token id

	node_data_t rootdata = { 0 };
	node_t * root = node_create(&rootdata);
	node_t * cur = root;

	while((t = yylex()) != 0) {
		node_data_t * nd = malloc(sizeof(node_data_t));
		nd->token_id = t;

		switch(t) {
			case '(':
			case '{':
			case '[':
				cur = node_append_child(cur, node_create(nd));
				break;
			case ')':
			case '}':
			case ']':
				cur = cur->parent;
				break;

			case TOK_STRLIT:
				break;
			default:
				break;
		}

	}


	yy_delete_buffer(bufstate);
}
