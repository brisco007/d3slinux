#include "instrumentationparser.h"
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <list>
#include "tuplesparser.h"
#include <sstream>

#define ACCEPTED_ERRNO 17
#define ACTIONS_FILE_NAME "g_actions.cpp"
#define ACTIONS_FILE_H "g_actions.h"
#define ACTIONS_FILE_HU "G_ACTIONS_H"
#define INSTRUMENTATION_FILE_NAME "g_instrumentation.cpp"
#define INSTRUMENTATION_FILE_H "g_instrumentation.h"
#define INSTRUMENTATION_FILE_HU "G_INSTRUMENTATION_H"
#define STATE_FILE_H "state.h"
#define STATE_FILE_HU "STATE_H"

extern const string ADD_TUPLE = "addTuple";
extern const string DEL_TUPLE = "delTuple";

InstrumentationParser::InstrumentationParser(std::string filename)
{
    try{
        parseFile(filename);
    }catch(exception & e){
        throw e;
    }
    this->graphName = filename;
    //this->classNameDef = ACTIONS_FILE_H;
    //openFluxFile();
}

void InstrumentationParser::parseFile(string filename){
     try{
     ifstream i(filename);
     i >> graph;
   }catch(::detail::parse_error & e){
        cout << e.what();
        throw e;
   }
}

void InstrumentationParser::openFluxFile(){
    if ((mkdir(this->baseDir, 0777) == -1) && errno != ACCEPTED_ERRNO)
        cerr << "Error :  "<<errno<<" " << strerror(errno) << endl;
    else{
        cout << "created instrumentation parser for parser for "<< this->baseDir<<"/"<<this->classNameDef<<endl;
        this->classNameDeff.open("./"+this->baseDirS+"/"+this->classNameDef,ios::out/*|ios::app*/);
    }
}
void InstrumentationParser::appendFile(string codeToAdd){
    if(this->classNameDeff.good()){
        this->classNameDeff << codeToAdd;
    }
}
string InstrumentationParser::putIncludes(list<string> includesList){
    string include;
    include = "#include <string>\n";
    for (auto const& i : includesList) {
        include.append(i)
               .append("\n");
    }
    include.append("\n\n");
    return include;
}

