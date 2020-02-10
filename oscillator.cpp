#include "oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(float _analog_freq, int _sample_freq):
                              analog_freq(_analog_freq),
                              sample_freq(_sample_freq)
{

    normalize();

    //waveform = NULL;
}


Oscillator::Oscillator(float _analog_freq, int _sample_freq, WaveType _type):
                              analog_freq(_analog_freq),
                              sample_freq(_sample_freq),
                              type(_type)
{

  normalize();

  
  switch (_type){
    case WaveType::WAVE_SINE:
      waveform = new SineWave(norm_freq, 512);
      break;
    case WaveType::WAVE_SQUARE:
      waveform = new SquareWave(norm_freq, sizeof(buffer));
      break;
  default:
      waveform = new SineWave(norm_freq, sizeof(buffer));
      break;

  }

}

Oscillator::Oscillator(float _analog_freq, int _sample_freq, float * _buffer, WaveType _type):
    analog_freq(_analog_freq),
    sample_freq(_sample_freq),
    type(_type),
    buffer(_buffer)

{

    normalize();

    switch (_type){
    case WaveType::WAVE_SINE:
        waveform = new SineWave(norm_freq, sizeof(buffer));
        break;
    case WaveType::WAVE_SQUARE:
        waveform = new SquareWave(norm_freq, sizeof(buffer));
        break;
    default:
        waveform = new SineWave(norm_freq, sizeof(buffer));
        break;

    }
}

Oscillator::Oscillator(float _analog_freq, int _sample_freq, float * _buffer):
    analog_freq(_analog_freq),
    sample_freq(_sample_freq),
    buffer(_buffer)

{
    normalize();
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
