#ifndef G_AVERTEX_H
#define G_AVERTEX_H

#include <string>
#include <iostream>
#include <list>
#include "g_stagestypes.h"


using namespace std;
class BaseVertex{

};
template <class T, class U>
class AbstractVertex: public BaseVertex{
	public :
		list<U> output;
		virtual void execute(const list<T> & snapshot) = 0 ;
		static string mapping(const T & t);
		void setStageLabel(string s);
		string getStageLabel();
	private:
		string stageLabel;
};

#endif

