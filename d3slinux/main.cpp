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
void generateCheckingLogic(){
    const auto copyOptions = fs::copy_options::update_existing;
    fs::create_directory("temporary");
    fs::copy("generated_files/g_stagestypes.cpp", "temporary/g_stagestypes.cpp",copyOptions);
    fs::copy("generated_files/g_stagestypes.h", "temporary/g_stagestypes.h",copyOptions);
    fs::copy("generated_files/vertexObjectFactory.h", "temporary/vertexObjectFactory.h",copyOptions);
    system("cp vertexes/* temporary/");
    system("cp user_vertexes/* temporary/");
    system("cd temporary && g++ -c *.cpp -std=c++17 && ar rvs ./../outputs/chcklogic.a *.o");
    system("rm -rf ./temporary && rm -rf ./generated_files");
}
int main()
{
    string filename;
    cout << "    Welcome to d3slinux!\nYou are about to test your distributed system. it will be done through some few steps:" << endl;
    parsingFile(filename);
    generateCheckingLogic();
    return 0;
}

