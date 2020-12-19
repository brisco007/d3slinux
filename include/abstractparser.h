#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#define BASE_DIRECTORY "generated_files"
using namespace nlohmann;

class AbstractParser
{
    public:
        std::string toString();
    protected:
        const char* baseDir = BASE_DIRECTORY; //!< Member variable "baseDir"
        std::string const baseDirS =  BASE_DIRECTORY; //!< Member variable "baseDirS"
        std::string classNameDef; //!< Member variable "namespaceDef"
        std::ofstream classNameDeff; //!< Member variable "*wstream;"
        std::string graphName; //!<
        json graph;
};

#endif // ABSTRACTPARSER_H
