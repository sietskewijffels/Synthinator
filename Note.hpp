/*

    Top level class of a single audible note

*/
#ifndef _NOTE_HPP
#define _NOTE_HPP

#include <vector>

#include "oscillator.hpp"

class Note {

public:
    Note(const float _analog_freq, const int _sample_freq, const unsigned int buffer_size);

    void synthesize();
    void addHarmonic(const float _analog_freq);
    void addFilter();

    float * buffer;
    unsigned int buffer_size;

private:
    float norm_freq;
    float analog_freq;
    WaveType base_type = WaveType::WAVE_SINE;

    // Some datastrucure holding the filter chain

    std::vector<Oscillator> oscillators;

};

#endif
