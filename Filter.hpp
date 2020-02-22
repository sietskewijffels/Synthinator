/*

    Base class for filters

    Filter object will doFilterings on the buffer

*/

#ifndef _FILTER_HPP
#define _FILTER_HPP

#include <cstdlib>

class Filter {

public:
    Filter(float * _buffer, std::size_t _frame_length);

    virtual void doFilterings() = 0;

    float * buffer;
    std::size_t frame_length;
};

#endif
