#include <string>
#include <iostream>
#include <list>
#include <tuple>
#include "g_stagestypes.h"


using namespace std;

V0::Tuple::Tuple(int clientID,string lockModeV0,double lockModeV3){
	this->clientID = clientID;
	this->lockModeV0 = lockModeV0;
	this->lockModeV3 = lockModeV3;
}


V1::Tuple::Tuple(int clientID,string lockModeV1){
	this->clientID = clientID;
	this->lockModeV1 = lockModeV1;
}


V2::Tuple::Tuple(string lockModeV2){
	this->lockModeV2 = lockModeV2;
}

