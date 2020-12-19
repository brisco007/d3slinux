#ifndef TUPLESPARSER_H
#define TUPLESPARSER_H
#include <string>
#include "abstractparser.h"
#include <nlohmann/json.hpp>
#include <list>
using namespace std;
using namespace nlohmann;

class TuplesParser : public AbstractParser
{
    public:
        /** Default constructor */
        TuplesParser(std::string filename);
        /** Default destructor */
        ~TuplesParser();
        /**to string */
        std::string toString();
        /**parsing the json config file*/
        void parseFile(string filename);
        /**adds the required includes in the generated file
        here are the includes for the different types used C++ standard and
        custom from dev*/
        string putIncludes(list<string> includesList);
        /**generate the vector of stagesList*/
        string generateStagesVector(map<string,string> stages);
        /**generate a class*/
        string generateBlockClass(string className);
        /**generate an internal class named Tuple */
        string generateTupleClass(json output);
        /**generate a collection of elements*/
        string generateCollection();
        /**add to file*/
        void appendFile(string codeToAdd);
        /**the main function to call for generating the tuples file*/
        void generateFile();
    protected:

    private:
};

#endif // TUPLESPARSER_H
