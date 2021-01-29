#ifndef G_ACTIONS_H
#define G_ACTIONS_H

#include <string>
#include <iostream>
#include <list>
#include "stateExposer.h"
#include "g_stagestypes.h"


using namespace std;
using namespace V0;

const int numberOfFunctions = 3;

void addTuple(int clientID,string lockModeV0,double lockModeV3);

void delTuple(int clientID,string lockModeV0,double lockModeV3);



#endif