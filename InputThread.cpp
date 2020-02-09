



#include "InputThread.hpp"


InputThread::InputThread(EventQueue * _input_queue): input_events(_input_queue){

    // Startup the input thread
    //input_events = new EventQueue();
    kbd = new Keyboard(input_events);

    std::cerr << "Started Input Thread" << std::endl;

}

InputThread::~InputThread(){

    delete kbd;

}
