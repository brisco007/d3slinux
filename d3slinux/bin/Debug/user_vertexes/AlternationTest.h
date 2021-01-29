#ifndef GGGGGGG
#define GGGGGGG

#include "abstractVertex.h"
#include <iostream>
#include <string>

class AlternationTest : public AbstractVertex<V0::Tuple,V1::Tuple> {
	public:
		void execute(const list<V0::Tuple> & snapshot);
};

#endif
