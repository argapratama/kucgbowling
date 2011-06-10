#include "Color.h"

namespace Virgin
{

Color::Color()
    : R(0.0)
    , G(0.0)
    , B(0.0)
    , A(0.0)
{
}

Color::Color(float r, float g, float b, float a)
    : R(r)
    , G(g)
    , B(b)
    , A(a)
{
}

Color::~Color()
{
}

}
