/*

    Wrapper class for event queue handling

*/

#ifndef _EVENTQUEUE_HPP
#define _EVENTQUEUE_HPP

#include <vector>
#include <mutex>
#include <queue>

enum Event_type{
        NOTE_OFF,
        NOTE_ON
};

typedef struct {

    Event_type type;
    float freq;
    int velocity;

} Event;

class EventQueue {

public:
    void handleNext(); // Handle the next event and pop
    void append(float freq, Event_type type);
    //std::vector<Event> queue;
    std::queue<Event> queue;
    std::mutex queue_mutex;

};


#endif
