#pragma once

#include <string>

namespace Virgin
{

#if defined(UNICODE) || defined(_UNICODE)
typedef ::std::wstring String;
#else
typedef ::std::string String;
#endif

}
