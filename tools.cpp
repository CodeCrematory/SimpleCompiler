#include "tools.h"

template <class Type>  
Type stringToNum(const string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  

template <class Type>
string constFold(string left, string op, string right){
	Type leftConst = stringToNum<Type>(left);
	Type rightConst = stringToNum<Type>(right);
	string res;
	if(op == "+")
		res = to_string(leftConst+rightConst);
	else if (op == "-")
		res = to_string(leftConst-rightConst);
	else if(op == "*")
		res = to_string(leftConst*rightConst);
	else if(op == "/")
		res = to_string(leftConst/rightConst);
	else if(op == ">"){
		if(leftConst > rightConst)
			res = "TRUE";
		else 
			res = "FALSE";
	}
	else if(op == "<"){
		if(leftConst < rightConst)
			res = "TRUE";
		else 
			res = "FALSE";
	}
	else if(op == ">="){
		if(leftConst >= rightConst)
			res = "TRUE";
		else 
			res = "FALSE";
	}
	else if(op == "<="){
		if(leftConst <= rightConst)
			res = "TRUE";
		else 
			res = "FALSE";
	}
	else if(op == "=="){
		if(leftConst == rightConst)
			res = "TRUE";
		else 
			res = "FALSE";
	}
	else if(op == "!="){
		if(leftConst != rightConst)
			res == "TRUE";
		else 
			res = "FALSE";
	}
	return res;
	
}