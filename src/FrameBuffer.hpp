/*
    Heap Based Buffer datatype

    Initializes to 0
*/
#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <cstdint>

class FrameBuffer {

public:

    FrameBuffer();
	FrameBuffer(const FrameBuffer& old);
    ~FrameBuffer();
    float * get() {return buffer;};
	float * get() const {return buffer;};

    static const std::size_t frame_size = 512;
    static const std::size_t num_channels = 1;

    FrameBuffer& operator+=(const FrameBuffer& rhs);
    const FrameBuffer operator+(const FrameBuffer& rhs);

    FrameBuffer& operator*=(float val);
    const FrameBuffer operator*(float val);

    const float& operator[](const std::size_t index) const {return buffer[index];};
    float& operator[](const std::size_t index){return buffer[index];};


private:
    float * buffer;

};

#endif
