#include "FrameBuffer.hpp"
#include <cstring>

FrameBuffer::FrameBuffer(){

    buffer = new float[frame_size * num_channels];

    for (std::size_t i = 0; i < frame_size * num_channels; i++){
        buffer[i] = 0;
    }
}

FrameBuffer::FrameBuffer(const FrameBuffer& old){

	buffer = new float[frame_size * num_channels];

	std::memcpy(buffer, old.get(), frame_size * num_channels * sizeof(float));
}

FrameBuffer::~FrameBuffer(){

    delete[] buffer;
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

FrameBuffer& FrameBuffer::operator*=(float val){

    for (std::size_t i = 0; i < frame_size; i++){

        buffer[i] *= val;
    }

    return *this;
}

const FrameBuffer FrameBuffer::operator*(float val){

    return FrameBuffer(*this) *= val;
}
