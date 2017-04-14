%option header-file="build/scanner.h"
%option never-interactive

%top{

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef NDEBUG
#	include <stdio.h>
#	define DEBUG(...)		fprintf(stderr, ">> %s():", __func__); fprintf(stderr, " "__VA_ARGS__); fputc('\n', stderr);
#else
#	define DEBUG(...)
#endif

#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif

#ifndef REALLOC
#	define REALLOC(...)	realloc(__VA_ARGS__)
#endif

#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif

#ifndef PAGESIZE
#	define PAGESIZE 4096
#endif



/* Token types */
enum {
	TOK_ID = 300,
	TOK_NUM,
	TOK_FPNUM,
	TOK_STRLIT,

	/* Keywords */
	TOK_IF = 400,
	TOK_ELSE,
	TOK_WHILE,
	TOK_FOR,
	TOK_SWITCH,
	TOK_BREAK,
	TOK_CONTINUE,
	TOK_RETURN,
	TOK_TRUE,
	TOK_FALSE,

	TOK_DEBUG
};


/* declare buffer related variables */
extern char * strlit_buf;
extern size_t strlit_bufsize;
extern size_t strlit_len;

/* declare our dummy yywrap */
extern int yywrap();
}
%{
char * strlit_buf = NULL;
size_t strlit_bufsize = 0;
size_t strlit_len = 0;
%}
/* END OF CODE SECTION */


ID					[A-Za-z_][A-Za-z0-9_]*
NUM				[0-9]+
FPNUM				[0-9]*\.[0-9]+
HEX_CHAR			[A-Fa-f0-9]
ESC_HEX			\\x{HEX_CHAR}{1,2}
%x STRLIT




/******************************************** RULES ***************************************************/
%%
	/* function local variables */
	char * p = NULL;

	/* ignore white space */
[\t\n ]+


	/* string literal related rules */
["] {
	BEGIN(STRLIT);
	strlit_bufsize = PAGESIZE;
	strlit_buf = REALLOC(strlit_buf, strlit_bufsize);
	p = strlit_buf;
}

<STRLIT>\\n					*p = '\n'; p++;
<STRLIT>\\t					*p = '\t'; p++;
<STRLIT>\\v					*p = '\v'; p++;
<STRLIT>\\b					*p = '\b'; p++;
<STRLIT>\\\\				*p = '\\'; p++;

<STRLIT>{ESC_HEX}			*p = (unsigned char)strtoul(yytext+2, NULL, 16); p++;

<STRLIT>[^"] {

	/* realloc if necessary */
	if(((p - strlit_buf) + yyleng + 1) >= strlit_bufsize) {
		strlit_bufsize += PAGESIZE;
		strlit_buf = REALLOC(strlit_buf, strlit_bufsize);
	}

	*p = yytext[0];
	p++;
}


<STRLIT>["] {
	BEGIN(0);
	*p = 0;
	strlit_len = (p - strlit_buf);
	p = NULL;
	return TOK_STRLIT;
}


	/* keywords */
"if"			return TOK_IF;
"else"		return TOK_ELSE;
"while"		return TOK_WHILE;
"for"			return TOK_FOR;
"switch"		return TOK_SWITCH;
"break"		return TOK_BREAK;
"continue"	return TOK_CONTINUE;
"return"		return TOK_RETURN;
"true"		return TOK_TRUE;
"false"		return TOK_FALSE;


	/* misc rules */
{ID}			return TOK_ID;
{NUM}			return TOK_NUM;
{FPNUM}		return TOK_FPNUM;

.				return yytext[0];

<<EOF>> {
	FREE(strlit_buf);
	return 0;
}
%%

int yywrap() {
	return 1;
}
