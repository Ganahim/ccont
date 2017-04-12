%top{

enum {
	TOK_ID = 1,
	TOK_NUM,
	TOK_FPNUM
};

}

%option nowarn
%option noyywrap
%option header-file="./build/scanner.h"


ID			[A-Za-z_][A-Za-z0-9_]*
NUM		[0-9]+
FPNUM		[0-9]*\.[0-9]+


%x STRING

%%
[\t\n ]+			/* ignore ws */
#.*				/* ignore */

["] {
	BEGIN(STRING);
}
<STRING>["] {

}


{ID}			return TOK_ID;
{NUM}			return TOK_NUM;
{FPNUM}		return TOK_FPNUM;


.				return yytext[0];
%%
