#include "instrumentationparser.h"
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#define ACCEPTED_ERRNO 17
#define ACTIONS_FILE_NAME "g_actions.cpp"
#define INSTRUMENTATION_FILE_NAME "g_instrumentation.cpp"

InstrumentationParser::InstrumentationParser(std::string filename)
{
     this->classNameDef = INSTRUMENTATION_FILE_NAME;
    this->graphName = filename;
    if ((mkdir(this->baseDir, 0777) == -1) && errno != ACCEPTED_ERRNO)
        cerr << "Error :  "<<errno<<" " << strerror(errno) << endl;
    else{
        cout << "created instrumentation parser for "<< this->baseDir<<"/"<<this->classNameDef<<endl;
        this->classNameDeff = new ofstream("./"+this->baseDirS+"/"+this->classNameDef,ios::out|ios::app);
    }
}

InstrumentationParser::~InstrumentationParser()
{
    //dtor
}
