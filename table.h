#ifndef _TABLE_H_
#define _TABLE_H_
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int hashFunction(string s);
void SplitString(string& s, vector<string>& v, const string& c);

class aSymbol {
public:
	string name;
	string type;
	
	aSymbol(string s,string type);
};

class HashList {
private:
	int length = 13;
	vector<vector<aSymbol*>*> list;
public:
	HashList();
	~HashList();
	int insertElement(string nane, string type);
	int deleteElement(string name);
	string elementType(string name);
	int findElement(string name);
	int printList();
};

class SymbolTable {
private:
	int length = 0;
	vector<HashList*> tableStack;
public:
	SymbolTable();
	~SymbolTable();
	int insertSymbol(string name, string type);//insert symbol, if successful, return 0; if the name has been defined return -1
	int findSymbol(string name);//successful return 1, not find return 0
	string getSymbolType(string name);//if not find,return the string "NotFind";for function, its type string is returnType, para1Type, ..., split by space
	int deleteTable();//for semantic,used when meet }
	int createTable();//for semantic,used when meet {
	int printTable();//for test
};

#endif 
