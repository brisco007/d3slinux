#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#define BASE_DIRECTORY "generated_files"
using namespace nlohmann;

using namespace std;
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
        string D3SL_ERROR(string a){string p ; p = "[ERROR] : "; p.append(a); return p;}
        string D3SL_INFO(string a){string p ; p = "[INFO] : "; p.append(a); return p;}
};

#endif // ABSTRACTPARSER_H
