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
string V0::Tuple::toString(){
	string value="Tuple Value:\n";
	value.append("-clientID : ").append(to_string(this->clientID)+"\n");
	value.append("-lockModeV0 : ").append(this->lockModeV0+"\n");
	value.append("-lockModeV3 : ").append(to_string(this->lockModeV3)+"\n");
	return value;}

V1::Tuple::Tuple(int clientID,string lockModeV1){
	this->clientID = clientID;
	this->lockModeV1 = lockModeV1;
}
string V1::Tuple::toString(){
	string value="Tuple Value:\n";
	value.append("-clientID : ").append(to_string(this->clientID)+"\n");
	value.append("-lockModeV1 : ").append(this->lockModeV1+"\n");
	return value;}

V2::Tuple::Tuple(string lockModeV2){
	this->lockModeV2 = lockModeV2;
}
string V2::Tuple::toString(){
	string value="Tuple Value:\n";
	value.append("-lockModeV2 : ").append(this->lockModeV2+"\n");
	return value;}
