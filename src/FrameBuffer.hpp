/*
    Buffer datatype

    Initializes to 0
*/
#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <cstdint>

class FrameBuffer {

public:

    FrameBuffer();

    static const std::size_t frame_size = 512;
    static const std::size_t num_channels = 1;

    FrameBuffer& operator+=(const FrameBuffer& rhs);
    const FrameBuffer operator+(const FrameBuffer& rhs);
    const float& operator[](const std::size_t index) const {return buffer[index];};
    float& operator[](const std::size_t index){return buffer[index];};


private:
    float buffer[frame_size * num_channels];

};

#endif
