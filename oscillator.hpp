/*
  Holds components for a VCO.

  oscillate() fills the buffer with samples

  Upon construction normalizes the analog frequency.
  From then only normalized frequency need be used.

  Buffer can be pre-allocated, or if NULL is passed it will allocate one.
*/

#ifndef _OSCILLATOR_HPP
#define _OSCILLATOR_HPP

#include <cstdlib>
#include "waveform.hpp"



class Oscillator {

public:

  Oscillator(float _analog_freq, int _sample_freq);
  Oscillator(float _analog_freq, int _sample_freq, float * _buffer);
  Oscillator(float _analog_freq, int _sample_freq, WaveType _type);
  Oscillator(float _analog_freq, int _sample_freq, float * buffer, WaveType _type);
public:
  Waveform * waveform;    // Waveform gen
  float norm_freq;        // Normalized frequency (cycles / sample)
  float * buffer;         // Sample Buffer

public:
  void oscillate();       // Do oscillate callback thingy

public:
  void setAnalogFreq(float _freq);
  void setSampleFreq(int _sample_freq);
  void setType(WaveType _type){ type = _type;}
  WaveType getType(){return type;}
  float getAnalogFreq(){return analog_freq;}

private:
  float analog_freq;    // Analog Frequency
  int sample_freq;      // Sample rate (samples / second)
  WaveType type;        // WaveType

private:
  void normalize();     // Calculate normalized freq


};


#endif
