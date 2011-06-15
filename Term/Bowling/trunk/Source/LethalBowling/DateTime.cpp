#include "DateTime.h"
#include <Mmsystem.h>

// timeGetTime() 함수는 Winmm.lib, Winmm.dll 사용함

namespace Virgin
{
DateTime::DateTime(uint32 ms)
    : timeMs_(ms)
{
}

DateTime DateTime::SinceSystemStarted()
{
    return DateTime(timeGetTime());
}

TimeSpan DateTime::operator-(const DateTime& rhs) const
{
    return TimeSpan(this->timeMs_ - rhs.timeMs_);
}

DateTime DateTime::operator+=(const uint32 timeMs)
{
    timeMs_ += timeMs;
    return *this;
}

}
