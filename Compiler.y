%{
#define YYSTYPE attributes
#include <cstdio>
#include <map>
#include "tree.h"
#include "table.h"
#include "draw.h" 
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern int yylineno;

treeNode *root;//the root node of the syntax tree
SymbolTable symTable;// the symbol table
int resState;//the buffer to show the state of the symbol in table (found or not found)
vector<string> funcPaTypes;// buffer of the parameters of the function, used to insert paras into tables when function declaration
vector<string> funcPaNames;// buffer of the parameters of the function, used to insert paras into tables when function declaration
int isFuncStatement = 0;//to show if a compound statement belongs to a function delaration, which compiler need to add the parameters into the symbol table 
map<string,bool> funcDefined;//to show a function is defined or not

int yylex(void);
void yyerror(const char*); 

%}

%token IDENTIFIER CONSTANT_INT CONSTANT_DOUBLE CONSTANT_BOOL
%token ADD_OP MUL_OP REL_OP
%token BOOL INT DOUBLE VOID
%token IF ELSE WHILE RETURN

%token ';' ',' '=' '[' ']' '{' '}' '(' ')'

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

Program:
	declaration_list { 
		root = create_tree("Program", 1, -1, $1.st);
		
		root->nodeType = "PROGRAM";
	};

declaration_list:
	declaration_list declaration {
		$$.st = create_tree("declaration_list", 2, -1, $1.st, $2.st);
		$$.st->nodeType = "DECLARATION";
		$$.lineNo = $1.lineNo;
	}
	| declaration {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
	};

declaration:
	var_declaration {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
	}
	| fun_definition {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
	}
	| fun_declaration {
		//TODO
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
	};

var_declaration:
	type_specifier IDENTIFIER ';' {
		$$.st = create_tree("var_declaration", 2, -1, $1.st, $2.st);
		$$.st->nodeType = "VAR_DECLARATION";
		$$.lineNo = $1.lineNo;
		
		//insert into symbol table
		resState = symTable.insertSymbol($2.st->nodeName, $1.st->nodeName);
		if(resState == -1){
			cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $2.st->nodeName << " has been defined." << endl; 
		}
	}
	| type_specifier IDENTIFIER '=' simple_expression ';' {
		//TODO
		$$.st = create_tree("var_declaration_with_initial", 3, -1, $1.st, $2.st, $4.st);
		$$.st->nodeType = "VAR_DECLARATION_WITH_INITIAL";
		$$.lineNo = $1.lineNo;
		
		//insert into symbol table
		resState = symTable.insertSymbol($2.st->nodeName, $1.st->nodeName);
		if(resState == -1){
			cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $2.st->nodeName << " has been defined." << endl; 
		}
		else{
			//check type
			if($1.st->nodeName != $4.type){
				cout << "[Compile Error] Line:" << $$.lineNo << " initializer should be type " << $1.st->nodeName << " but not " << $4.type << endl; 
			}
		}	
	}
	| type_specifier IDENTIFIER '[' CONSTANT_INT ']' ';' {
		$$.st = create_tree("var_declaration", 3, -1, $1.st, $2.st, $4.st);
		$$.st->nodeType = "VAR_ARRAY_DECLARATION";
		$$.lineNo = $1.lineNo;
		
		resState = symTable.insertSymbol($2.st->nodeName, $1.st->nodeName+"*");
		if(resState == -1){
			cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $2.st->nodeName << " has been defined." << endl; 
		}
	};

type_specifier:
	INT {
		$$.st = create_tree("INT", 0, -1);
		$$.st->nodeType = "TYPE";
		$$.lineNo = $1.lineNo;
	}
	| VOID {
		$$.st = create_tree("VOID", 0, -1);
		$$.st->nodeType = "TYPE";
		$$.lineNo = $1.lineNo;
	}
	| BOOL {
		$$.st = create_tree("BOOL", 0, -1);
		$$.st->nodeType = "TYPE";
		$$.lineNo = $1.lineNo;
	}
	| DOUBLE {
		$$.st = create_tree("DOUBLE", 0, -1);
		$$.st->nodeType = "TYPE";
		$$.lineNo = $1.lineNo;
	};

fun_declaration:
	type_specifier IDENTIFIER '(' para_starts params ')' ';' {
		//TODO
		$$.st = create_tree("fun_declaration", 3, -1, $1.st, $2.st, $5.st);
		$$.st->nodeType = "FUN_DECLARATION";
		$$.lineNo = $1.lineNo;
		
		resState = symTable.insertSymbol($2.st->nodeName, $1.st->nodeName + " " + $5.funcParas);
		if(resState == -1){
			cout << "[Compile Error] Line:" << $$.lineNo << " function " << $2.st->nodeName << " has been declared." << endl; 
		}
		else{
			funcDefined[$2.st->nodeName]=false;
		}
		
	};

