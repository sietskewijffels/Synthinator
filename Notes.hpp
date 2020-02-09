

#ifndef _NOTES_HPP
#define _NOTES_HPP




enum Note{
    NOTE_C,
    NOTE_CS,
    NOTE_D,
    NOTE_DS,
    NOTE_E,
    NOTE_F,
    NOTE_FS,
    NOTE_G,
    NOTE_GS,
    NOTE_A,
    NOTE_AS,
    NOTE_B,
};


namespace Notes {


    float getFreq(Note note){

        switch (note){
        case NOTE_C:    return 261.63;
        case NOTE_CS:   return 277.18;
        case NOTE_D:    return 293.66;
        case NOTE_DS:   return 311.13;
        case NOTE_E:    return 329.63;
        case NOTE_F:    return 349.23;
        case NOTE_FS:   return 369.99;
        case NOTE_G:    return 392.00;
        case NOTE_GS:   return 415.30;
        case NOTE_A:    return 440.00;
        case NOTE_AS:   return 466.16;
        case NOTE_B:    return 493.88;

        }

        return 0;
    }


}

#endif
