#include "Exception.h"
#include <Windows.h>

namespace Exception
{
Exception::Exception()
    : errorCode_(GetLastError())
{
}

Exception::Exception(const String& message)
    : errorCode_(GetLastError())
    , message_(message)
{
}

Exception::~Exception()
{
}

String Exception::Message() const
{
    return message_;
}

uint32 Exception::ErrorCode() const
{
    return errorCode_;
}

}
