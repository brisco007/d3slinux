#ifndef VERTEX_OBJECT_FACTORY_H
#define VERTEX_OBJECT_FACTORY_H

#include <string>
#include <memory>
#include <map>
#include <variant>
#include "abstractVertex.h"
#include "AlternationTest.h"
#include "Agglutination.h"


using namespace std;

class VertexObjectFactory {
	public:
		static shared_ptr<AlternationTest> createInstanceAlternationTest(){
			AlternationTest * instance = new AlternationTest();
			if(instance != nullptr)
				return shared_ptr<AlternationTest> (instance);
			else
				return nullptr;
		}
		static shared_ptr<Agglutination> createInstanceAgglutination(){
			Agglutination * instance = new Agglutination();
			if(instance != nullptr)
				return shared_ptr<Agglutination> (instance);
			else
				return nullptr;
		}
};

const std::map<string, std::variant<shared_ptr<AlternationTest>,shared_ptr<Agglutination>>> registry {{"AlternationTest",VertexObjectFactory::createInstanceAlternationTest()},{"Agglutination",VertexObjectFactory::createInstanceAgglutination()}
};

#endif