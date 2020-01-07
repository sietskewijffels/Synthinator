
#include "keyboard.hpp"


Keyboard::Keyboard(){

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

void Keyboard::keyboardLoop(){

    while (active){

        int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));

        if (bytes > 0){

            if (keyboard_ev->type & EV_KEY){

                keyboard_st->keys[keyboard_ev->code] = keyboard_ev->value;
            }

        }
    }

}

short Keyboard::getKeyState(short key){

    return keyboard_st->keys[key];
}
