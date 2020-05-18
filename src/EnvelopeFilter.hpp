/*

    Envelope filter class

    Runs ADSR filter over the buffer

*/

#ifndef _ENVELOPE_FILTER_HPP
#define _ENVELOPE_FILTER_HPP

#include "Filter.hpp"
#include "FrameBuffer.hpp"

typedef struct {

    // Attack decay and release times are in number of samples
    int attack;
    int decay;
    float sustain;
    int release;

} ADSR;

enum State {
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE,
    FINISHED
};

class EnvelopeFilter : public Filter {

public:
    EnvelopeFilter(const int _attack, const int _decay, const float _sustain, const int _release)
        : adsr({_attack, _decay, _sustain, _release}){};


    FrameBuffer& doFilterings(FrameBuffer& buffer) override;
    State envelope_phase = ATTACK;

private:
    ADSR adsr;
    int phase = 0;

};


#endif
