



#include "InputThread.hpp"


InputThread::InputThread(){

    // Startup the input thread
    std::cerr << "Started Input Thread" << std::endl;
    active = true;
    loop = std::thread(&InputThread::inputLoop, this);

}

InputThread::~InputThread(){

    active = false;
    loop.join();

}


void InputThread::inputLoop(){

    bool held = false;

    while (active){
        if (kbd.getKeyState(KEY_SPACE) && held == false){
            held = true;
            std::cerr << "SPACE PRESSED" << std::endl;
        } else if (kbd.getKeyState(KEY_SPACE) == 0 && held == true){
            held = false;
            std::cerr << "SPACE RELEASED" << std::endl;
        }
    }

}
