#ifndef INSTRUMENTATIONPARSER_H
#define INSTRUMENTATIONPARSER_H
#include <string>
#include <list>
#include "abstractparser.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

class InstrumentationParser : public AbstractParser
{
    public:
        /** Default constructor */
        InstrumentationParser(string filename);
         //**to string */
        //std::string toString();
        /**parsing the json config file*/
        void parseFile(string filename);
        void openFluxFile();
        /**adds the required includes in the generated file
        here are the includes for the different types used C++ standard and
        custom from dev*/
        string putIncludes(list<string> includesList);
        /**adds the required includes in the generated file
        here are the includes for the different types used C++ standard and
        custom from dev*/
        string putIncludesActions(list<string> includesList);
        /**generate an insertion (a pin tool injection function)*/
        string generateAnInsertion(json stages);
        string intToString(int i);
        /**generate an action (globally regardless of its nature it is likely a switchcase)*/
        void generateAnyAction(json output);
        /**generate the action addTuple to add a tuple into a state (the actions file should then include StateExposer.h*/
        string generateAddTupleSpecific(json output,json firstStage);
        /**generate the action addTuple to remove a tuple into a state (the actions file should then include StateExposer.h*/
        string generateDelTupleSpecific(json output,json firstStage);
        /*the addTuple and DelTuple specific will be used in generate any action all the types there will change according to the file*/
        /**add to a file*/
        void appendFile(string codeToAdd);
        /**the main function to call for generating the g_instrumentation.cpp file*/
        void generateInstrumentationFileContent();
        /**the main function to call for generating the g_actions.cpp file*/
        void generateActionsFileContent();
        void generateStateHeaderFileContent();
        string outputOfFirstStage();
        string parseParams(string params, string timing);
        bool is_number(const std::string& s);
};

#endif // INSTRUMENTATIONPARSER_H
