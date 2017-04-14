#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <test.h>
#include <scanner.h>


node_t * build_source_tree(const char * source_code) {
	assert(source_code != NULL);
	YY_BUFFER_STATE bufstate = yy_scan_string(source_code);


	int t;					// token id

	node_t * root = node_create(NULL);
	node_t * p = root;

	while((t = yylex()) != 0) {
		node_data_t * nd = calloc(sizeof(node_data_t), 1);
		nd->token_id = t;
		node_t * cur = node_create(nd);

		switch(t) {
			case '(':
			case '{':
			case '[':
				p = node_append_child(p, cur);
				break;
			case ')':
			case '}':
			case ']':
				p = p->parent;
				break;

			case TOK_DEBUG:
			case TOK_ID:
				nd->data_vp = calloc(yyleng+1, 1);
				cur->destroy_hook = textnode_destructor;
				memcpy(nd->data_vp, yytext, yyleng);
				node_append_child(p, cur);
				break;
			case TOK_NUM:
				nd->data_int = strtol(yytext, NULL, 0);
				cur->destroy_hook = node_destructor;
				node_append_child(p, cur);
				break;
			case TOK_FPNUM:
				nd->data_float = strtod(yytext, NULL);
				cur->destroy_hook = node_destructor;
				node_append_child(p, cur);
				break;
			case TOK_STRLIT:
				nd->data_vp = calloc(strlit_len+1, 1);
				cur->destroy_hook = textnode_destructor;
				memcpy(nd->data_vp, strlit_buf, strlit_len);
				node_append_child(p, cur);
				break;

			case TOK_IF:
			case TOK_ELSE:
			case TOK_WHILE:
			case TOK_FOR:
			case TOK_SWITCH:
			case TOK_BREAK:
			case TOK_CONTINUE:
			case TOK_RETURN:
			case TOK_TRUE:
			case TOK_FALSE:
				node_append_child(p, cur);
				break;

			default:
				node_append_child(p, cur);
				break;
		}

	}


	yy_delete_buffer(bufstate);
	return root;
}




void * node_destructor(node_t * node) {
	assert(node != NULL);
	assert(node->data != NULL);

	free(node->data);

	return NULL;
}

void * textnode_destructor(node_t * node) {
	assert(node != NULL);
	assert(((node_data_t *)node->data)->data_vp != NULL);

	free(((node_data_t *)node->data)->data_vp);
	free(node->data);

	return NULL;
}





void * print_source_tree(node_t * node, void * arg, size_t level) {
	assert(node != NULL);

	for(size_t i = 0; i < level; i++)
		printf("   ");

	if(node->data == NULL) {
		printf("[root]\n");
		return NULL;
	}

	node_data_t * nd = node->data;
	if(nd->token_id < 256) {
		printf("%c\n", (char)nd->token_id);
		return NULL;
	}

	switch(nd->token_id) {
		case TOK_ID:
			printf("%s", (char *)nd->data_vp);
			break;
		case TOK_DEBUG:
			rprintf("%s", (char *)nd->data_vp);
			break;
		case TOK_NUM:
			printf("%jd", nd->data_int);
			break;
		case TOK_FPNUM:
			printf("%g", nd->data_float);
			break;
		case TOK_STRLIT:
			printf("\"%s\"", (char *)nd->data_vp);
			break;

		case TOK_IF:			gprintf("if"); break;
		case TOK_ELSE:			gprintf("else"); break;
		case TOK_WHILE:		gprintf("while"); break;
		case TOK_FOR:			gprintf("for"); break;
		case TOK_SWITCH:		gprintf("switch"); break;
		case TOK_BREAK:		gprintf("break"); break;
		case TOK_CONTINUE:	gprintf("continue"); break;
		case TOK_RETURN:		gprintf("return"); break;
		case TOK_TRUE:			gprintf("true"); break;
		case TOK_FALSE:		gprintf("false"); break;
			break;

		default:
			printf("[unknown]");
			break;
	}

	putchar('\n');
	return NULL;
}





enum {
	SYM_EQU
};

int symbols[] = {
	SYM_EQU,
	'=', '=',
	0,
	0
};



//
