#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "pin.H"
#include "g_instrumentation.h"
#include "g_actions.h"


using namespace std;

VOID Image(IMG img, void *v){
	for (SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym)){
		 string undFuncName = PIN_UndecorateSymbolName(SYM_Name(sym), UNDECORATION_NAME_ONLY);
		if (undFuncName == "lockAcquired"){
			RTN mulRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(sym));
			if (RTN_Valid(mulRtn)){
				RTN_Open(mulRtn);
				RTN_InsertCall(mulRtn, IPOINT_AFTER, (AFUNPTR)addTuple,IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 2, IARG_END);
				RTN_Close(mulRtn);
			}
		}
		if (undFuncName == "lockAcquired"){
			RTN mulRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(sym));
			if (RTN_Valid(mulRtn)){
				RTN_Open(mulRtn);
				RTN_InsertCall(mulRtn, IPOINT_BEFORE, (AFUNPTR)delTuple,IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 3, IARG_END);
				RTN_Close(mulRtn);
			}
		}
		if (undFuncName == "lockReleased"){
			RTN mulRtn = RTN_FindByAddress(IMG_LowAddress(img) + SYM_Value(sym));
			if (RTN_Valid(mulRtn)){
				RTN_Open(mulRtn);
				RTN_InsertCall(mulRtn, IPOINT_BEFORE, (AFUNPTR)addTuple,IARG_FUNCARG_ENTRYPOINT_VALUE, 0, IARG_FUNCARG_ENTRYPOINT_VALUE, 1, IARG_FUNCARG_ENTRYPOINT_VALUE, 4, IARG_END);
				RTN_Close(mulRtn);
			}
		}
		
		}
	}