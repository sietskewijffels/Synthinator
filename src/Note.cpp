#include "Note.hpp"
#include "EnvelopeFilter.hpp"
#include "Filter.hpp"
#include <iostream>

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

    // Add some harmonics for shits n giggles
    oscillators.emplace_back(norm_freq / 2, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq / 4, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq / 8, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq * 2, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq * 4, WaveType::WAVE_SINE);

    /*
        Initialize the base envelope and place at first position in chain
    */

    base_envelope = new EnvelopeFilter(buffer, 512, 5000, 500, 0.95, 6000);

}


void Note::synthesize(){

    // Reset buffer
    for (unsigned int n = 0; n < buffer_size; n++){
        buffer[n] = 0;
    }

    if (base_envelope->envelope_phase != FINISHED){

        // Oscillate and sum all harmonics
        for (auto osc: oscillators){

            osc.oscillate();

            for (unsigned int n = 0; n < buffer_size; n++){

                buffer[n] += osc.buffer[n] / oscillators.size();

            }
        }

        // Run filters on final buffer
        for (auto filter: filter_chain){
            filter->doFilterings();
        }

        // Finally run base envelope
        base_envelope->doFilterings();
    } else {
        note_active = false;
    }
}

void Note::signalOff(){

    // Signal the base envelope to release
    base_envelope->envelope_phase = RELEASE;
    envelope_phase = RELEASE;


}

void Note::addHarmonic(const float freq){

    oscillators.emplace_back(normalize(freq), WaveType::WAVE_SINE);

}

void Note::addFilter(){

}