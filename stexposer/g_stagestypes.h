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
			bool operator == (const Tuple& t) const { return (clientID == t.clientID) &&(lockModeV0 == t.lockModeV0) &&(lockModeV3 == t.lockModeV3) ; }
			bool operator != (const Tuple& t) const { return !operator==(t); }
			string toString();
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
			bool operator == (const Tuple& t) const { return (clientID == t.clientID) &&(lockModeV1 == t.lockModeV1) ; }
			bool operator != (const Tuple& t) const { return !operator==(t); }
			string toString();
	};
}
namespace V2
{

	class Tuple
	{
		public:
			string lockModeV2;
			Tuple(string lockModeV2);
			bool operator == (const Tuple& t) const { return (lockModeV2 == t.lockModeV2) ; }
			bool operator != (const Tuple& t) const { return !operator==(t); }
			string toString();
	};
}

const list<string> stages_list = {"V0","V1","V2"};

#endif