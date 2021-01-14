#ifndef STATEEXPOSER_H
#define STATEEXPOSER_H
#include "state.h"
#include "lamport_clock.h"
#include "Networking.h"

class stateExposer //: public Subject
{
    public:
        State state;
        getInstance();
        expose();  //send the state with the given nodeID and the value of the clock

        exposeInfinite(); // expose indefinitely

        exposeWithinAPeriod(long period); // expose within that period of time

        static void exposeLimit(); // method to verify and control that the limits are not exceeded

        const int D = 1; // const minimal delay for the infiniteExpose method
        void verifyTimeAndVolume(); // to verify that the delay between two expose dont exceed 1second and the volume 500bytes

    private:
        const int limNumTuple = 500; // limit number of bytes to expose
        const LamportTime limTimeTuple = 500; // limit number of time in ms to expose
        bool flag = true;
        stateExposer();
        long nodeID ;
        stateExposer stexposer;
        LamportClock clock;

};

#endif // STATEEXPOSER_H


// We set the classes of observables and sucribers
    /*

    class Subject
    {
    public:
         virtual ~Subject() = default;
         void Attach(Observer& o) { observers.push_back(&o); }
         void Detach(Observer& o)
         {
             observers.erase(std::remove(observers.begin(), observers.end(), &o));
         }
         void Notify()
         {
             for (auto* o : observers) {
                 o->Update(*this);
             }
         }
    private:
         std::vector<Observer*> observers;
    };

    */
