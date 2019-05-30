#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stdarg.h>
#include "tree.h"

treeNode::treeNode(string name,int childNum, int lineNo){
	this->nodeName = name;
	this->childNum = childNum;
	this->lineNum = lineNo;
	
	this->nodeType = name;
}

void treeNode::printTree(){
	queue<treeNode*> nodes;
	nodes.push(this);
	nodes.push(NULL);
	while(!nodes.empty()){
		treeNode* first = nodes.front();
		if(first == NULL){
			cout << endl;
			nodes.pop();
			nodes.push(NULL);
			first = nodes.front();
			if(first == NULL){
				cout << "print over" << endl;
				break;
			}
		}
		
		int childCount = 0;
		for(int i = 0;i < first->child.size(); i++){
			if(first->child[i] != NULL)
				childCount += 1;
		}
		
		cout << "[" << first->nodeName << ":" << childCount << "]";
		nodes.pop();
		for(int i = 0; i < first->child.size(); i++){
			if(first->child[i] == NULL)
				continue;
			else
				nodes.push(first->child[i]);
		}
	}
	return;
}

treeNode::~treeNode(){

}

treeNode* create_tree(string name, int childNum, int lineNo, ...){
	if(childNum <= 0){
		treeNode* res = new treeNode(name,childNum,lineNo);
		return res;
	}
	else{
		treeNode* res = new treeNode(name,childNum,lineNo);
		va_list valist;
		va_start(valist,lineNo);
		int i = 0;
		for(i = 0;i < childNum; i++){		
			treeNode* args=va_arg(valist,treeNode*);
			res->child.push_back(args);
		}
		va_end(valist);
		
		//cout << res->nodeName << ":" << res->child.size() << endl;
		/*
		cout << res->nodeName << ":" << endl; 
		for(int j = 0;j<res->child.size();j++)
			cout << res->child[j]->nodeName << endl;*/
		return res;
	}
}

