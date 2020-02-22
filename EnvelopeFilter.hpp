/*

    Envelope filter class

    Runs ADSR filter over the buffer

*/

#ifndef _ENVELOPE_FILTER_HPP
#define _ENVELOPE_FILTER_HPP

#include "Filter.hpp"

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
    RELEASE
};

class EnvelopeFilter : public Filter {

public:
    EnvelopeFilter(float * buffer, std::size_t frame_length) : Filter(buffer, frame_length){}
    EnvelopeFilter(float * buffer, std::size_t frame_length, const int _attack, const int _decay, const float _sustain, const int _release)
        : Filter(buffer, frame_length),
        adsr({_attack, _decay, _sustain, _release}){}
    ~EnvelopeFilter();

    ADSR * getADSR() {return &adsr;}

    void doFilterings() override;

private:
    ADSR adsr;
    int phase = 0;
    State envelope_phase = ATTACK;

};


#endif
