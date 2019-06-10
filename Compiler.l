%{
#define YYSTYPE attributes
#include "tree.h"
#include "Compiler.tab.h"
#include <iostream>
using namespace std;

void comment(void);
void count(void);

int column = 0;
%}

%option yylineno

D			[0-9]
L			[a-zA-Z_]

%%

"/*"			{ comment();/*这种注释需要一个函数来去掉*/}
"//"[^\n]*      { /* 直接去掉行注释 */ }

"void"			{ count(); yylval.lineNo = yylineno;	return(VOID); 	}
"bool"			{ count(); yylval.lineNo = yylineno;  	return(BOOL); 	}
"int"			{ count(); yylval.lineNo = yylineno;  	return(INT); 	}
"double"		{ count(); yylval.lineNo = yylineno;  	return(DOUBLE); }
"char"			{ count(); yylval.lineNo = yylineno;	return(CHAR);}

"if"			{ count(); yylval.lineNo = yylineno;  	return(IF); 	}
"else"			{ count(); yylval.lineNo = yylineno;  	return(ELSE); 	}
"while"			{ count(); yylval.lineNo = yylineno; 	return(WHILE); 	}
"return"		{ count(); yylval.lineNo = yylineno;	return(RETURN); }

"true"			{ count(); 
					yylval.tokenContent = yytext; 
					yylval.lineNo = yylineno;
					yylval.st = create_tree(yytext, 0, yylineno);
					yylval.st->nodeType = "CONSTANT";			
				  	return(CONSTANT_BOOL); 	}
"false"			{ count();
					yylval.tokenContent = yytext; 
					yylval.lineNo = yylineno;
					yylval.st = create_tree(yytext, 0, yylineno);
					yylval.st->nodeType = "CONSTANT";				
					return(CONSTANT_BOOL); 	}

"+"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent="+";  	return(ADD_OP); }
"-"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent="-"; 	return(ADD_OP); }
"*"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent="*"; 	return(MUL_OP); }
"/"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent="/"; 	return(MUL_OP); }
"<"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent="<"; 	return(REL_OP); }
">"				{ count(); yylval.lineNo = yylineno; yylval.tokenContent=">"; 	return(REL_OP); }
"="				{ count(); yylval.lineNo = yylineno;  	return('='); 	}
";"				{ count(); yylval.lineNo = yylineno;  	return(';'); 	}
","				{ count(); yylval.lineNo = yylineno;  	return(','); 	}
"("				{ count(); yylval.lineNo = yylineno;  	return('('); 	}
")"				{ count(); yylval.lineNo = yylineno;  	return(')'); 	}
"["				{ count(); yylval.lineNo = yylineno;  	return('['); 	}
"]"				{ count(); yylval.lineNo = yylineno;  	return(']'); 	}
"{"				{ count(); yylval.lineNo = yylineno;  	return('{'); 	}
"}"				{ count(); yylval.lineNo = yylineno;  	return('}'); 	}

"<="			{ count(); yylval.lineNo = yylineno; yylval.tokenContent="<=";  	return(REL_OP);	}
">="			{ count(); yylval.lineNo = yylineno; yylval.tokenContent=">=";  	return(REL_OP);	}
"=="			{ count(); yylval.lineNo = yylineno; yylval.tokenContent="==";  	return(REL_OP);	}
"!="			{ count(); yylval.lineNo = yylineno; yylval.tokenContent="!=";  	return(REL_OP);	}

{L}({L}|{D})* 	{ count(); 
					yylval.tokenContent = yytext; 
					yylval.lineNo = yylineno; 
					yylval.st = create_tree(yytext, 0, yylineno);
					yylval.st->nodeType = "ID";
					return(IDENTIFIER);}

0|([1-9]{D}*)	{ count(); 
					yylval.tokenContent = yytext; 
					yylval.lineNo = yylineno;
					yylval.st = create_tree(yytext, 0, yylineno);	
					yylval.st->nodeType = "CONSTANT";				
					return(CONSTANT_INT);}

{D}+"."{D}*		{ count(); 
					yylval.tokenContent = yytext; 
					yylval.lineNo = yylineno;
					yylval.st = create_tree(yytext, 0, yylineno);
					yylval.st->nodeType = "CONSTANT";					
					return(CONSTANT_DOUBLE);}

[\t\v\n\f ]		{ count();}

%%
int yywrap() {
	return 1;
}

void comment(void) {
	column = 0;
	char c, prev = 0;
	
	while (c = fgetc(yyin))      /* (EOF maps to 0) *//*有问题*/
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	cerr << "unterminated comment" << endl;
}

void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 4 - (column % 4);
		else
			column++;
	//ECHO;
}
