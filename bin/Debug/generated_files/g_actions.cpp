#include <string>
#include <iostream>
#include <list>
#include <tuple>
#include "g_stagestypes.h"
#include "g_actions.h"


using namespace std;
void addTuple(args...){
	V0::Tuple t = V0::Tuple::Tuple(args[0],args[1],args[2]);
	cout << "tuple created with first param " << args[0]<<endl;
}

void delTuple(args...){
	V0::Tuple t = V0::Tuple::Tuple(args[0],args[1],args[2]);
	cout << "tuple created with first param " << args[0]<<endl;
}

