#define __GAMEINIT_H_INCLUDED__  
#define __GAMEINIT_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include "math.h"
#include <stdio.h>
#include <float.h>
#include <cstdlib>
#include <ctime>




#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>


using namespace std;

using namespace boost::archive;

#include <fstream>

using namespace boost::archive;

void save()
{
  std::ofstream file{"archive.txt"};
  text_oarchive oa{file};
  int i = 1;
  oa << i;
}

void load()
{
  std::ifstream file{"archive.txt"};
  text_iarchive ia{file};
  int i = 0;
  ia >> i;
  std::cout << i << '\n';
}

int main()
{
  save();
  load();
}

/*

extern bool isturncompleted[5];
extern int whichplayerturn;
extern int startlocationno;
extern int kplane;
extern float jplane;
extern bool showplanetransition;
extern int playerwhocanbuy;
extern int whichplayeristhis;


class City
{
public:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & *name;
        ar & group;
        ar & cost;
        ar & mortagecost;
        ar & house1cost;
        ar & house2cost;
        ar & house3cost;
        ar & house4cost;
        ar & rent0;
        ar & rent1;
        ar & rent2;
        ar & rent3;
        ar & rent4;
        ar & renthotel;
        ar & isbought;
        ar & boughtby;
        ar & totalhouses;
        ar & ishotel;
    }

    string* name;
    int group;
    int cost;
    int mortagecost;
    int house1cost;
    int house2cost;
    int house3cost;
    int house4cost;
    int hotelcost;
    int rent0;
    int rent1;
    int rent2;
    int rent3;
    int rent4;
    int renthotel;
    int isbought;
    int boughtby;
    int totalhouses;
    int ishotel;



};

class Game
{
public:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & startingmoney;
        ar & jailfine;
        ar & tax;
        ar & map;
        ar & totalcolorgroups;
        ar & colorcodes;

        ar & whichplayerturn;

        ar & isturncompleted;
        ar & hismoney;

        cout << "robin"<< endl;
        ar & citiesowned;

        ar & noofcitiesowned;
        ar & citiesofeachgroup;
        ar & currentlocation;

        ar & temporarylocation;

        ar & cities;
        ar & *currency;
    }

    string* currency;
    int startingmoney;
    int jailfine;
    int tax;
    vector <City> cities;
    int map[50][50];
    int totalcolorgroups;
    float colorcodes[20][3];
    int whichplayerturn=1;
    bool isturncompleted[5]={1,1,1,1,1};
    void Generatecolorgroups();

    //string *name[5];
    float hismoney[5];
    int citiesowned[5][100][5];
    int noofcitiesowned[5];
    int citiesofeachgroup[5][50];
    int currentlocation[5];
    int temporarylocation[5];


};
*/
