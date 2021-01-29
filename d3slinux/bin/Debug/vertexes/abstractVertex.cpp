#include <string>
#include <iostream>
#include <list>
#include "abstractVertex.h"
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;



template <class T, class U>
string AbstractVertex<T,U>::mapping(const T & t){
	//ostringstream out;
	return to_string((duration_cast<milliseconds> (system_clock::now().time_since_epoch())).count());
	//return out.str();
}
template <class T, class U>
void AbstractVertex<T,U>::setStageLabel(string s){
	this->stageLabel = s;
}
template <class T, class U>
string AbstractVertex<T,U>::getStageLabel(){
	return this->stageLabel;
}
