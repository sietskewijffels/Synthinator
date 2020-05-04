#include "oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(const float _norm_freq):
    norm_freq(_norm_freq)
{


  buffer = (float*) malloc(sizeof(float) * 512);
}


Oscillator::Oscillator(const float _norm_freq, WaveType _type):
                              norm_freq(_norm_freq),
                              type(_type)
{



  switch (_type){
    case WaveType::WAVE_SINE:
      waveform = new SineWave(norm_freq, 512); //TODO: fix magic number
      break;
    case WaveType::WAVE_SQUARE:
      waveform = new SquareWave(norm_freq, sizeof(buffer));
      break;
  default:
      waveform = new SineWave(norm_freq, sizeof(buffer));
      break;

  }

  buffer = (float*) malloc(sizeof(float) * 512);

}

Oscillator::Oscillator(const float _norm_freq, float * _buffer, WaveType _type):
    norm_freq(_norm_freq),
    buffer(_buffer),
    type(_type)


{


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

Oscillator::Oscillator(const float _norm_freq, float * _buffer):
    norm_freq(_norm_freq),
    buffer(_buffer)


{
}

void Oscillator::oscillate(){

  waveform->generate(buffer);

}
