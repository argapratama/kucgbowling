#include "TimeSpan.h"

namespace Virgin
{
TimeSpan::TimeSpan(uint32 ms)
    : timeMs_(ms)
{
}

double TimeSpan::TotalSeconds() const
{
    return TotalMilliseconds() / 1000.0;
}

double TimeSpan::TotalMilliseconds() const
{
    return static_cast<double>(timeMs_);
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& rhs)
{
    this->timeMs_ += rhs.timeMs_;
    return *this;
}

}