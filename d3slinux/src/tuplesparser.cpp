#include "tuplesparser.h"
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <list>
#include <vector>
#include <sys/types.h>
//#include "toolsandmacros.h"
#define TUPLES_FILE_NAME "g_stagestypes.cpp"
#define TUPLES_FILE_H "g_stagestypes.h"
#define TUPLES_FILE_HU "G_STAGESTYPES_H"
#define ACCEPTED_ERRNO 17
#define FACTORY_FILE_NAME "vertexObjectFactory.cpp"
#define FACTORY_FILE_H "vertexObjectFactory.h"
#define FACTORY_FILE_HU "VERTEX_OBJECT_FACTORY_H"
#define BASE_CLASS "AbstractVertex"
#define BASE_FILE "abstractVertex.h"

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
        string info = "created tuple parser for ";
        info.append(this->baseDir).append("/").append(this->classNameDef).append("\n");
        cout <<D3SL_INFO(info)<<endl;
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
string TuplesParser::putIncludesVector(vector<string> includesList){
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

string TuplesParser::generateTupleClassConstructor(json o){
     string code;
     string toStringMethod;
     string construct;
     json output = o["infos"];
     toStringMethod = "string ";
     toStringMethod.append( o["name"]).append("::Tuple::toString(){\n\tstring value=\"Tuple Value:\\n\";");
     construct = "Tuple::Tuple(";
     //ctor = "Tuple(Tuple tple){";
     code = "";
     /*code.append("\n\t{\n\t\t")
         .append("public:\n\t\t\t");*/
     for(const auto& item : output["output"].items()){
        construct.append(item.value()).append(" ").append(item.key()).append(",");
        toStringMethod.append("\n\tvalue.append(\"-").append(item.key());
        if(item.value() == "string"){
        toStringMethod.append(" : \").append(this->").append(item.key()).append("+\"\\n\");");
        }else {
        toStringMethod.append(" : \").append(to_string(this->").append(item.key()).append(")+\"\\n\");");
        }
     }
     toStringMethod.append("\n\treturn value;}");
     construct.pop_back();
     construct.append("){");
     //code.append(construct);
     for(const auto& item : output["output"].items()){
        construct.append("\n\tthis->").append(item.key()).append(" = ").append(item.key()).append(";");
     }
     code.append(construct);
     code.append("\n}\n");
     code.append(toStringMethod);
     return code;
}
string TuplesParser::generateTupleClass(json output){
     string code,construct,opbuild;
      string toStringMethod;
    toStringMethod = "\n\t\t\tstring toString();";
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
     code.append(construct).append(opbuild).append(toStringMethod).append("\n\t};\n");
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
    string listOfVerifiersForStages = "\nconst list<string> stages_verifiers_list = {";
    appendFile(code);

    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
         //code = "class ";
         code = "namespace ";
         code.append(item.value()["name"]);
         listOfStages.append("\"").append(item.value()["name"]).append("\",");
         listOfVerifiersForStages.append("\"").append(item.value()["infos"]["verifierClass"]).append("\",");
         code.append("\n{\n");
         code.append(generateTupleClass(item.value()["infos"]));
         //code.append("};\n");
         code.append("}\n");
         appendFile(code);
    }
    listOfStages.pop_back();
    listOfVerifiersForStages.pop_back();
    listOfStages.append("};\n");
    listOfVerifiersForStages.append("};");
    appendFile(listOfStages);
    appendFile(listOfVerifiersForStages);
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
      code.append(generateTupleClassConstructor(item.value()));
      code.append("\n");
      appendFile(code);
    }
    this->classNameDeff.close();

    //GENERATING HEADER FILE FOR FACTORY
      //GENERATING .H
    this->classNameDef = FACTORY_FILE_H;
    openFluxFile();
    code = "#ifndef ";
    code.append(FACTORY_FILE_HU).append("\n#define ").append(FACTORY_FILE_HU).append("\n\n");
    string baseClass = "#include \"";
    baseClass.append(BASE_FILE)
                 .append("\"");
    vector<string> includesListCPPFactory ={"#include <memory>","#include <map>","#include <variant>",baseClass};
    /*includeHeader = "#include \"";
    includeHeader.append(TUPLES_FILE_H)
                 .append("\"");
    includesListCPPFactory.push_back(includeHeader);*/
    string includeSingle;
    string singleInstanciation;
    string prevStage = graph["computationGraph"]["firstStage"];
    string actualStage;
    string condInstantiation = "";
    string mapStringEntete = "const std::map<string, std::variant<";
    string mapString = "";
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
        if(prevStage == item.value()["name"])
            continue;
        actualStage = item.value()["name"];
        includeSingle = "#include \"";
        singleInstanciation = "\t\tstatic shared_ptr<";
        singleInstanciation.append(item.value()["infos"]["verifierClass"]).append("> createInstance")
                           .append(item.value()["infos"]["verifierClass"]).append("(){\n\t\t\t")
                           .append(item.value()["infos"]["verifierClass"]).append(" * instance = new ")
                           .append(item.value()["infos"]["verifierClass"]).append("();\n\t\t\t")
                           .append("if(instance != nullptr)")
                           .append("\n\t\t\t\treturn shared_ptr<").append(item.value()["infos"]["verifierClass"])
                           .append("> (instance);\n\t\t\telse\n\t\t\t\treturn nullptr;\n\t\t}\n");
        condInstantiation.append(singleInstanciation);
        includeSingle.append(item.value()["infos"]["verifierClass"]).append(".h\"");
        includesListCPPFactory.push_back(includeSingle);
        mapStringEntete.append("shared_ptr<")
                       .append(item.value()["infos"]["verifierClass"]).append(">,");
        mapString.append("{\"").append(item.value()["infos"]["verifierClass"]).append("\",")
                 .append("VertexObjectFactory::createInstance")
                 .append(item.value()["infos"]["verifierClass"]).append("()},");
        prevStage = actualStage;
    }
    mapString.pop_back();
    mapString.append("\n");
    mapStringEntete.pop_back();
    mapStringEntete.append(">> registry {")
    .append(mapString)
    .append("};");
    //includesListC.
    //code.append(putIncludes(includesListC));
    namepspacesList = "using namespace std;\n\n";
    //namepspacesList.append("\n\n");
    code.append(putIncludesVector(includesListCPPFactory))
        .append(namepspacesList)
        .append("class VertexObjectFactory {\n\tpublic:\n")
        .append(condInstantiation)
        .append("};\n\n")
        .append(mapStringEntete)
        .append("\n\n#endif");
    appendFile(code);
    this->classNameDeff.close();
    //GENERATING CPP FILE FOR FACTORY
      //GENERATING .CPP
   /* this->classNameDef = FACTORY_FILE_NAME;
    openFluxFile();
    code ="";
    includeHeader = "#include \"";
    includeHeader.append(FACTORY_FILE_H)
                 .append("\"");
    vector<string> includesListCPPFactory ={"#include <memory>", includeHeader};
    includeHeader = "#include \"";
    includeHeader.append(TUPLES_FILE_H)
                 .append("\"");
    includesListCPPFactory.push_back(includeHeader);
    //includesListC.
    string includeSingle;
    string singleInstanciation;
    string prevStage = graph["computationGraph"]["firstStage"];
    string actualStage;
    string condInstantiation = "";
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
        if(prevStage == item.value()["name"])
            continue;
        actualStage = item.value()["name"];
        includeSingle = "#include \"";
        singleInstanciation = "\tif(name == \"";
        singleInstanciation.append(item.value()["infos"]["verifierClass"]).append("\")\n\t\t instance = new ")
        .append(item.value()["infos"]["verifierClass"]).append("<").append(prevStage).append("::Tuple,").append(actualStage).append("::Tuple").append(">();\n\n\t");
        condInstantiation.append(singleInstanciation);
        includeSingle.append(item.value()["infos"]["verifierClass"]).append(".h\"");
        includesListCPPFactory.push_back(includeSingle);
        prevStage = actualStage;
    }
     namepspacesList = "using namespace std;\n";
    //namepspacesList.append("\n\n");
    code = putIncludesVector(includesListCPPFactory);
    code.append(namepspacesList);
    appendFile(code);
    code = "shared_ptr<";
        code.append(BASE_CLASS).append("> VertexObjectFactory::createInstance(string name){\n\t")
        .append(BASE_CLASS).append(" * instance = nullptr;\n\t")
        .append(condInstantiation)
        .append("if(instance != nullptr) \n\t\treturn shared_ptr<").append(BASE_CLASS).append("> (instance);\n\telse\n\t\t return nullptr;\n};");
    appendFile(code);
    this->classNameDeff.close();*/
}
string TuplesParser::intToString(int i){
    stringstream temp;
    temp << i;
    return temp.str();

}
