#include <iostream>
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <string>
#include <array>

#include "oscillator.hpp"
#include "InputThread.hpp"
#include "keyboard.hpp"
#include "EventQueue.hpp"
#include "AudioThread.hpp"


int main (int argc, char *argv[]){
    
    // TODO: make log file instead of stderr
    std::cerr << "Yo Whaddup!" << std::endl;

    EventQueue event_queue;

    InputThread input_thread(&event_queue);
    AudioThread audio_thread(&event_queue);

    return 0;
}
