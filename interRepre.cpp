#include "interRepre.h"
// #define NDEBUG
#include <assert.h>

using namespace std;

// Quad ====================================================

string Quad::print_quad(){
    ostringstream ostr;
	ostr << op << "," << arg1 << "," << arg2 << "," << res;
    string quad = ostr.str();
    return quad;
}

// interRepre ==============================================

int interRepre::tempNum = 0;
int interRepre::labelNum = 0;

interRepre::interRepre(treeNode* node){
    cout << "= constructing IR ... ====================================" << endl;
    gen_code(node);
}

void interRepre::print_code(){
    for(auto code : codeVec){
        cout << code.print_quad() << endl;
    }
}

string interRepre::get_temp(){
    ostringstream ostr;
	ostr << "temp" << tempNum++;
    string temp = ostr.str();
    return temp;
}

string interRepre::get_label(){
    ostringstream ostr;
	ostr << "L" << labelNum++;
    string label = ostr.str();
    return label;
}

string interRepre::elem_size(treeNode* node){
    assert(nodeMap[node->nodeType] == ID);
    return typeMap[node->varType];
}

void interRepre::add_code(string op, string arg1, string arg2, string res){
    Quad quad = Quad(op, arg1, arg2, res);
    codeVec.push_back(quad);
}

void interRepre::gen_code(treeNode* node){
    string op = "", arg1 = "", arg2 = "", res = "";
    string L1 = "", L2 = "";
    ostringstream ostr;

    if (node != nullptr){

        // cout << node->nodeType << ": " << node->nodeName << endl;
        // for(auto child : node->child){
        //     if(child != nullptr){
        //         cout << "   " << child->nodeType << ": " << child->nodeName  << " " << child->varType << endl;
        //     }
        // }

        switch(nodeMap[node->nodeType]){
            case PROGRAM:
                /**
                 * PARAGRAM: call gen_code() on its child: DECLARATION
                **/
                gen_code(node->child[0]);
                break;

            case DECLARATION:
                /**
                 * DECLARATION: call gen_code() on its child: DECLARATION | VAR_DECLARATION | VAR_DECALRATION_WITH_INITIAL | VAR_ARRAY_DECALRATION| FUN_DECLARATION| FUN_DEFINITION
                **/
                for(auto child : node->child){
                    gen_code(child);
                }
                break;

            case VAR_DECLARATION:
                /**
                 * VAR_DECLARATION:
                 * op(dec) arg1(size) res(ID)
                **/
                assert(node->child.size() == 2);
                
                // type assignment
                node->child[1]->varType = node->child[0]->nodeName;
                // op(dec) arg1(size) res(ID)
                op = "dec";
                arg1 = elem_size(node->child[1]); // elem_size of ID
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                break;

            case VAR_DECLARATION_WITH_INITIAL:
                /**
                 * VAR_DECLARATION_WITH_INITIAL:
                 * op(dec) arg1(size) res(ID)
                 * res(ID) op(:=) arg1
                **/
                assert(node->child.size() == 3);

                // type assignment
                node->child[1]->varType = node->child[0]->nodeName;
                // op(dec) arg1(size) res(ID)
                op = "dec";
                arg1 = elem_size(node->child[1]); // elem_size of ID
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                // res(ID) op(:=) arg1
                op = ":=";
                arg1 = gen_exp(node->child[2]); // initial value
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                break;

            case VAR_ARRAY_DECLARATION:
                /**
                 * VAR_ARRAY_DECALRATION:
                 * res(t1) = arg1(length) op(*) arg2(elem_size(ID))
                 * op(dec) arg1(t1) res(ID)
                **/
                assert(node->child.size() == 3);

                // type assignment
                node->child[1]->varType = node->child[0]->nodeName;
                // t1 = length * elem_size(ID)
                op = "*"; // multiply
                arg1 = gen_exp(node->child[2]); // length
                arg2 = elem_size(node->child[1]); // elem_size(ID)
                res = get_temp();
                add_code(op, arg1, arg2, res);
                // op(dec) arg1(t1) res(ID)
                op = "dec";
                arg1 = res; // size
                arg2 = "";
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                break;
            
            case FUN_DEFINITION:
                /**
                 * FUN_DEFINITION:
                 * op(entry) res(ID)
                 * call gen_code (params/param/void)
                 * call gen_code (com_statement)
                **/
                assert(node->child.size() == 4);
                
                // op(entry) res(ID)
                op = "entry";
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                // params/param/void
                gen_code(node->child[2]);
                // com_statement
                gen_code(node->child[3]);
                break;

            case PARAMS:
                /**
                 * PARAMS:
                 * call gen_code (params/param)
                **/
                assert(node->child.size() == 2);

                for (auto param : node->child){
                    gen_code(param);
                }
                break;
            
            case PARAM:
                /**
                 * PARAM:
                 * op(param) arg1(size) res(ID)
                **/
                assert(node->child.size() == 2);

                // type assignment
                node->child[1]->varType = node->child[0]->nodeName;
                op = "param";
                arg1 = elem_size(node->child[1]); // size
                res = gen_exp(node->child[1]); // ID
                add_code(op, arg1, arg2, res);
                break;
            
            case COM_STATEMENTS:
                /**
                 * COM_STATEMENTS:
                 * call gen_code
                **/
                assert(node->child.size() == 2);

                for (auto child : node->child){
                    gen_code(child); // declaration, statements(other expression)
                }
                break;
            
            case STATEMENTS:
                /**
                 * STATEMENTS:
                 * call gen_code
                **/
                assert(node->child.size() == 2);

                for (auto statement : node->child){
                    gen_code(statement);
                }
                break;

            case _IF:
                /**
                 * IF:
                 * op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L1)
                 * gen_code(exec)
                 * op(label) res(L1)
                **/
                assert(node->child.size() == 2);

                // op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L1)
                op = "if_false";
                arg1 = gen_exp(node->child[0]); // condition
                arg2 = "goto";
                res = get_label();
                add_code(op, arg1, arg2, res);
                // gen_code(exec)
                gen_code(node->child[1]); // execution
                // op(label) res(L1)
                op = "label";
                arg1 = "";
                arg2 = "";
                add_code(op, arg1, arg2, res);
                break;
            
            case IF_ELSE:
                /**
                 * IF_ELSE:
                 * op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L1)
                 * gen_code(exec1)
                 * op(goto) res(L2)
                 * op(label) res(L1)
                 * gen_code(exec2)
                 * op(label) res(L2)
                **/
                assert(node->child.size() == 3);

                L1 = get_label();
                L2 = get_label();
                // op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L1)
                op = "if_false";
                arg1 = gen_exp(node->child[0]); // cond
                arg2 = "goto";
                res = L1;
                add_code(op, arg1, arg2, res);
                // gen_code(exec1)
                gen_code(node->child[1]); // exec1
                // op(goto) res(L2)
                op = "goto";
                arg1 = "";
                arg2 = "";
                res = L2;
                add_code(op, arg1, arg2, res);
                // op(label) res(L1)
                op = "label";
                res = L1;
                add_code(op, arg1, arg2, res);
                // gen_code(exec2)
                gen_code(node->child[2]);
                // op(label) res(L2)
                op = "label";
                res = L2;
                add_code(op, arg1, arg2, res);
                break;
            
            case _WHILE:
                /**
                 * WHILE:
                 * op(label) res(L1)
                 * op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L2)
                 * gen_code(exec)
                 * op(goto) res(L1)
                 * op(label) res(L2)
                **/
                assert(node->child.size() == 2);

                L1 = get_label();
                L2 = get_label();
                // op(label) res(L1)
                op = "label";
                res = L1;
                add_code(op, arg1, arg2, res);
                // op(if_false) arg1(gen_exp(cond)) arg2(goto) res(L2)
                op = "if_false";
                arg1 = gen_exp(node->child[0]); // cond
                arg2 = "goto";
                res = L2;
                add_code(op, arg1, arg2, res);
                // gen_code(exec)
                gen_code(node->child[1]);
                // op(goto) res(L1)
                op = "goto";
                arg1 = "";
                arg2 = "";
                res = L1;
                add_code(op, arg1, arg2, res);
                // op(label) res(L2)
                op = "label";
                res = L2;
                add_code(op, arg1, arg2, res);
                break;
            
            case _RETURN:
                /**
                 * RETURN:
                 * op(return) res(return value) | op(end)
                **/
                if(node->child.empty()){
                    // op(end)
                    op = "end";
                    add_code(op, arg1, arg2, res);
                }
                else{
                    //op(return) res(return value)
                    op = "return";
                    res = gen_exp(node->child[0]);
                    add_code(op, arg1, arg2, res);
                }
                break;

            case ARGS:
                /**
                 * ARGS: op("arg") res(name of argument)
                **/
                if(!node->child.empty()){
                    // first child: args or single arg
                    if(nodeMap[node->child[0]->nodeType] == ARGS){
                        gen_code(node->child[0]);
                    }
                    else{
                        op = "arg";
                        res = gen_exp(node->child[0]);
                        add_code(op, arg1, arg2, res);
                    }
                    // second child: always single arg
                    op = "arg";
                    res = gen_exp(node->child[1]);
                    add_code(op, arg1, arg2, res);
                }
                break;
            
            // expression
            case ASSIGNMENT:
            case OPERATOR:
            case CONSTANT:
            case ID:
            case ARRAY:
            case FUN_CALL:
                gen_exp(node);
                break;
            
            // do nothing
            case TYPE:
            case FUN_DECLARATION:
            case _VOID:
            default:
                break;
        }
    }
}

