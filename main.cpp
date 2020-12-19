#include <iostream>
#include <string>
#include "tuplesparser.h"
#include "instrumentationparser.h"
using namespace std;

void parsingFIle(string & filename){
    cout << "\n - Enter the absolute path of your configuration JSON file. you can find a sample here /*/*/graph.json : ";
    cin >> filename;
    try {
     TuplesParser tupleparser(filename);
     tupleparser.generateFile();
     InstrumentationParser instruparser(filename);
    }catch(exception & e){
      //cout << e.what();
      parsingFIle(filename);
    }
}
int main()
{
    string filename;
    cout << "    Welcome to d3slinux!\nYou are about to test your distributed system. it will be done through some few steps:" << endl;
    parsingFIle(filename);
    return 0;
}

