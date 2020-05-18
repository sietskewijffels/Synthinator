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

Note::Note(const float _analog_freq, const unsigned int _sample_freq) :
    analog_freq(_analog_freq),
    sample_freq(_sample_freq)
{

    norm_freq = normalize(_analog_freq);
    // Add the base oscillator
    oscillators.emplace_back(norm_freq, WaveType::WAVE_SINE);

    std::cerr << "Gonna make them oscillators" << std::endl;
    // Add some harmonics for shits n giggles
    oscillators.emplace_back(norm_freq / 2, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq / 4, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq / 8, WaveType::WAVE_SINE);
    oscillators.emplace_back(norm_freq * 2, WaveType::WAVE_SINE);
    //oscillators.emplace_back(norm_freq * 4, WaveType::WAVE_SINE);
    std::cerr << "Made them oscillators" << std::endl;
    /*
        Initialize the base envelope and place at first position in chain
    */

    base_envelope = new EnvelopeFilter(5000, 500, 0.95, 6000);

    std::cerr << "Made new Note object!" << std::endl;

}


FrameBuffer& Note::synthesize(){



    if (base_envelope->envelope_phase != FINISHED){

        // Oscillate and sum all harmonics
        for (auto osc: oscillators){

            buffer += osc.oscillate() * (1 / oscillators.size());

        }

        // Run filters on final buffer
        for (auto filter: filter_chain){
            filter->doFilterings(buffer);
        }

        // Finally run base envelope
        base_envelope->doFilterings(buffer);
    } else {
        note_active = false;
    }

    return buffer;
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
