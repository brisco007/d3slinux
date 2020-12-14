#include "tuplesparser.h"
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#define TUPLES_FILE_NAME "g_stagestypes.cpp"
#define ACCEPTED_ERRNO 17
using namespace std;
using namespace nlohmann;

TuplesParser::TuplesParser(string filename)
{
    this->classNameDef = TUPLES_FILE_NAME;
    this->graphName = filename;
    if ((mkdir(this->baseDir, 0777) == -1) && errno != ACCEPTED_ERRNO)
        cerr << "Error :  "<<errno<<" " << strerror(errno) << endl;
    else{
        cout << "created tuple parser for "<< this->baseDir<<"/"<<this->classNameDef<<endl;
        this->classNameDeff = new ofstream("./"+this->baseDirS+"/"+this->classNameDef,ios::out|ios::app);
    }
}

TuplesParser::~TuplesParser()
{
    cout <<"destroying parser..."<<endl;

}
string TuplesParser::toString(){
    return "parses file name : "+this->graphName;
}

