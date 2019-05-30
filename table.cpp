//Symbol Table
#include "table.h"
int hashFunction(string s) {
	int i = 0;
	int res = 0;
	for (i = 0; i < s.length(); i++){
		res = res + (i + 1)*int(s[i]);
	}
	return res;
}

void SplitString(string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

aSymbol::aSymbol(string s, string type) {
	this->name = s;
	this->type = type;
}

int HashList::insertElement(string name, string type) {
	if (this->findElement(name) == 1) {
		return -1;
	}
	int hashVal = hashFunction(name) % this->length;
	list[hashVal]->push_back(new aSymbol(name, type));
	return 0;
}

int HashList::deleteElement(string name) {
	return 0;
}

int HashList::findElement(string name) {
	int hashVal = hashFunction(name) % this->length;
	vector<aSymbol*> &aList = *(list[hashVal]);
	for (int i = 0; i < aList.size(); i++) {
		if (aList[i]->name == name)
			return 1;
	}
	return 0;
}

int HashList::printList() {
	for (int i = 0; i < list.size(); i++) {
		vector<aSymbol*> hashL = *(list[i]);
		for (int j = 0; j < hashL.size(); j++) {
			cout << hashL[j]->name << " ";
		}
		cout << "|";
	}
	cout << endl;
}

string HashList::elementType(string name){
	int hashVal = hashFunction(name) % this->length;
	vector<aSymbol*> &aList = *(list[hashVal]);
	for (int i = 0; i < aList.size(); i++) {
		if (aList[i]->name == name)
			return aList[i]->type;
	}
	return "NotFind";
}

HashList::HashList() {
	for (int i = 0; i < this->length; i++) {
		list.push_back(new vector<aSymbol*>);
	}
}

HashList::~HashList() {
	for (int i = 0; i < length; i++) {
		delete list[i];
	}
}


SymbolTable::SymbolTable() {
	this->tableStack.push_back(new HashList());
	this->length += 1;
}

SymbolTable::~SymbolTable() {
	for (int i = 0; i < length; i++) {
		delete tableStack[i];
	}
}

int SymbolTable::insertSymbol(string name, string type) {
	int res = tableStack[length - 1]->insertElement(name,type);
	return res;
}

int SymbolTable::findSymbol(string name) {
	int res;
	for (int i = length - 1; i >= 0; i--) {
		res = tableStack[i]->findElement(name);
		if (res == 1)
			return 1;
	}
	return 0;
}

string SymbolTable::getSymbolType(string name){
	string res;
	for (int i = length - 1; i >= 0; i--) {
		res = tableStack[i]->elementType(name);
		if (res != "NotFind")
			return res;
	}
	return "NotFind";
}

int SymbolTable::deleteTable() {
	delete tableStack[this->length - 1];
	tableStack.pop_back();
	this->length -= 1;
}

int SymbolTable::createTable() {
	tableStack.push_back(new HashList());
	this->length += 1;
}

int SymbolTable::printTable() {
	for (int i = 0; i < length; i++) {
		HashList temp = *(tableStack[i]);
		temp.printList();
		cout << "----------" << endl;
	}
}