fun_definition:
	type_specifier IDENTIFIER '(' para_starts params ')' compound_stmt {
		$$.st = create_tree("fun_definition", 4, -1, $1.st, $2.st, $5.st, $7.st);
		$$.st->nodeType = "FUN_DEFINITION";
		$$.lineNo = $1.lineNo;
		
		resState = symTable.insertSymbol($2.st->nodeName, $1.st->nodeName + " " + $5.funcParas);
		if(resState == -1 && funcDefined[$2.st->nodeName] == true){
			cout << "[Compile Error] Line:" << $$.lineNo << " function " << $2.st->nodeName << " has been defined." << endl; 
		}
		
		funcDefined[$2.st->nodeName]=true;
		
		if($7.type != $1.st->nodeName){
			cout << "[Compile Error] Line:" << $$.lineNo << " return value type in statement is not " << $1.st->nodeName << endl; 
		}
	};

para_starts:
	/*epsilon*/
	{
		for(int i = 0; i < funcPaTypes.size(); i++){
			funcPaTypes.pop_back();
			funcPaNames.pop_back();
		}
		isFuncStatement = 1;
	};

params:
	params_list {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = $1.funcParas;
	}
	| VOID {
		$$.st = create_tree("VOID", 0, -1);
		$$.st->nodeType = "VOID";
		
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = "VOID";
	};

params_list:
	params_list ',' param {
		$$.st = create_tree("params_list", 2, -1, $1.st, $3.st);
		$$.st->nodeType = "PARAMS";
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = $1.funcParas + " " + $3.funcParas;
	}
	| param {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = $1.funcParas;
	};

param:
	type_specifier IDENTIFIER {
		$$.st = create_tree("param", 2, -1, $1.st, $2.st);
		$$.st->nodeType = "PARAM";
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = $1.st->nodeName;
		funcPaTypes.push_back($1.st->nodeName);
		funcPaNames.push_back($2.st->nodeName);	
	}
	| type_specifier IDENTIFIER '[' ']' {
		$$.st = create_tree("param_array", 2, -1, $1.st, $2.st);
		$1.st->nodeName = $1.st->nodeName + "*"; 
		$$.st->nodeType = "PARAM";
		$$.lineNo = $1.lineNo;
		
		$$.funcParas = $1.st->nodeName;
		funcPaTypes.push_back($1.st->nodeName+"*");
		funcPaNames.push_back($2.st->nodeName);	
	};

compound_stmt:
	compound_stmt_start local_declarations statement_list compound_stmt_end {
		$$.st = create_tree("compound_stmt",2,-1,$2.st,$3.st);
		$$.st->nodeType = "COM_STATEMENTS";
		$$.lineNo = $1.lineNo;	 
		
		$$.type = $3.type; 
	};

compound_stmt_start:
	'{' {
		symTable.createTable();
		
		if(isFuncStatement == 1){
			for(int i = 0; i < funcPaTypes.size(); i++){
				resState = symTable.insertSymbol(funcPaNames[i], funcPaTypes[i]);
				if(resState == -1){
					cout << "[Compile Error] Line:" << $1.lineNo << " function parameters name should be different." << endl; 
				}
			}
		}
	};
	
compound_stmt_end:
	'}' {
		symTable.deleteTable();
	};

local_declarations: /*可为空*/{
		$$.st = NULL;
	}
	| local_declarations var_declaration {
		$$.st = create_tree("local_declarations",2,-1,$1.st,$2.st);
		$$.st->nodeType = "DECLARATION";
		$$.lineNo = $1.lineNo;
	};

statement_list: /*可为空*/{
		$$.st = NULL;
		
		$$.type = "STATEMENT";
	}
	| statement_list statement {
		$$.st = create_tree("statement_list",2,-1,$1.st,$2.st);
		$$.st->nodeType = "STATEMENTS";
		$$.lineNo = $1.lineNo;
		
		if($1.type != "STATEMENT" && $2.type != "STATEMENT"){
			if($1.type != $2.type){
				cout << "[Compile Error] Line:" << $2.lineNo << " there exist two return statement with different value." << endl; 
				$$.type = $1.type; 
			}
			else{
				$$.type = $1.type; 
			}
		}
		else if($1.type == "STATEMENT" && $2.type == "STATEMENT"){
			$$.type = "STATEMENT";
		}
		else if($1.type == "STATEMENT" && $2.type != "STATEMENT"){
			$$.type = $2.type;
		}
		else{
			$$.type = $1.type;
		}
	};

