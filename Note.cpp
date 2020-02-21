#include "Note.hpp"

void Note::normalize(){

    norm_freq = analog_freq / sample_freq;

}

float Note::normalize(const float freq){

    return freq / sample_freq;

}

Note::Note(const float _analog_freq, const unsigned int _sample_freq, const unsigned int _buffer_size) :
    buffer_size(_buffer_size),
    analog_freq(_analog_freq),
    sample_freq(_sample_freq)
{

    // Create buffer
    buffer = (float *) malloc(sizeof(float) * _buffer_size);

    norm_freq = normalize(_analog_freq);
    // Add the base oscillator
    oscillators.emplace_back(norm_freq, WaveType::WAVE_SINE);

}


void Note::synthesize(){

    // Reset buffer
    for (unsigned int n = 0; n < buffer_size; n++){
        buffer[n] = 0;
    }

    // Oscillate and sum all harmonics
    for (auto osc: oscillators){

        osc.oscillate();

        for (unsigned int n = 0; n < buffer_size; n++){

            buffer[n] += osc.buffer[n] / oscillators.size();

        }
    }

    // Run filters on final buffer
}

void Note::addHarmonic(const float freq){

    oscillators.emplace_back(normalize(freq), WaveType::WAVE_SINE);

}

void Note::addFilter(){

}
