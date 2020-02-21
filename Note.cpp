#include "Note.hpp"


Note::Note(const float _analog_freq, const int _sample_freq, const unsigned int _buffer_size) :
    buffer_size(_buffer_size),
    analog_freq(_analog_freq)
{


    // Add the base oscillator
    oscillators.emplace_back(_analog_freq, sample_freq, WaveType::WAVE_SINE);

}


void Note::synthesize(){

    // Oscillate and sum all harmonics
    for (auto osc: oscillators){

        osc.oscillate();

        for (unsigned int n = 0; n < buffer_size; n++){

            buffer[n] += osc.buffer[n];

        }
    }

    // Run filters on final buffer
}

void Note::addHarmonic(const float analog_freq){


}

void Note::addFilter(){
    
}
