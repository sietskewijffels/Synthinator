/*

    Top level class of a single audible note

    - Each note can have a number of oscillators.
    - Each note holds its own filter structure so that:
        - Different notes can have different filters apllied
        - Time based effects are easier to implement (e.g. ADSR filters)

*/
#ifndef _NOTE_HPP
#define _NOTE_HPP

#include <vector>

#include "oscillator.hpp"
#include "Filter.hpp"

class Note {

public:
    Note(const float _analog_freq, const unsigned int _sample_freq, const unsigned int buffer_size);

    void synthesize();
    void addHarmonic(const float _analog_freq);
    void addFilter();
    float getAnalogFreq(){return analog_freq;}

    float * buffer;
    unsigned int buffer_size;

    float norm_freq;
    float analog_freq;
    unsigned int sample_freq;
    WaveType base_type = WaveType::WAVE_SINE;

private:
    // Some datastrucure holding the filter chain
    std::vector<Filter> filter_chain;
    std::vector<Oscillator> oscillators;

    void normalize();
    float normalize(const float freq);

};

#endif
