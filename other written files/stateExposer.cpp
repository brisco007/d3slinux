#include "stateExposer.h"
#include <sys/types.h>
#include <chrono>
#include <thread>
// #include <iostream>
// #include <vector>

stateExposer::stateExposer()
{

    this->nodeID = static_cast<long>(getpid());
    this->state.nodeID = static_cast<long>(getpid());

}

    stateExposer getInstance(){
        if(stexposer= nullptr)
            this.stexposer=stateExposer();
        return stexposer;

    }

     void expose(){
        this.state.timestamp = clock.get_time();
        Networking.sendMessage(string addressReceiver,this.nodeID, this.state); // NodeID is there as the ID of the sender ,we suppose that in case of any error its handled inside the method
        this.state.timestamp = this.clock.send_event();

    }


    void exposeInfinite(){
        this.flag = false;// it helps to do that exposeLimit() does nothing when this method is in execution
        int i;
        int count = 1;
        for(true) // the function will loop and never stop
        {
            this.state.timestamp = this.clock.get_time();
            Networking.sendMessage(string addressReceiver,this.nodeID, this.state); // NodeID is there as the ID of the sender ,we suppose that in case of any error its handled inside the method
            this.state.timestamp = this.clock.send_event();

            std::this_thread::sleep_for(std::chrono::milliseconds(this.D)); // provide a delay of D milli-seconds

            // print
            cout << "the fonction looped: " << count << endl;
            count++
        }

    }

    void exposeWithinAPeriod(long period){
        this.flag = false;// it helps to do that exposeLimit() does nothing when this method is in execution
        int count = 1;
        while(count < period ) // the time here is in milli-second
        {
            // faudra qu on definisse bien comment charger les listes de tuples
            this.state.timestamp = this.clock.get_time();
            Networking.sendMessage(string addressReceiver,this.nodeID, this.state); // NodeID is there as the ID of the sender ,we suppose that in case of any error its handled inside the method
            this.state.li
            this.state.timestamp = this.clock.send_event();

            std::this_thread::sleep_for(std::chrono::milliseconds(this.D)); // provide a delay of D milli-seconds

            // print
            cout << "the fonction looped: " << count << endl;
            count++;
        }
        this.flag = true;// it helps to do that exposeLimit() does nothing when this method is in execution
    }

    static void exposeLimit(){  // method to verify and control that the limits are not exceeded

        auto start = std::chrono::high_resolution_clock::now(); // we set elements to estimate execution times
        auto finish = std::chrono::high_resolution_clock::now();

        for(true){  // the following intructions will be executed indefinitely



            start = std::chrono::high_resolution_clock::now();

            while( this.limNumTuple < 10*this.state.list_of_tuples.size() || std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() < this.limTimeTuple ){
                    if ( this.flag){  // we calculate the size of the list of tuples on the precedent line and 10 is the global size of a tuple also, we verify that the delay is less than the limTimeTuple
                        expose();
                        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // we can do without this
                    }

                    auto finish = std::chrono::high_resolution_clock::now(); // we mesure the time to see if the

            }
        }

    }


    // We set the classes of observables and sucribers


   /*


    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void Update(Subject&) = 0;
    };


    class ObserveState: public Observer
    {
    public:
         explicit ObserveState(stateExposer& s) : subject(s) { subject.Attach(*this); }
         ~ObserveState() { subject.Detach(*this); }
         void Update(Subject& theChangedSubject) override
         {



            if (&theChangedSubject == &subject)
                 flag= false;
                 //VerifyExpose();
         }

         void VerifyExpose()
         {

         }

    private:
         stateExposer& subject; // on declare le pointeur sur le sujet
    };



class stateExposer
{
    public:
        State state;
        getInstance();
        expose();  //send the state with the given nodeID and the value of th clock

        exposeInfinite(); // expose indefinitely

        exposeWithinAPeriod(long period); // expose within that period of time


    private:
        const int limNumTuple = 500; // limit number of bytes to expose
        const int limTimeTuple = 500; // limit number of time to expose
        stateExposer();
        long nodeID = ;
        stateExposer stexposer;
        LamportClock clock;

};

    */
