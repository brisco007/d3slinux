
#include "pin.H"
#include <iostream>
#include <fstream>
#include "g_instrumentation.h"

using namespace std;

#define MUL "div"
#define DIV "div"

VOID Fini(INT32 code, VOID *v)
{
    cout <<"fini"<<endl;//TraceFile.close();
}

INT32 Usage()
{
    cerr << "This tool produces a trace of calls to mul." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);
    // Never returns
    PIN_StartProgram();
    return 0;
}

