#pragma once

#include "PrimitiveType.h"
#include "TimeSpan.h"

namespace Virgin
{

class DateTime
{
public:
    DateTime(uint32 ms);

    //static DateTime Now();
    static DateTime SinceSystemStarted();

    TimeSpan operator-(const DateTime& rhs) const;
    DateTime operator+=(const uint32 timeMs);

private:
    uint32 timeMs_;
};

}
