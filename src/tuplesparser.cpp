#include "tuplesparser.h"
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <list>
#include <sys/types.h>

#define TUPLES_FILE_NAME "g_stagestypes.cpp"
#define TUPLES_FILE_H "g_stagestypes.h"
#define TUPLES_FILE_HU "G_STAGESTYPES_H"
#define ACCEPTED_ERRNO 17
using namespace std;
using namespace nlohmann;

//extern const string TUPLES_FILE_H = "g_stagestypes.h";
TuplesParser::TuplesParser(string filename)
{

    try{
        parseFile(filename);
    }catch(exception & e){
        throw e;
    }
    this->graphName = filename;
    this->classNameDef = TUPLES_FILE_H;
    openFluxFile();
}
void TuplesParser::openFluxFile(){
    if ((mkdir(this->baseDir, 0777) == -1) && errno != ACCEPTED_ERRNO)
        cerr << "Error :  "<<errno<<" " << strerror(errno) << endl;
    else{
        cout << "created tuple parser for "<< this->baseDir<<"/"<<this->classNameDef<<endl;
        this->classNameDeff.open("./"+this->baseDirS+"/"+this->classNameDef,ios::out/*|ios::app*/);
    }
}
void TuplesParser::parseFile(string filename){
     try{
     ifstream i(filename);
     i >> graph;
// TODO (brice#1#01/02/21): Implement a function which checks the coherence of the json file like the name of the stages should not start by numbers or special characters etc and call it here and in parseFile in instrumentationParser

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
string generateConstInside(json output){
     string initVars;
     string construct;
     //TODO ajouter dans la fonction qui appelle celle ci le nom de la classe de base.
     construct = "::Tuple::Tuple(";
     initVars = "\t\t\t{\n";
     for(const auto& item : output["output"].items()){
        construct.append(item.value()).append(" ").append(item.key()).append(",");
        initVars.append("\t\t\t\t").append("this->").append(item.key()).append(" = ").append(item.key()).append(";");
     }
     construct.append(")");
     initVars.append("\n\t\t\t}");
     construct.append(initVars);
     return construct;
}
string TuplesParser::putIncludes(list<string> includesList){
    string include;
    include = "#include <string>\n";
    for (auto const& i : includesList) {
        include.append(i)
               .append("\n");
    }
    include.append("\n\n");
    return include;
}

string generateTupleConstructors(json output){
 string code;
 string construct;
     construct = "Tuple(";
     code = "\tclass ";
     code.append("Tuple")
         .append("\n\t{\n\t\t")
         .append("public:\n\t\t\t");
     for(const auto& item : output["output"].items()){
        code.append(item.value()).append(" ").append(item.key()).append(";");
        code.append("\n\t\t\t");
        construct.append(item.value()).append(" ").append(item.key()).append(",");
     }
     construct.append(");");
     code.append(construct).append("\n\t}\n");
     return code;
}

string TuplesParser::generateTupleClassConstructor(json output){
     string code;
     string construct;
     construct = "Tuple::Tuple(";
     //ctor = "Tuple(Tuple tple){";
     code = "";
     /*code.append("\n\t{\n\t\t")
         .append("public:\n\t\t\t");*/
     for(const auto& item : output["output"].items()){
        construct.append(item.value()).append(" ").append(item.key()).append(",");
     }
     construct.pop_back();
     construct.append("){");
     //code.append(construct);
     for(const auto& item : output["output"].items()){
        construct.append("\n\tthis->").append(item.key()).append(" = ").append(item.key()).append(";");
     }
     code.append(construct);
     code.append("\n}\n");
     return code;
}
string TuplesParser::generateTupleClass(json output){
     string code,construct,opbuild;
     construct = "Tuple(";
     opbuild = "\n\t\t\tbool operator == (const Tuple& t) const { return ";
     //ctor = "\n\t\t\tTuple(Tuple tple);";
     //code = "\tpublic:\n\t\tclass ";
     code = "\n\tclass ";
     code.append("Tuple")
         .append("\n\t{\n\t\t")
         .append("public:\n\t\t\t");
     for(const auto& item : output["output"].items()){
        code.append(item.value()).append(" ").append(item.key()).append(";");
        code.append("\n\t\t\t");
        construct.append(item.value()).append(" ").append(item.key()).append(",");
        opbuild.append("(").append(item.key()).append(" == t.").append(item.key()).append(") &&");
     }
     opbuild.pop_back();
     opbuild.pop_back();
     construct.pop_back();
     opbuild.append("; }\n\t\t\t").append("bool operator != (const Tuple& t) const { return !operator==(t); }");
     construct.append(");");
     code.append(construct).append(opbuild).append("\n\t};\n");
     return code;
}
void TuplesParser::generateFile(){
    /*iterate in the main list f stages to know the classes to create*/
    string code;
    //include namespaces
    //GENERATING .H
    //include everything
    list<string> includesListH = {"#include <iostream>","#include <list>","#include <tuple>"};
    code = "#ifndef ";
    code.append(TUPLES_FILE_HU).append("\n#define ").append(TUPLES_FILE_HU).append("\n\n");
    code.append(putIncludes(includesListH));
    //adding namepsaces
    code.append("using namespace std;\n\n");
     code.append("const int numberOfStages = ").append(intToString(graph["computationGraph"]["numberOfStages"])).append(";\n");
    code.append("const string firstStage = ").append("\"").append(graph["computationGraph"]["firstStage"]).append("\"").append(";\n");
    code.append("const string finalStage = ").append("\"").append(graph["computationGraph"]["finalStage"]).append("\"").append(";\n\n");
    //adding the list of stages
    string listOfStages = "\nconst list<string> stages_list = {";
    appendFile(code);

    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
         //code = "class ";
         code = "namespace ";
         code.append(item.value()["name"]);
         listOfStages.append("\"").append(item.value()["name"]).append("\",");
         code.append("\n{\n");
         code.append(generateTupleClass(item.value()["infos"]));
         //code.append("};\n");
         code.append("}\n");
         appendFile(code);
    }
    listOfStages.pop_back();
    listOfStages.append("};");
    appendFile(listOfStages);
    appendFile("\n\n#endif");
    this->classNameDeff.close();

    //GENERATING .CPP
    this->classNameDef = TUPLES_FILE_NAME;
    openFluxFile();
    code ="";
    string includeHeader = "#include \"";
    includeHeader.append(TUPLES_FILE_H)
                 .append("\"");
    list<string> includesListC ={"#include <iostream>","#include <list>","#include <tuple>", includeHeader};
    //includesListC.
    code = putIncludes(includesListC);
    string namepspacesList = "using namespace std;\n";
    /*for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
        namepspacesList.append("using namespace ")
                       .append(item.value()["name"])
                       .append(";\n");
    }*/
    //namepspacesList.append("\n\n");
    code.append(namepspacesList);
    appendFile(code);
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
      code = "\n";
      code.append(item.value()["name"]);
      code.append("::");
      code.append(generateTupleClassConstructor(item.value()["infos"]));
      code.append("\n");
      appendFile(code);
    }
    this->classNameDeff.close();
}
string TuplesParser::intToString(int i){
    stringstream temp;
    temp << i;
    return temp.str();

}
