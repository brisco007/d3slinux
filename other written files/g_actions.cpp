
#include "pin.H"
#include <iostream>

using namespace std;

void Arg1Before(char * name, ADDRINT size)
{
    cout << name << "(" << size << ")" << endl;
}

void MulAfter(ADDRINT ret)
{
    cout << "  returns " << ret << endl;
}


