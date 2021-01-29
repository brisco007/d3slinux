#include <iostream>
#include <string>
#include "g_stagestypes.h"

using namespace std;

int main(){
	cout << "Hello world"<<endl;
	V0::Tuple t(255,"exclusive",64.5);
	cout << t.toString()<<endl; 
	V1::Tuple t1(45,"shared");
	cout <<t1.toString()<<endl; 
	V2::Tuple t2("none");
	cout << t2.toString()<<endl; 
	cout <<"Other params recorded : \n- numberOfStages: "<< numberOfStages << "\n- firstStage: "<<firstStage<<"\n- finalStage: "<<finalStage<< "\n- list of stages: "<<endl; 
	for (const string &it : stages_list){
		cout << "\t* "<<it<<endl;  
	}
	return 0;
}
