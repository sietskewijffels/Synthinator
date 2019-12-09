#include "oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(float _analog_freq, int _sample_freq):
                              analog_freq(_analog_freq),
                              sample_freq(_sample_freq){

    normalize();

    //waveform = NULL;
}


Oscillator::Oscillator(float _analog_freq, int _sample_freq, WaveType _type):
                              analog_freq(_analog_freq),
                              sample_freq(_sample_freq),
                              type(_type){

  normalize();

  std::cout << "Normalized freq: " << norm_freq << std::endl;

  switch (_type){
    case WaveType::WAVE_SINE:
      waveform = new SineWave(norm_freq, 512);
      break;
    case WaveType::WAVE_SQUARE:
      waveform = new SquareWave(norm_freq, sizeof(buffer));
      break;
  }

}

void Oscillator::setAnalogFreq(float _freq){

    analog_freq = _freq;
    normalize();
    waveform->setNormFreq(norm_freq);
}

void Oscillator::setSampleFreq(int _sample_freq){

    sample_freq = _sample_freq;
    normalize();
    waveform->setNormFreq(norm_freq);
}



void Oscillator::normalize(){

  norm_freq = analog_freq / sample_freq;

}

void Oscillator::oscillate(){

  waveform->generate(buffer);

}
