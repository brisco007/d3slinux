#include <iostream>
#include <string>
#include "tuplesparser.h"
#include "instrumentationparser.h"
using namespace std;

int main()
{
    string filename;
    cout << "    Welcome to d3slinux!\nYou are about to test your distributed system. it will be done through some few steps:" << endl;
    cout << " - Enter the name of your configuration JSON file. you can find a sample here /*/*/graph.json : ";
    cin >> filename;
    TuplesParser tupleparser(filename);
    InstrumentationParser instruparser(filename);
    return 0;
}

