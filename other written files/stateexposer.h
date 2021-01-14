#include "state.h"
#include "lamport_clock.h"
#include "Networking.h"

class stateexposer {
	private:
		long nodeID;
		stateexposer();
		stateexposer stexposer;
		LamportClock clock;		
	public:
		State state;
		getInstance();
		expose(); // sends directly the state with the given node id and the value of clock that we add to the state 
		exposeInfinite(); // expose indefinitely
		exposeWithinAPeriod(long period);//expose within that period
		/*for the two exposes methods, we loop accordingly to the lamport clock and call expose when appropriate (we also verify all the rules before calling expose() such that the paper is fully respected we shall enumerate all these rules. at the begining of an iteration, we reinitialise the content of list_of_tuples such that it can be set wthout worries by the actions.*/
		//this class is the core class of the state exposer. 
		// we should not care about how the list of tuples will enter the state it will be done by the actions so it is okay.
		// this class is singleton. so to have an instance we shall call the method getInstance. the private constructor will initialise the variable clock, stexposer, nodeID the state is exposed in the loop seen before.
};
