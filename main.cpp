#include <iostream>
#include <string>
#include <stdlib.h>
#include "tuplesparser.h"
#include "instrumentationparser.h"
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
    //string generationFilePath = "./generated_files/main.cpp";
    //const char* command = "g++ -Wall -o test ./generated_files/main.cpp";
    //system(command);
    //system("./test");
    return 0;
}

