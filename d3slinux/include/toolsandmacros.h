#ifndef TOOLSANDMACROS_H
#define TOOLSANDMACROS_H

#include <string>
#define ACCEPTED_ERRNO 17
#define D3SL_ERROR(e) "[ERROR] : " e
#define D3SL_INFO(e) "[INFO] : " e

using namespace std;

//const string D3SL_ERROR(string a){string p ; p = "[ERROR] : "; p.append(a); return p;}
//const string D3SL_INFO(string a){string p ; p = "[INFO] : "; p.append(a); return p;}

const string TIMING_BEFORE = "before";
const string TIMING_AFTER = "after";
const string ADD_TUPLE = "addTuple";
const string DEL_TUPLE = "delTuple";

#endif // TOOLSANDMACROS_H
