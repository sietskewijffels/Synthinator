#include "EnvelopeFilter.hpp"
//#include <iostream>

FrameBuffer& EnvelopeFilter::doFilterings(FrameBuffer& buffer){

    float y = 0;

    for (unsigned int n = 0; n < FrameBuffer::frame_size; n++){

        switch (envelope_phase){
        case(ATTACK):

            y = (1 / (float) adsr.attack) * phase;
            //std::cerr << "A @ " << phase << " : " << y << std::endl;
            if (phase >= adsr.attack) {envelope_phase = DECAY; phase = 0;}
            break;

        case(DECAY):

            y = -((1 - adsr.sustain)  / (float) adsr.decay) * phase + 1;
            //y = 1;
            //std::cerr << "D @ " << phase << " : " << y << std::endl;
            if (phase > adsr.decay) envelope_phase = SUSTAIN;
            break;

        case(SUSTAIN):

            phase = 0;
            // std::cerr << "S" << std::endl;
            y = adsr.sustain;
            break;

        case(RELEASE):
            y = -(adsr.sustain / (float)adsr.release) * phase + adsr.sustain;
            if (y <= 0){
                y = 0;
                envelope_phase = FINISHED;
            }
            //std::cerr << "Release " << y << std::endl;
            break;
        case(FINISHED):
            y = 0;
            break;
        }

        buffer[n] = buffer[n] * y;
        phase++;
    }

    return buffer;
}
