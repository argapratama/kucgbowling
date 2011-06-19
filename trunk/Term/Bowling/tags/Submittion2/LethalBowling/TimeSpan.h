#pragma once

#include "PrimitiveType.h"

namespace Virgin
{

class TimeSpan
{
public:
    explicit TimeSpan(uint32 ms);

    double TotalSeconds() const;
    double TotalMilliseconds() const;

    TimeSpan& operator+=(const TimeSpan& rhs);

private:
    uint32 timeMs_;
};

}