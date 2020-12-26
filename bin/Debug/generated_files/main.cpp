#include <iostream>
#include <string>
#include "g_stagestypes.h"

using namespace std;

int main(){
	cout << "Hello world"<<endl;
	V0::Tuple t(255,"exclusive",64.5);
	cout << "Created V0 tuple with params : \n- clientID: " << t.clientID << "\n- lockModeV0: "<< t.lockModeV0 << "\n- lockModeV3: "<< t.lockModeV3<<endl<<endl; 
	V1::Tuple t1(45,"shared");
	cout << "Created V0 tuple with params : \n- clientID: " << t1.clientID << "\n- lockModeV1: "<< t1.lockModeV1 <<endl<<endl; 
	V2::Tuple t2("none");
	cout << "Created V0 tuple with param :\n- lockModeV2 "<< t2.lockModeV2 <<endl<<endl; 
	cout <<"Other params recorded : \n- numberOfStages: "<< numberOfStages << "\n- firstStage: "<<firstStage<<"\n- finalStage: "<<finalStage<< "\n- list of stages: "<<endl; 
	for (const string &it : stages_list){
		cout << "\t* "<<it<<endl;  
	}
	return 0;
}
