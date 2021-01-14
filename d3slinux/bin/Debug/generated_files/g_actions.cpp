#include <string>
#include <iostream>
#include <list>
#include "stateexposer.h"
#include "g_stagestypes.h"
#include "g_actions.h"


using namespace std;
using namespace V0;

void addTuple(int clientID,string lockModeV0,double lockModeV3){
	Tuple t = Tuple::Tuple(clientID,lockModeV0,lockModeV3);
	(stateExposer.getInstance()).clock.local_event();
	(stateExposer.getInstance()).state.list_of_tuples.push_back(t);
}

void delTuple(int clientID,string lockModeV0,double lockModeV3){
	Tuple t = Tuple::Tuple(clientID,lockModeV0,lockModeV3);
	(stateExposer.getInstance()).clock.local_event();
	(stateExposer.getInstance()).state.list_of_tuples.remove(t);
}

