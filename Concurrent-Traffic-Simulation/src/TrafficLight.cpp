#include <iostream>
#include <random>
#include <cmath>
#include "TrafficLight.h"
#define SLEEP_FOR_DEFAULT 4
/* Implementation of class "MessageQueue" */


template <class T>
T MessageQueue<T>::receive()
{
  	std::unique_lock<std::mutex> uLock(_mutex);
  	_condition.wait(uLock, [this] { return !_queue.empty(); });
  	T msg = std::move(_queue.back());
  	_queue.pop_back();
  	return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
  	std::lock_guard<std::mutex> uLock(_mutex);
    _queue.push_back(std::move(msg));
  	_condition.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
	while(true) {
      if(_queue.receive() == TrafficLightPhase::green) {
        return;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
	threads.emplace_back(&TrafficLight::cycleThroughPhases, this);
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dist(4, 6);
  int interval = dist(mt);
  auto start = std::chrono::high_resolution_clock::now();
  
  while(true) {
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now()-start;
    if(elapsed.count() >= interval) {
      TrafficLightPhase newPhase = (_currentPhase == TrafficLightPhase::red)?TrafficLightPhase::green:TrafficLightPhase::red;
      _currentPhase = newPhase;
      // std::cout << "Traffic Light #:" << getID() << " turning " << newPhase << std::endl;
      _queue.send(std::move(newPhase));
      start = std::chrono::high_resolution_clock::now();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

