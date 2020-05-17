#include "EventQueue.hpp"
#include <iostream>


void EventQueue::append(float freq, Event_type type){

    Event event = {type, freq, 1};

    queue_mutex.lock();
    queue.push(event);
    queue_mutex.unlock();


}
