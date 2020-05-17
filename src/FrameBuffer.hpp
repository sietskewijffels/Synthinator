/*
    Buffer datatype
*/
#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <cstdint>

class FrameBuffer {

public:

    static const unsigned int frame_size = 512;
    static const unsigned int num_channels = 1;

    FrameBuffer& operator+=(const FrameBuffer& rhs);
    const FrameBuffer operator+(const FrameBuffer& rhs);
    const float& operator[](const std::size_t index) const {return buffer[index];};
    float& operator[](const std::size_t index){return buffer[index];};


private:
    float buffer[frame_size * num_channels];

};

#endif
