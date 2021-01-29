#include "instrumentationparser.h"
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <list>
#include <vector>
#include "tuplesparser.h"
#include <sstream>
#include <algorithm>
//#include "toolsandmacros.h"
#define ACTIONS_FILE_NAME "g_actions.cpp"
#define ACTIONS_FILE_H "g_actions.h"
#define ACTIONS_FILE_HU "G_ACTIONS_H"
#define INSTRUMENTATION_FILE_NAME "g_instrumentation.cpp"
#define INSTRUMENTATION_FILE_H "g_instrumentation.h"
#define INSTRUMENTATION_FILE_HU "G_INSTRUMENTATION_H"
#define STATE_FILE_H "state.h"
#define STATE_FILE_HU "STATE_H"
#define ACCEPTED_ERRNO 17

//#define D3SL_ERROR(e) "[ERROR] : " e
//#define D3SL_INFO(e) "[INFO] : " e

const string TIMING_BEFORE = "before";
const string TIMING_AFTER = "after";
const string ADD_TUPLE = "addTuple";
const string DEL_TUPLE = "delTuple";

//const string D3SL_ERROR(string a){string p ; p = "[ERROR] : "; p.append(a); return p;}
//const string D3SL_INFO(string a){string p ; p = "[INFO] : "; p.append(a); return p;}
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
        string info = "created instrumentation parser for parser for ";
        info.append(this->baseDir).append("/").append(this->classNameDef).append("\n");
        cout << D3SL_INFO(info)<<endl;
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
    string code;
    //include namespaces
    //GENERATING .H
    this->classNameDef = INSTRUMENTATION_FILE_H;
    openFluxFile();
    string includeDef = "#include \"pin.H\"\n\n";
    code = "#ifndef ";
    code.append(INSTRUMENTATION_FILE_HU).append("\n#define ").append(INSTRUMENTATION_FILE_HU).append("\n\n")
        .append(includeDef)
        .append("using namespace std;\n\nVOID Image(IMG img, void *v);\n\n#endif");
    this->appendFile(code);
    this->classNameDeff.close();
 //GENERATING .CPP
    this->classNameDef = INSTRUMENTATION_FILE_NAME;
    openFluxFile();
    code ="";
    string includeHeader = "#include \"pin.H\"";
    list<string> includesListC = {"#include <iostream>","#include <fstream>","#include <list>", includeHeader};
    includeHeader = "#include \"";
    includeHeader.append(INSTRUMENTATION_FILE_H).append("\"");
    includesListC.push_back(includeHeader);
    includeHeader = "#include \"";
    includeHeader.append(ACTIONS_FILE_H).append("\"");
    includesListC.push_back(includeHeader);
    code = putIncludes(includesListC);
    code.append("using namespace std;\n\n")
        .append("VOID Image(IMG img, void *v){\n\t")
        .append("for (SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym)){\n\t\t")
        .append(" string undFuncName = PIN_UndecorateSymbolName(SYM_Name(sym), UNDECORATION_NAME_ONLY);\n\t\t");


    for(const auto& item : this->graph["monitoring"]["functionsDescription"].items()){
        code.append("if (undFuncName == \"")
            .append(item.value()["infos"]["function"])
            .append("\"){\n\t\t\t")
            .append("RTN mulRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(sym));\n\t\t\t")
            .append("if (RTN_Valid(mulRtn)){\n\t\t\t\t")
            .append("RTN_Open(mulRtn);\n\t\t\t\t")
            .append("RTN_InsertCall(mulRtn, ")
            .append(item.value()["infos"]["timing"] == TIMING_BEFORE ? "IPOINT_BEFORE, ": "IPOINT_AFTER, ")
            .append("(AFUNPTR)")
            .append(item.value()["infos"]["action"])
            .append(",")
            .append(parseParams(item.value()["infos"]["tupleDescription"], item.value()["infos"]["timing"]))
            .append(");\n\t\t\t\t")
            .append("RTN_Close(mulRtn);\n\t\t\t}\n\t\t}\n\t\t");
    }
    code.append("\n\t\t}\n\t}");
    appendFile(code);
    this->classNameDeff.close();
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
                throw runtime_error(D3SL_ERROR(exceptmsg));
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
    list<string> includesListH = {"#include <iostream>","#include <list>","#include \"stateExposer.h\"",includeTupleDef};
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
                throw runtime_error(D3SL_ERROR(exceptmsg));
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
string InstrumentationParser::parseParams(string params, string timing){
    string code= "";
    params.erase(remove(params.begin(), params.end(), '('), params.end());
    params.erase(remove(params.begin(), params.end(), ')'), params.end());
    params.erase(remove(params.begin(), params.end(), '$'), params.end());
    params.erase(remove(params.begin(), params.end(), ' '), params.end());
    stringstream ss(params);
    vector<string> result;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        result.push_back( substr );
    }
    for(auto itr : result){
        if(itr == "ret"){
            if(timing == TIMING_BEFORE){
                throw runtime_error(D3SL_ERROR("Cannot use the 'before' timing with a return argument"));
            }else {
                code.append("IARG_FUNCRET_EXITPOINT_VALUE, ");
            }
        }else{
         if(is_number(itr)){
              code.append("IARG_FUNCARG_ENTRYPOINT_VALUE, ")
                    .append(itr)
                    .append(", ");
         }else{
            throw runtime_error(D3SL_ERROR("Tuple definition arguments must be $integers or 'ret' value"));
         }
        }

    }
    code.append("IARG_END");
    return code;
}

bool InstrumentationParser::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
