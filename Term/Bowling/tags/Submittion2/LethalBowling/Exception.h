#pragma once

#include "TString.h"
#include "PrimitiveType.h"

namespace Virgin
{

class Exception
{
public:
    Exception();
    Exception(const String& message);
    virtual ~Exception();

    String Message() const;
    uint32 ErrorCode() const;

protected:
    uint32 errorCode_;
    String message_;
};

}
