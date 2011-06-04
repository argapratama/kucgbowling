#include "OpenGlException.h"

namespace OpenGl
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
