/*

    Base class for filters

    Filter object will doFilterings on the buffer

*/

#ifndef _FILTER_HPP
#define _FILTER_HPP

#include <cstdlib>

class Filter {

public:
    Filter(float * _buffer, std::size_t _frame_length) :
        buffer(_buffer), frame_length(_frame_length){}

    virtual ~Filter();
    virtual void doFilterings();

    float * buffer;
    std::size_t frame_length;
};

#endif
