#ifndef _WAVEFORM_HPP
#define _WAVEFORM_HPP

#include <cmath>
#include "FrameBuffer.hpp"

enum class WaveType {
  WAVE_SINE,
  WAVE_SQUARE,
  WAVE_TRIANGLE,
  WAVE_SAW
};


class Waveform {

public:
  Waveform(float _freq);
  virtual ~Waveform() = 0;
  virtual FrameBuffer& generate();
  FrameBuffer buffer;

protected:
  float norm_freq;
  float phase = 0;

};

class SquareWave : public Waveform{

public:
  SquareWave(float _freq): Waveform(_freq){}
  FrameBuffer& generate() override;


};


class SineWave : public Waveform{

public:
  SineWave(float _freq): Waveform(_freq){}
  FrameBuffer& generate() override;
};

#endif
