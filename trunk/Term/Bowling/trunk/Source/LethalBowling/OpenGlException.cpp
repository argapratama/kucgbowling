#include "OpenGlException.h"

namespace Virgin
{

OpenGlException::OpenGlException(void)
{
}

OpenGlException::OpenGlException(const String& message)
    : Exception(message)
{
}


OpenGlException::~OpenGlException(void)
{
}

}
