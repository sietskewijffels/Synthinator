/*

    Base class for filters

    Filter object will doFilterings on the buffer

*/

#ifndef _FILTER_HPP
#define _FILTER_HPP

class Filter {

public:
    Filter(float * _buffer) : buffer(_buffer){}
    virtual ~Filter();
    virtual void doFilterings();

    float * buffer;
};

#endif
