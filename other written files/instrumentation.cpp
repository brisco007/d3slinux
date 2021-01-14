#include "pin.H"
#include <iostream>
#include <fstream>
#include "instrumentation.h"
#include "g_actions.h"

#define MUL "mul"
#define DIV "div"


using namespace std;

void Image(IMG img, void *v)
{
    // Instrument the mul() and div() functions.  Print the input argument
    // of each mul() or div(), and the return value of mul().
    //
    //  Find the mul() function.
    
     for (SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym))
    {
        string undFuncName = PIN_UndecorateSymbolName(SYM_Name(sym), UNDECORATION_NAME_ONLY);

        //  Find the RtlAllocHeap() function.
        if (undFuncName == MUL)
        {
            RTN mulRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(sym));
            
            if (RTN_Valid(mulRtn))
            {
                // Instrument to print the input argument value and the return value.
                RTN_Open(mulRtn);
                
                RTN_InsertCall(mulRtn, IPOINT_BEFORE, (AFUNPTR)Arg1Before,
                       IARG_ADDRINT, MUL,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                       IARG_END);
       	 RTN_InsertCall(mulRtn, IPOINT_AFTER, (AFUNPTR)MulAfter,
                       IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);
                
                RTN_Close(mulRtn);
            }
        }
    }
}
