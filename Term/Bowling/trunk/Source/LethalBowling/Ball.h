#pragma once

#include "Sprite.h"
#include "Sphere.h"

namespace Virgin
{

class Ball : public Sprite
{
public:
    Sphere& CoveringSphere() { return sphere_; }

private:
    Sphere sphere_;
};

}
