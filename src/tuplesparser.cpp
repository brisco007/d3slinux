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
#define TUPLES_FILE_H "g_stagestypes.h"
#define ACCEPTED_ERRNO 17
using namespace std;
using namespace nlohmann;

TuplesParser::TuplesParser(string filename)
{
    try{
        parseFile(filename);
    }catch(exception & e){
        throw e;
    }
   this->classNameDef = TUPLES_FILE_H;
    this->graphName = filename;
    if ((mkdir(this->baseDir, 0777) == -1) && errno != ACCEPTED_ERRNO)
        cerr << "Error :  "<<errno<<" " << strerror(errno) << endl;
    else{
        cout << "created tuple parser for "<< this->baseDir<<"/"<<this->classNameDef<<endl;
        this->classNameDeff.open("./"+this->baseDirS+"/"+this->classNameDef,ios::out|ios::app);
    }
}
void TuplesParser::parseFile(string filename){
     try{
     ifstream i(filename);;
     i >> graph;
   }catch(::detail::parse_error & e){
        cout << e.what();
        throw e;
   }
}
TuplesParser::~TuplesParser()
{
    cout <<"destroying parser..."<<endl;
    this->classNameDeff.close();

}
string TuplesParser::toString(){
    return "parses file name : "+this->graphName;
}
void TuplesParser::appendFile(string codeToAdd){
    if(this->classNameDeff.good()){
        this->classNameDeff << codeToAdd;
    }
}
string TuplesParser::generateTupleClass(json output){
     string code;
     code = "\tclass ";
     code += "Tuple";
     code += "\n\t{\n\t\t";
     for(const auto& item : output["output"].items()){
        code.append(item.value()).append(" ").append(item.key()).append(";");
        code.append("\n\t\t");
     }
     code += "\n\t}\n";
     return code;
}
void TuplesParser::generateFile(){
    /*iterate in the main list f stages to know the classes to create*/
    string code;
    //include namespaces
    //GENERATING .H
    code += "using namespace std;\n\n";
    appendFile(code);
    /*
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
        cout << item.key() << " \n " << item.value()["name"] <<endl;
    }*/
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
         code = "class ";
         code += item.value()["name"];
         code += "\n{\n";
         code += generateTupleClass(item.value()["infos"]);
         code += "}\n";
         appendFile(code);
    }
}
