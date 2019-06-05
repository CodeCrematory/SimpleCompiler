//
// Created by hasee on 2019/5/29.
//

#include "draw.h"

void DrawTree(ofstream& out, treeNode* curNode, treeNode* parNode, int parNum){
	static int my_id = 0;
	int curNum = my_id;
	if (curNode != NULL){
		out << "\tnode" << my_id++ << " [label=\"" << curNode->nodeName << "(" << curNode->nodeType << ")" <<"\"];" <<endl;
		if (parNode != NULL){
			out << "\tnode" << parNum << " -> node" << curNum << ";" <<endl;
		}
		if (curNode->childNum > 0){
			for (auto iter = curNode->child.begin();iter != curNode->child.end();++iter){
				DrawTree(out,*iter,curNode,curNum);
			}
		}
	}
}