/**
 * gen_exp: types require return values(ASSIGNMENT|OPERATOR|CONSTANT|ID|ARRAY|FUN_CALL)
**/
string interRepre::gen_exp(treeNode* node){
    string op = "", arg1 = "", arg2 = "", res = "";
    string temp;
    ostringstream ostr;

    if (node != nullptr){

        // cout << node->nodeType << ": " << node->nodeName << endl;
        // for(auto child : node->child){
        //     if(child != nullptr){
        //         cout << "   " << child->nodeType << ": " << child->nodeName  << " " << child->varType << endl;
        //     }
        // }

        switch(nodeMap[node->nodeType]){
            case ASSIGNMENT:
                /**
                 * ASSIGNMENT: res op(:=) arg1, return res
                **/
                assert(node->child.size() == 2);

                op = ":=";
                arg1 = gen_exp(node->child[1]);
                res = gen_exp(node->child[0]);
                add_code(op, arg1, arg2, res);
                return res;

            case OPERATOR:
                /**
                 * OPERATOR: res := arg1 op arg2, return res
                **/
                assert(node->child.size() == 1 || node->child.size() == 2);

                op = node->nodeName;
                arg1 = gen_exp(node->child[0]);
                if(node->child.size() == 2){
                    arg2 = gen_exp(node->child[1]);
                }
                res = get_temp();
                add_code(op, arg1, arg2, res);
                return res;

            case ID:
                /**
                 * ID: return nodeName
                **/
                return node->nodeName;

            case CONSTANT:
                /**
                 * CONSTANT: return #nodeName
                **/
	            ostr << "#" << node->nodeName;
                temp = ostr.str();
                return temp;

            case ARRAY:
                /**
                 * ARRAY:
                 * t1 = index * elem_size(ID) # ID = nodeName
                 * t2 = &ID + t1
                 * return *t2
                **/
                assert(node->child.size() == 2);

                // t1 = index * elem_size(ID)
                op = "*"; // multiply
                arg1 = gen_exp(node->child[1]); // index
                arg2 = elem_size(node->child[0]); // elem_size(ID)
                res = get_temp();
                add_code(op, arg1, arg2, res);
                // t2 = &ID + t1
                op = "+"; // add
                arg1 = "&" + node->child[0]->nodeName; // array address
                arg2 = res; // offset: t1
                res = get_temp();
                add_code(op, arg1, arg2, res);
                // return *t2
                return "*" + res;

            case FUN_CALL:
                /** 
                 * FUN_CALL:
                 * begin_args
                 * arg t1 ...
                 * op(call) arg1(f) res(return value)
                 * return res(return value)
                **/
                assert(node->child.size() == 2);
                // begin_args
                op = "begin_args";
                add_code(op, arg1, arg2, res);
                // arg
                if(nodeMap[node->child[1]->nodeType] == ARGS){
                    // 0 or >= 2 args
                    gen_code(node->child[1]);
                }
                else{
                    // single arg
                    op = "arg";
                    res = gen_exp(node->child[1]);
                    add_code(op, arg1, arg2, res);
                }
                // op(call) arg1(f) res(return value)
                op = "call";
                arg1 = node->child[0]->nodeName; // ID
                res = get_temp();
                add_code(op, arg1, arg2, res);
                // return res(return value)
                return res; // call ID
        }
    }
}