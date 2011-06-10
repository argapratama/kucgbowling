#pragma once
#include "exception.h"

namespace OpenGl
{
using namespace Virgin;

class OpenGlException : public Exception::Exception
{
public:
    OpenGlException(void);
    OpenGlException(const String& message);

    virtual ~OpenGlException(void);
};

}