// TODO (brice#1#12/25/20): Modifier les generateFiles conformément aux besoins
void InstrumentationParser::generateInstrumentationFileContent(){
     /*iterate in the main list f stages to know the classes to create*/
  /*  string code;
    //include namespaces
    //GENERATING .H
    //include everything
    list<string> includesListH = {"#include <iostrean>","#include <list>","#include <tuple>"};
    code = putIncludes(includesListH);
    //adding namepsaces
    code.append("using namespace std;\n\n");
    //adding the list of stages
    string listOfStages = "\nlist<string> list_of_stages = {";
    appendFile(code);

    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
         code = "class ";
         code.append(item.value()["name"]);
         listOfStages.append("\"").append(item.value()["name"]).append("\",");
         code.append("\n{\n");
         code.append(generateTupleClass(item.value()["infos"]));
         code.append("}\n");
         appendFile(code);
    }
    listOfStages.pop_back();
    listOfStages.append("}");
    appendFile(listOfStages);
    this->classNameDeff.close();

    //GENERATING .CPP
    this->classNameDef = TUPLES_FILE_NAME;
    openFluxFile();
    code ="";
    string includeHeader = "#include \"";
    includeHeader.append(TUPLES_FILE_H)
                 .append("\"");
    list<string> includesListC {"#include <iostrean>","#include <list>","#include <tuple>", includeHeader};
    //includesListC.
    code = putIncludes(includesListC);
    code.append("using namespace std;\n\n");
    appendFile(code);
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
      code = "\n";
      code.append(item.value()["name"]);
      code.append("::");
      code.append(generateTupleClassConstructor(item.value()["infos"]));
      code.append("\n");
      appendFile(code);
    }
    this->classNameDeff.close();*/
}
string InstrumentationParser::generateAddTupleSpecific(json output,json firstStage){
// TODO (brice#1#12/25/20): The addTUple should add the created tuple into the state
    static bool flag = false;
    if(flag == false){
        flag = true;
        string code = "void ";
        code.append(ADD_TUPLE).append("(").append(outputOfFirstStage()).append("){\n\t");
        code.append("Tuple t = ").append("Tuple::Tuple(");
        for(const auto& item : firstStage["infos"]["output"].items()){
            code.append(item.key()).append(",");
        }
        code.pop_back();
        code.append(");\n")
            .append("\t(stateExposer.getInstance()).clock.local_event();\n")
            .append("\t(stateExposer.getInstance()).state.list_of_tuples.push_back(t);\n")
            .append("}\n\n");
        return code;
    }else {
        return "";
    }
}
string InstrumentationParser::generateDelTupleSpecific(json output,json firstStage){
    // TODO (brice#1#12/25/20): The addTUple should remove the created tuple into the state
    static bool flag = false;
    if(flag == false){
        flag = true;
        string code = "void ";
        code.append(DEL_TUPLE).append("(").append(outputOfFirstStage()).append("){\n\t");
        code.append("Tuple t = ").append("Tuple::Tuple(");
        for(const auto& item : firstStage["infos"]["output"].items()){
            code.append(item.key()).append(",");
        }
        code.pop_back();
        code.append(");\n")
            .append("\t(stateExposer.getInstance()).clock.local_event();\n")
            .append("\t(stateExposer.getInstance()).state.list_of_tuples.remove(t);\n")
            .append("}\n\n");
        return code;
    }else{
        return "";
    }
}
// TODO (brice#1#12/25/20): MAKE SURE OF THAT THE NUMBER OF FUNCTIONS GIVEN IS THE REAL ONE. SAME FOR THE NUMBER OF STAGES
// TODO (brice#1#12/25/20): The number of params given to the actions should be the same as the exposers output's one

void InstrumentationParser::generateAnyAction(json output){
//lookup for the first stage in graph
// TODO (brice#1#12/25/20): what if the first stage described is not one of the given stages
         string code;
         string first = graph["computationGraph"]["firstStage"];
         json firstStage;
         for(auto& item : graph["computationGraph"]["stagesDescription"].items()){
            if(item.value()["name"] == first){
                firstStage = item.value();
                break;
            }
         }
         string action = output["infos"]["action"];
         if(action == ADD_TUPLE){
                code = generateAddTupleSpecific(output,firstStage);
                appendFile(code);
         }else if(action == DEL_TUPLE){
                code = generateDelTupleSpecific(output,firstStage);
                appendFile(code);
         }else {
                string exceptmsg = "Unknown action for state exposer \"";
                exceptmsg.append(action)
// TODO (brice#1#12/25/20): find how to handle this exception wisely
                         .append("\" please review your json configuration file");
                throw exceptmsg;
         }

}