statement:
	expression_stmt {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = "STATEMENT"; 
		
	}
	| compound_stmt {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	}
	| selection_stmt {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	}
	| iteration_stmt {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	}
	| return_stmt {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

expression_stmt:
	expression ';' {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
	}
	| ';' {$$.st = NULL;$$.lineNo = $1.lineNo;};

selection_stmt:
	IF '(' expression ')' statement %prec LOWER_THAN_ELSE{
		$$.st = create_tree("IF", 2, -1, $3.st, $5.st);
		$$.st->nodeType = "IF";
		$$.lineNo = $1.lineNo;
		
		if($3.type != "BOOL"){
			cout << "[Compile Error] Line:" << $3.lineNo << " the value of the branch condition should be a bool" << endl; 
		}
		$$.type = $5.type;
	}
	| IF '(' expression ')' statement ELSE statement {
		$$.st = create_tree("IF_ELSE", 3, -1, $3.st, $5.st, $7.st);
		$$.st->nodeType = "IF_ELSE";
		$$.lineNo = $1.lineNo;
		
		if($3.type != "BOOL"){
			cout << "[Compile Error] Line:" << $3.lineNo << " the value of the branch condition should be a bool" << endl; 
		}
		
		if($5.type != "STATEMENT" && $7.type != "STATEMENT"){
			if($5.type != $7.type){
				cout << "[Compile Error] Line:" << $5.lineNo << " there exist two return statement with different value." << endl; 
				$$.type = $5.type; 
			}
			else{
				$$.type = $5.type; 
			}
		}
		else if($5.type == "STATEMENT" && $7.type == "STATEMENT"){
			$$.type = "STATEMENT";
		}
		else if($5.type == "STATEMENT" && $7.type != "STATEMENT"){
			$$.type = $7.type;
		}
		else{
			$$.type = $5.type;
		}
	};

iteration_stmt:
	WHILE '(' expression ')' statement {
		$$.st = create_tree("WHILE", 2, -1, $3.st, $5.st);
		$$.st->nodeType = "WHILE";
		$$.lineNo = $1.lineNo;
		
		if($3.type != "BOOL"){
			cout << "[Compile Error] Line:" << $3.lineNo << " the value of the branch condition should be a bool" << endl; 
		}
		
		$$.type = $5.type;
	};

return_stmt:
	RETURN ';' {
		$$.st = create_tree("RETURN", 0, -1);
		$$.st->nodeType = "RETURN";
		$$.lineNo = $1.lineNo;
		
		$$.type = "VOID";
	}
	| RETURN expression ';' {
		$$.st = create_tree("RETURN", 1, -1, $2.st);
		$$.st->nodeType = "RETURN";
		$$.lineNo = $1.lineNo;
		
		$$.type = $2.type;
	};

expression:
	var '=' expression {
		$$.st = create_tree("=", 2, -1, $1.st, $3.st);
		$$.st->nodeType = "ASSIGNMENT";
		$$.lineNo = $1.lineNo;
		
		if($1.type != $3.type){
			cout << "[Compile Error] Line:" << $$.lineNo << " type " << $3.type << " cannot assigned to variable " << $1.st->nodeName << endl; 
			$$.type = "UNDEFINED";
		}
		else{
			$$.type = $1.type;		
		}
	}
	| simple_expression {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

var:
	IDENTIFIER {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		//check symbol defined and get type
		resState = symTable.findSymbol($1.st->nodeName);
		if(resState == 0){
			cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $1.st->nodeName << " is not defined." << endl; 
			$$.type = "UNDEFINED";
		}
		else{
			$$.type = symTable.getSymbolType($1.st->nodeName);
		} 
	}
	| IDENTIFIER '[' expression ']' {
		$$.st = create_tree($1.st->nodeName, 1, -1, $3.st);
		$$.st->nodeType = "ARRAY";
		$$.lineNo = $1.lineNo;
		
		string buff;
		//check symbol defined 
		resState = symTable.findSymbol($1.st->nodeName);
		if(resState == 0){
			cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $1.st->nodeName << " is not defined." << endl; 
			$$.type = "UNDEFINED";
		}
		else{
			buff = symTable.getSymbolType($1.st->nodeName);
			//check if type is array and get type
			
			if(buff[buff.size()-1] != '*'){
				cout << "[Compile Error] Line:" << $$.lineNo << " variable " << $1.st->nodeName << " is not array type." << endl; 
				$$.type = buff;
			}
			else{
				$$.type = buff.substr(0,buff.size()-1);
			} 
		}
		
		if($3.type != "INT"){
				cout << "[Compile Error] Line:" << $$.lineNo << " array index type should be int but not " << $3.type << endl; 
		}
	};

simple_expression:
	additive_expression REL_OP additive_expression {
		$$.st = create_tree($2.tokenContent, 2, -1, $1.st, $3.st);
		$$.st->nodeType = "OPERATOR";
		$$.lineNo = $1.lineNo;
		
		if($1.type != $3.type){
			cout << "[Compile Error] Line:" << $$.lineNo << " REL_OP cannot operate on type " << $1.type << " and type " << $3.type << endl;
			$$.type = "UNDEFINED"; 
		}
		else{
			$$.type = "BOOL";		
		}
	}
	| additive_expression {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

additive_expression:
	additive_expression ADD_OP term {
		$$.st = create_tree($2.tokenContent, 2, -1, $1.st, $3.st);
		$$.st->nodeType = "OPERATOR";
		$$.lineNo = $1.lineNo;
		
		if($1.type != $3.type){
			cout << "[Compile Error] Line:" << $$.lineNo << " ADD_OP cannot operate on type " << $1.type << " and type " << $3.type << endl;
			$$.type = "UNDEFINED"; 
		}
		else{
			$$.type = $1.type;		
		}		
	}
	| term {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

term:
	term MUL_OP factor {
		$$.st = create_tree($2.tokenContent, 2, -1, $1.st, $3.st);
		$$.st->nodeType = "OPERATOR";
		$$.lineNo = $1.lineNo;
		
		if($1.type != $3.type){
			cout << "[Compile Error] Line:" << $$.lineNo << " MUL_OP cannot operate on type " << $1.type << " and type " << $3.type << endl;
			$$.type = "UNDEFINED"; 
		}
		else{
			$$.type = $1.type;		
		}
	}
	| factor {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

factor:
	'(' expression ')' {
		$$.st = $2.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $2.type;
	}
	| var {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;

		$$.type = $1.type;		
	}
	| call {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type; 
	}
	| CONSTANT_INT {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;	
		$$.type = "INT";
	}
	| CONSTANT_DOUBLE {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;	
		$$.type = "DOUBLE";
	}
	| CONSTANT_BOOL {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;	
		$$.type = "BOOL";
	};

call:
	IDENTIFIER '(' args ')' {
		$$.st = create_tree("call", 2, -1, $1.st, $3.st);
		$$.st->nodeType = "FUN_CALL";
		$$.lineNo = $1.lineNo;
		
		resState = symTable.findSymbol($1.st->nodeName);
		if(resState == 0){
			cout << "[Compile Error] Line:" << $$.lineNo << " function " << $1.st->nodeName << " is not declared." << endl; 
			$$.type = "UNDEFINED"; 
		}
		else if(funcDefined.find($1.st->nodeName) == funcDefined.end()){
			cout << "[Compile Error] Line:" << $$.lineNo  << " "<< $1.st->nodeName << " is not a function." << endl; 
			$$.type = "UNDEFINED"; 
		}
		else{
			string resType = symTable.getSymbolType($1.st->nodeName);
			
			if(funcDefined[$1.st->nodeName] == false){
				cout << "[Compile Error] Line:" << $$.lineNo << " function " << $1.st->nodeName << " is not defined." << endl; 
			}
			
			vector<string> splitType;
			SplitString(resType,splitType," ");
			$$.type = splitType[0];
			
			vector<string> splitArgs;
			SplitString($3.type,splitArgs," ");
			if(splitArgs.size() != splitType.size() - 1){
				cout << "[Debug Message] Line:" << $$.lineNo << " " << resType << " || " << $3.type << endl; 
				cout << "[Compile Error] Line:" << $$.lineNo << " the number of the parameters does not match the defination of the " << $1.st->nodeName << endl; 
			}
			else{
				for(int i = 0;i < splitArgs.size(); i++){
					if(splitArgs[i] != splitType[i+1]){
						cout << "[Compile Error] Line:" << $$.lineNo << " the " << i << "th parameter should be " << splitType[i+1] << " but not " << splitArgs[i] << endl; 
						break;
					}
				}
			}
		} 
		
	};

args: /*可为空*/{
		$$.st = create_tree("NO_ARGS", 0, -1);
		$$.st->nodeType = "ARGS";
		$$.type = "VOID";
	}
	| arg_list {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

arg_list:
	arg_list ',' expression {
		$$.st = create_tree("arg_list", 2, -1, $1.st, $3.st);
		$$.st->nodeType = "ARGS";
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type + " " + $3.type;
	}
	| expression {
		$$.st = $1.st;
		$$.lineNo = $1.lineNo;
		
		$$.type = $1.type;
	};

%%
void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main(int argc,char* argv[]) {

	yyin = fopen(argv[1],"r");
	cout << "Open File" << endl;
	
	yyparse();
	
	root->printTree2(0);
	
	ofstream out("a.gv");
	out << "digraph AST {" << endl;
	DrawTree(out, root, NULL, 0);
	out << "}" << endl;
	out.close();

	fclose(yyin);
	return 0;
}


