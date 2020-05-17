#include "FrameBuffer.hpp"

FrameBuffer& FrameBuffer::operator+=(const FrameBuffer& rhs){


    for (unsigned int i = 0; i < frame_size; i++){

        buffer[i] += rhs[i];
    }

    return *this;
}

const FrameBuffer FrameBuffer::operator+(const FrameBuffer& rhs){

    return FrameBuffer(*this) += rhs;
}
