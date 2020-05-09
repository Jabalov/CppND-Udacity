#include <iostream>
#include <random>
#include "TrafficLight.h"

using namespace std;
/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // perform queue modification under the lock
    unique_lock<mutex> uLock(mtx);
    cond.wait(uLock, [this] { return !_queue.empty(); });

    T msg = move(_queue.back());
    _queue.pop_back();

    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    lock_guard<mutex> uLock(mtx);

    _queue.push_back(move(msg));

    cond.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight() { _currentPhase = TrafficLightPhase::red; }

TrafficLight::~TrafficLight() {}

void TrafficLight::waitForGreen()
{
    while (true)
    {
        TrafficLightPhase phase = msgQueue.receive();
        if (phase == TrafficLightPhase::green)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase() { return _currentPhase; }

void TrafficLight::simulate() { threads.emplace_back(thread(&TrafficLight::cycleThroughPhases, this)); }

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds((rand() % 5000) + 3000));

        if (_currentPhase == TrafficLightPhase::red)
            _currentPhase = TrafficLightPhase::green;

        else
            _currentPhase = TrafficLightPhase::red;

        msgQueue.send(move(_currentPhase));
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}
