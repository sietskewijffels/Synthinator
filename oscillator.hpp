/*
  Holds components for a VCO.

  oscillate() fills the buffer with samples

  Buffer can be pre-allocated, or if NULL is passed it will allocate one.
*/

#ifndef _OSCILLATOR_HPP
#define _OSCILLATOR_HPP

#include <cstdlib>
#include "waveform.hpp"



class Oscillator {

public:

  Oscillator(const float norm_freq);
  Oscillator(const float norm_freq, float * _buffer);
  Oscillator(const float norm_freq, WaveType _type);
  Oscillator(const float norm_freq, float * buffer, WaveType _type);
public:
  Waveform * waveform;    // Waveform gen
  float norm_freq;        // Normalized frequency (cycles / sample)
  float * buffer;         // Sample Buffer

public:
  void oscillate();       // Do oscillate callback thingy

public:
  void setType(WaveType _type){ type = _type;}
  WaveType getType(){return type;}

private:
  WaveType type;        // WaveType

private:
  void normalize();     // Calculate normalized freq


};


#endif
