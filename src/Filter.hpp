/*

    Base class for filters

    Filter object will doFilterings on the buffer

*/

#ifndef _FILTER_HPP
#define _FILTER_HPP

#include "FrameBuffer.hpp"

class Filter {

public:

    virtual FrameBuffer& doFilterings(FrameBuffer& buffer) = 0;
};

#endif
