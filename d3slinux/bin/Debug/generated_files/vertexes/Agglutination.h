#ifndef GGGGGGGF
#define GGGGGGGF

#include "abstractVertex.h"
#include <iostream>
#include <string>

class Agglutination : public AbstractVertex<V1::Tuple,V2::Tuple>{
	public:
		void execute(const list<V1::Tuple> & snapshot);
};

#endif
