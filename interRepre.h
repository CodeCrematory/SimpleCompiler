#ifndef _INNERCODE_H_
#define _INNERCODE_H_

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "tree.h"
#include "table.h"

using namespace std;

typedef enum {CONSTANT, ID, PROGRAM, DECLARATION, VAR_DECLARATION, VAR_DECLARATION_WITH_INITIAL, 
            VAR_ARRAY_DECLARATION, TYPE, FUN_DECLARATION, FUN_DEFINITION, _VOID, PARAMS, PARAM, 
            COM_STATEMENTS, STATEMENTS, _IF, IF_ELSE, _WHILE, _RETURN, ASSIGNMENT, ARRAY, OPERATOR, FUN_CALL, ARGS} nodeType;

static map<string, int> typeMap = {{"BOOL", 1}, {"CHAR", 1}, {"INT", 4}, {"DOUBLE", 8}};

static map<string, int> nodeMap = {{"CONSTANT", CONSTANT}, {"ID", ID}, {"OPERATOR", OPERATOR}, {"PROGRAM", PROGRAM}, {"DECLARATION", DECLARATION}, 
                                {"VAR_DECLARATION", VAR_DECLARATION}, {"VAR_DECLARATION_WITH_INITIAL", VAR_DECLARATION_WITH_INITIAL}, 
                                {"VAR_ARRAY_DECLARATION", VAR_ARRAY_DECLARATION}, {"TYPE", TYPE}, {"FUN_DECLARATION", FUN_DECLARATION}, 
                                {"FUN_DEFINITION", FUN_DEFINITION}, {"VOID", _VOID}, {"PARAMS", PARAMS}, {"PARAM", PARAM}, {"COM_STATEMENTS", COM_STATEMENTS}, 
                                {"STATEMENTS", STATEMENTS}, {"IF", _IF}, {"IF_ELSE", IF_ELSE}, {"WHILE", _WHILE}, {"RETURN", _RETURN}, {"ASSIGNMENT", ASSIGNMENT}, 
                                {"ARRAY", ARRAY}, {"OPERATOR", OPERATOR}, {"FUN_CALL", FUN_CALL}, {"ARGS", ARGS}};

class Quad{
private:
    string op;
    string arg1;
    string arg2;
    string res;
public:
    Quad(string op, string arg1, string arg2, string res):
        op(op), arg1(arg1), arg2(arg2), res(res){}
    ~Quad(){}
    string print_quad();
};

class interRepre{
private:
    vector<Quad> codeVec;
    static int tempNum;
    static int labelNum;

    void add_code(string, string, string, string); // push a quad into code vector
    string get_temp(); // generate temporary variable
    string get_label(); // generate label
    string elem_size(treeNode*); // return the size of its type
    string gen_exp(treeNode*); // for expression which returns value in the right side of a equation

public:
    interRepre(treeNode*);
    ~interRepre(){}
    void gen_code(treeNode*); // no return value
    void print_code();
};

#endif