void InstrumentationParser::generateStateHeaderFileContent(){
       /*generate the file */
    string code;
    //include namespaces
    //GENERATING .H
    this->classNameDef = STATE_FILE_H;
    openFluxFile();
    //include everything
    string includeTupleDef = "#include \"";
    includeTupleDef.append(TUPLES_FILE_H).append("\"");
    list<string> includesListH = {"#include <list>","#include \"lamport_clock.h\"",includeTupleDef};
    code = "#ifndef ";
    code.append(STATE_FILE_HU).append("\n#define ").append(STATE_FILE_HU).append("\n\n")
        .append(putIncludes(includesListH))
        .append("using namespace std;\nusing namespace ")
        .append(graph["computationGraph"]["firstStage"])
        .append(";\n\n")
        .append("typedef struct State{\n")
        .append("\tlist<Tuple> list_of_tuples;\n")
        .append("\tLamportTime timestamp;\n")
        .append("\tlong nodeID;\n")
        .append("} State;\n\n")
        .append("\n\n#endif");
    this->appendFile(code);
    this->classNameDeff.close();
}
void InstrumentationParser::generateActionsFileContent(){
    /*iterate in the main list f stages to know the classes to create*/
    string code;
    //include namespaces
    //GENERATING .H
    this->classNameDef = ACTIONS_FILE_H;
    openFluxFile();
    //include everything
    string includeTupleDef = "#include \"";
    includeTupleDef.append(TUPLES_FILE_H).append("\"");
    list<string> includesListH = {"#include <iostream>","#include <list>","#include \"stateexposer.h\"",includeTupleDef};
    code = "#ifndef ";
    code.append(ACTIONS_FILE_HU).append("\n#define ").append(ACTIONS_FILE_HU).append("\n\n");
    code.append(putIncludes(includesListH));
    //adding namepsaces
    code.append("using namespace std;\nusing namespace ")
        .append(graph["computationGraph"]["firstStage"])
        .append(";\n\n");
    //adding the number of functions
    code.append("const int numberOfFunctions = ").append(intToString(graph["monitoring"]["numberOfFunctions"])).append(";\n\n");
    this->appendFile(code);
    bool a1 = false;
    bool a2 = false;
    for(const auto& item : this->graph["monitoring"]["functionsDescription"].items()){
// TODO (brice#2#12/25/20): make sure of the fact that we don't have any duplicated function inside the .h
// TODO (brice#1#12/25/20): Check if the action is in a list instead of a if with each constant
         string action = item.value()["infos"]["action"];
         if(action == ADD_TUPLE){
               if(a1 == false){
                a1 = true;
                code = "void ";
                code.append(ADD_TUPLE).append("(").append(outputOfFirstStage()).append(");\n\n");
                appendFile(code);
               }
         }else if(action == DEL_TUPLE){
                if(a2 == false){
                 a2 = true;
                 code = "void ";
                 code.append(DEL_TUPLE).append("(").append(outputOfFirstStage()).append(");\n\n");
                 appendFile(code);
                }
         }else {
                string exceptmsg = "Unknown action for state exposer \"";
                exceptmsg.append(item.value()["action"])
// TODO (brice#1#12/25/20): find how to handle this exception wisely
                         .append("\" please review your json configuration file");
                throw exceptmsg;
         }
    }
    appendFile("\n\n#endif");
    this->classNameDeff.close();

    //GENERATING .CPP
    this->classNameDef = ACTIONS_FILE_NAME;
    openFluxFile();
    code ="";
    string includeHeader = "#include \"";
    includeHeader.append(TUPLES_FILE_H)
                 .append("\"");
    list<string> includesListC = {"#include <iostream>","#include <list>","#include \"stateexposer.h\"", includeHeader};
    includeHeader = "#include \"";
    includeHeader.append(ACTIONS_FILE_H).append("\"");
    includesListC.push_back(includeHeader);
    //includesListC.
    code = putIncludes(includesListC);
    code.append("using namespace std;\nusing namespace ")
        .append(graph["computationGraph"]["firstStage"])
        .append(";\n\n");
    appendFile(code);
    for(const auto& item : this->graph["monitoring"]["functionsDescription"].items()){
        generateAnyAction(item.value());
    }
    this->classNameDeff.close();
}
string InstrumentationParser::outputOfFirstStage(){
    string code ="";
    for(const auto& item : this->graph["computationGraph"]["stagesDescription"].items()){
         if(item.value()["name"] == graph["computationGraph"]["firstStage"]){
             for(const auto& output : item.value()["infos"]["output"].items()){
                code.append(output.value()).append(" ").append(output.key()).append(",");
             }
             code.pop_back();
            break;
         }
    }
    return code;
}
string InstrumentationParser::intToString(int i){
    stringstream temp;
    temp << i;
    return temp.str();

}
