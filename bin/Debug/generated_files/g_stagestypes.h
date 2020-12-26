#ifndef G_STAGESTYPES_H
#define G_STAGESTYPES_H

#include <string>
#include <iostream>
#include <list>
#include <tuple>


using namespace std;

const int numberOfStages = 3;
const string firstStage = "V0";
const string finalStage = "V2";

namespace V0
{

	class Tuple
	{
		public:
			int clientID;
			string lockModeV0;
			double lockModeV3;
			Tuple(int clientID,string lockModeV0,double lockModeV3);
	};
}
namespace V1
{

	class Tuple
	{
		public:
			int clientID;
			string lockModeV1;
			Tuple(int clientID,string lockModeV1);
	};
}
namespace V2
{

	class Tuple
	{
		public:
			string lockModeV2;
			Tuple(string lockModeV2);
	};
}

const list<string> stages_list = {"V0","V1","V2"};

#endif