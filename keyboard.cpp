
#include "keyboard.hpp"
#include "Notes.hpp"

Keyboard::Keyboard(EventQueue * _queue): queue(_queue){

    active = false;

    keyboard_ev = new input_event();
    keyboard_st = new keyboard_state();

    keyboard_fd = 0;
    keyboard_fd = open(KEYBOARD_DEV, O_RDONLY);

    if (keyboard_fd > 0){

        ioctl(keyboard_fd, EVIOCGNAME(256), name);
        std::cerr << "Keyboard Device: " << name << std::endl;

        active = true;
        loop = std::thread(&Keyboard::keyboardLoop, this);
    }

}

Keyboard::~Keyboard(){

    if (keyboard_fd > 0){

        active = false;
        loop.join();
        close(keyboard_fd);
    }

    delete keyboard_ev;
    delete keyboard_st;
    keyboard_fd = 0;
}

static float getNote(int key_code){

    switch (key_code){
    case KEY_Z: return Notes::getFreq(NOTE_C);
    case KEY_S: return Notes::getFreq(NOTE_CS);
    case KEY_X: return Notes::getFreq(NOTE_D);
    case KEY_D: return Notes::getFreq(NOTE_DS);
    case KEY_C: return Notes::getFreq(NOTE_E);
    case KEY_V: return Notes::getFreq(NOTE_F);
    case KEY_G: return Notes::getFreq(NOTE_FS);
    case KEY_B: return Notes::getFreq(NOTE_G);
    case KEY_H: return Notes::getFreq(NOTE_GS);
    case KEY_N: return Notes::getFreq(NOTE_A);
    case KEY_J: return Notes::getFreq(NOTE_AS);
    case KEY_M: return Notes::getFreq(NOTE_B);
    case KEY_COMMA: return 2*Notes::getFreq(NOTE_C);
    }

    return 0;
}


void Keyboard::keyboardLoop(){

    while (active){

        int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));

        if (bytes > 0){

            if (keyboard_ev->type & EV_KEY){

                if (keyboard_st->keys[keyboard_ev->code] != keyboard_ev->value && keyboard_ev->value != 2){
                    keyboard_st->keys[keyboard_ev->code] = keyboard_ev->value;

                    float freq = getNote(keyboard_ev->code);
                    Event_type type;

                    switch(keyboard_ev->value){
                    case 0: type = NOTE_OFF; break;
                    case 1: type = NOTE_ON; break;
                    }

                    queue->append(freq, type);
                }
            }

        }
    }

}

short Keyboard::getKeyState(short key){

    return keyboard_st->keys[key];
}
