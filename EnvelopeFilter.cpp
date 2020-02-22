#include "EnvelopeFilter.hpp"

void EnvelopeFilter::doFilterings(){

    float y = 0;

    for (unsigned int n; n < frame_length; n++){

        switch (envelope_phase){
        case(ATTACK):

            y = (1 / adsr.attack) * phase;
            if (phase >= adsr.attack) {envelope_phase = DECAY; phase = 0;}
            break;

        case(DECAY):

            y = 1 - adsr.sustain - (1 / adsr.decay) * phase;
            if (phase > adsr.decay) envelope_phase = SUSTAIN;
            break;

        case(SUSTAIN):

            phase = 0;
            y = adsr.sustain;
            break;

        case(RELEASE):
            y = adsr.sustain - (adsr.release * phase);
            break;
        }

        buffer[n] = buffer[n] * y;
        phase++;
    }

}
