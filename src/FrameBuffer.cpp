#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer(){

    for (std::size_t i = 0; i < frame_size; i ++){
        buffer[i] = 0;
    }
}

FrameBuffer& FrameBuffer::operator+=(const FrameBuffer& rhs){


    for (std::size_t i = 0; i < frame_size; i++){

        buffer[i] += rhs[i];
    }

    return *this;
}

const FrameBuffer FrameBuffer::operator+(const FrameBuffer& rhs){

    return FrameBuffer(*this) += rhs;
}
