#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"
using namespace std;

// forward declarations to avoid include cycle
class Vehicle;

enum class TrafficLightPhase
{
    red = 0,
    green
};

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&message);

private:
    deque<T> _queue; //Store objects of TrafficLightPhases
    condition_variable cond;
    mutex mtx;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();

    // getters / setters

    // typical behaviour methods
    void waitForGreen();
    void simulate();
    TrafficLightPhase getCurrentPhase();

private:
    // typical private behaviour methods
    void cycleThroughPhases();

    // private member hold the current state of the ligth!
    TrafficLightPhase _currentPhase;
    MessageQueue<TrafficLightPhase> msgQueue;

    condition_variable _condition;
    mutex _mutex;
};

#endif