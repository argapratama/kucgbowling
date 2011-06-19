#pragma once
#include "exception.h"

namespace Virgin
{

class OpenGlException : public Exception
{
public:
    OpenGlException(void);
    OpenGlException(const String& message);

    virtual ~OpenGlException(void);
};

}
