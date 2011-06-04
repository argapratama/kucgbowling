#include "Drawer.h"
#include <gl/GL.h>

namespace Virgin
{

Drawer::Drawer(void)
    : translateX_(0.0)
    , translateY_(0.0)
    , translateZ_(0.0)
{
}


Drawer::~Drawer(void)
{
}

void Drawer::TranslateTo(float x, float y, float z)
{
    translateX_ = x;
    translateY_ = y;
    translateZ_ = z;
}

void Drawer::TranslateMore(float x, float y, float z)
{
    TranslateTo(translateX_ + x, translateY_ + y, translateZ_ + z);
}

}
