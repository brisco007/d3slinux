#ifndef STATE_H
#define STATE_H

#include <string>
#include <list>
#include "lamport_clock.h"
#include "g_stagestypes.h"


using namespace std;
using namespace V0;

typedef unsigned int LamportTime;

typedef struct State{
	list<Tuple> list_of_tuples;
	LamportTime timestamp;
	long nodeID;
} State;



#endif
