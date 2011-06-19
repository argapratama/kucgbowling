#pragma once

#include "Sprite.h"
#include "Sphere.h"

namespace Virgin
{

class Ball : public Sprite
{
public:
    Sphere& CoveringSphere();

private:
    Sphere sphere_;
};

}
