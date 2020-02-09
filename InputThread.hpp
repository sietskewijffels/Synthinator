/*

    Wrapper for the input thread

*/

#ifndef _INPUT_THREAD_HPP
#define _INPUT_THREAD_HPP

#include <thread>
#include "keyboard.hpp"

class InputThread{

public:
    InputThread();
    ~InputThread();

    void inputLoop();

private:
    std::thread loop;
    bool active;
    Keyboard kbd;


};

#endif
