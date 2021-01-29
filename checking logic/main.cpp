#include "vertexObjectFactory.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
	//VertexObjectFactory vof;
	auto i1 = registry.find("AlternationTest");
	auto i2 =  registry.find("Agglutination");
	/*auto i1 = VertexObjectFactory<V0::Tuple,V1::Tuple>::createInstance("AlternationTest");	
	auto i2 = VertexObjectFactory<V1::Tuple,V2::Tuple>::createInstance("Agglutination");*/
	//i1->execute({});
	//i2->execute({});
	get<0>(i1->second)->execute({});
	get<1>(i2->second)->execute({});
	//cout << i2;
	return 0;
}
