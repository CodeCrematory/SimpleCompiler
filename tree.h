#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class treeNode{
public:
	string nodeName;
	int lineNum;//unused
	string content;//unused
	int childNum;//unused,use child.size() 
	vector<treeNode*> child;//there may be NULL in this vector, remember to check when reference
	string code;//now may be useless
	string nodeType;
	//CONSTANT value can be accessed in nodeName,leaf node
	//ID var name can be accessed in nodeName,leaf node
	//OPERATOR op type can be accessed in nodeName, has 2 children(CONSTANT | ID | ARRAY | OPERATOR | FUN_CALL)*2
	//PROGRAM root node,has one child DECLARATION
	//DECLARATION has 1 or 2 children(DECLARATION | VAR_DECLARATION | VAR_DECALRATION_WITH_INITIAL | VAR_ARRAY_DECALRATION)*1/2
	//VAR_DECLRATION has 2 children(TYPE + ID)
	//VAR_DECLARATION_WITH_INITIAL has 3 children(TYPE + ID + (OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL))
	//VAR_ARRAY_DECLRATION has 3 children(TYPE + ID + CONSTANT)
	//TYPE value can be accessed in nodeName,leaf node
	//FUN_DECLARATION has 3 children (TYPE + ID + (PARAMS|VOID))
	//FUN_DEFINITION 4 children (TYPE + ID + (PARAMS|PARAM|VOID) + STATEMENTS)
	//VOID means no parameters,leaf
	//PARAMS 1/2 children (PARAMS|PARAM)*1/2
	//PARAM 2 child (TYPE + ID )
	//COM_STATEMENTS 2 child (DECLARATION + (STATEMENTS|STATEMENT)) 
	//STATEMENTS  1/2 (STATEMENTS|ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL|IF|IF_ELSE|WHILE|RETURN)
	//IF  2 (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)+(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL|COM_STATEMENTS|IF|IF_ELSE|WHILE|RETURN) 
	//IF_ELSE 3 (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)+(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL|COM_STATEMENTS|IF|IF_ELSE|WHILE|RETURN)*2
	//WHILE 2 (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)+(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL|COM_STATEMENTS|IF|IF_ELSE|WHILE|RETURN) 
	//RETURN 1/0 (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)
	//ASSIGNMENT 2 ID|ARRAY + (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)
	//ARRAY 2 ID+(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)
	//OPERATOR (ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)*2
	//FUN_CALL ID+(ARGS|(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)) 
	//ARGS (ARGS|ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)
	
	
	treeNode(string name, int childNum, int lineNo);
	void printTree();
	~treeNode();
};

class attributes{
//ALL attributes  must be synthesized attributes, if inherited attributes are needed, grammar in yacc may need to be modified
public:
	/*below for semantic analysis*/
	treeNode* st; //node of the tree, all terminal and non-terminal has the valid attr
	int lineNo;	//the line of the token, all terminal and non-terminal has the valid attr
	string tokenContent;//content of the token, ADD MUL REL-OP has the valid attr
	string type;//cthe type of the variable, expression, function call,args, paras has the valid attr
	string funcParas;//usd to collect function parameters types when function declaration
	/*below used for code generation*/
	string interCode;
};

treeNode* create_tree(string name, int childNum, int lineNo, ...);

#endif
