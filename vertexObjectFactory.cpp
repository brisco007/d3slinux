#include <string>
#include <memory>
#include "vertexObjectFactory.h"
#include "g_stagestypes.h"
#include "AlternationTest.h"
#include "Agglutination.h"


using namespace std;
template<class T,class U>
shared_ptr<AbstractVertex<T,U>> VertexObjectFactory<T,U>::createInstance(string name){
	AbstractVertex<T,U> * instance = nullptr;
		if(name == "AlternationTest")
		 instance = new AlternationTest();

		if(name == "Agglutination")
		 instance = new Agglutination();

	if(instance != nullptr) 
		return shared_ptr<AbstractVertex<T,U>> (instance);
	else
		 return nullptr;
}
