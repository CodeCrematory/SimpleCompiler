#ifndef _INNERCODE_H_
#define _INNERCODE_H_

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
#include "table.h"
#include "convert.h"

using namespace std;

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

    void print_code();
    void add_code(string, string, string, string); // push a quad into code vector
    string get_temp(); // generate temporary variable
    string get_label(); // generate label
    string elem_size(treeNode*); // return the size of its type

public:
    interRepre(){}
    ~interRepre(){}
    void gen_code(treeNode*); // no return value
    string gen_exp(treeNode*); // for expression which returns value in the right side of a equation
};

#endif