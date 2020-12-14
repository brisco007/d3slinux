#ifndef INSTRUMENTATIONPARSER_H
#define INSTRUMENTATIONPARSER_H
#include <string>
#include <list>
#include "abstractparser.h"

using namespace std;
class InstrumentationParser : public AbstractParser
{
    public:
        /** Default constructor */
        InstrumentationParser(string filename);
        /** Default destructor */
        ~InstrumentationParser();
         /**to string */
        std::string toString();
        /**parsing the json config file*/
        void parseFile();
        /**adds the required includes in the generated file
        here are the includes for the different types used C++ standard and
        custom from dev*/
        string putIncludes(list<string> includesList);
        /**adds the required includes in the generated file
        here are the includes for the different types used C++ standard and
        custom from dev*/
        string putIncludesActions(list<string> includesList);
        /**generate an insertion (a pin tool injection function)*/
        string generateAnInsertion(map<string,string> stages);
        /**generate an action (globally regardless of its nature it is likely a switchcase)*/
        string generateAnyAction(map<string,string> stages);
        /**generate the action addTuple to add a tuple into a state (the actions file should then include StateExposer.h*/
        string generateAddTupleSpecific(map<string,string> stages);
        /**generate the action addTuple to remove a tuple into a state (the actions file should then include StateExposer.h*/
        string generateDelTupleSpecific(map<string,string> stages);
        /*the addTuple and DelTuple specific will be used in generate any action all the types there will change according to the file*/
        /**add to a file*/
        void appendFile(string codeToAdd);
        /**the main function to call for generating the g_instrumentation.cpp file*/
        void generateInstrumentationFileContent();
        /**the main function to call for generating the g_actions.cpp file*/
        void generateActionsFileContent();
};

#endif // INSTRUMENTATIONPARSER_H
