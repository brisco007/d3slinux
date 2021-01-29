#include <iostream>
#include <string>
#include <stdlib.h>
#include "tuplesparser.h"
#include "instrumentationparser.h"
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

void parsingFile(string & filename){
    cout << "\n - Enter the absolute path of your configuration JSON file. you can find a sample here /*/*/graph.json : ";
    cin >> filename;
    try {
     TuplesParser tupleparser(filename);
     tupleparser.generateFile();
     InstrumentationParser instruparser(filename);
     instruparser.generateStateHeaderFileContent();
     instruparser.generateActionsFileContent();
     instruparser.generateInstrumentationFileContent();
    }catch(exception & e){
      cout << e.what();
      parsingFile(filename);
    }
}
int main()
{
    string filename;
    cout << "    Welcome to d3slinux!\nYou are about to test your distributed system. it will be done through some few steps:" << endl;
    parsingFile(filename);
    const auto copyOptions = fs::copy_options::update_existing;
    fs::copy("generated_files/g_stagestypes.cpp", "generated_files/vertexes/g_stagestypes.cpp",copyOptions);
    fs::copy("generated_files/g_stagestypes.h", "generated_files/vertexes/g_stagestypes.h",copyOptions);
    fs::copy("generated_files/vertexObjectFactory.h", "generated_files/vertexes/vertexObjectFactory.h",copyOptions);
    system("cd generated_files/vertexes && g++ -c *.cpp -std=c++17 && ar rvs ./../outputs/chcklogic.a *.o");
    //string generationFilePath = "./generated_files/main.cpp";
    //const char* command = "g++ -Wall -o test ./generated_files/main.cpp";
    //system(command);
    //system("./test");
    return 0;
}

