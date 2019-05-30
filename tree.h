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
	vector<treeNode*> child;//there may be NULL in this vector, remembet to check when reference
	string code;//now may be useless
	string nodeType;//CONSTANT(value can be accessed in nodeName); ID(var name can be accessed in nodeName); OPERATOR
	
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
