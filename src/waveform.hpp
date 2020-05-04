#ifndef _WAVEFORM_HPP
#define _WAVEFORM_HPP

#include <cmath>

enum class WaveType {
  WAVE_SINE,
  WAVE_SQUARE,
  WAVE_TRIANGLE,
  WAVE_SAW
};


class Waveform {

public:
  Waveform(float _freq, unsigned int _num_samples);
  virtual void generate(float * buffer) = 0;
  void setNormFreq(float _freq);
  void setNumSamples(unsigned int samples);

protected:
  float norm_freq;
  float phase = 0;
  unsigned int num_samples;

};

class SquareWave : public Waveform{

public:
  SquareWave(float _freq, unsigned int _num_samples): Waveform(_freq, _num_samples){}
  void generate(float * buffer);


};


class SineWave : public Waveform{

public:
  SineWave(float _freq, unsigned int _num_samples): Waveform(_freq, _num_samples){}
  void generate(float * buffer) override;
};

#endif
