

#ifndef _NOTES_HPP
#define _NOTES_HPP




enum Note{
    NOTE_C4,
    NOTE_CS4,
    NOTE_D4,
    NOTE_DS4,
    NOTE_E4,
    NOTE_F4,
    NOTE_FS4,
    NOTE_G4,
    NOTE_GS4,
    NOTE_A4,
    NOTE_AS4,
    NOTE_B4,
    NOTE_C5,
    NOTE_CS5,
    NOTE_D5,
    NOTE_DS5,
    NOTE_E5
};


namespace Notes {


    float getFreq(Note note){

        switch (note){
        case NOTE_C4:    return 261.63;
        case NOTE_CS4:   return 277.18;
        case NOTE_D4:    return 293.66;
        case NOTE_DS4:   return 311.13;
        case NOTE_E4:    return 329.63;
        case NOTE_F4:    return 349.23;
        case NOTE_FS4:   return 369.99;
        case NOTE_G4:    return 392.00;
        case NOTE_GS4:   return 415.30;
        case NOTE_A4:    return 440.00;
        case NOTE_AS4:   return 466.16;
        case NOTE_B4:    return 493.88;
        case NOTE_C5:    return 523.25;
        case NOTE_CS5:   return 554.37;
        case NOTE_D5:    return 587.33;
        case NOTE_DS5:   return 622.25;
        case NOTE_E5:    return 659.26;

        }

        return 0;
    }


}

#endif
