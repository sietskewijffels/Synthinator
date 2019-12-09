#include "waveform.hpp"
#include <iostream>






Waveform::Waveform(float _freq, unsigned int _num_samples):
                        norm_freq(_freq), num_samples(_num_samples){

    //std::cout << "Wollah Waveform" << std::endl;

}

void Waveform::setNormFreq(float _freq){norm_freq = _freq;}

void Waveform::setNumSamples(unsigned int samples){num_samples = samples;}



void SineWave::generate(float * buffer){

  int n;
  for (n = 0; n < num_samples; n++){

    float sample = std::sin(3.14151598 * 2 * norm_freq * n + phase);

    buffer[n] = sample;
    //buffer[2 * n + 1] = sample;

  }

  phase = 3.141598 * 2 *norm_freq * n + phase;


}


void SquareWave::generate(float * buffer){

  for (int i = 0; i < sizeof(buffer); i++)
    buffer[i] = 0;
}
