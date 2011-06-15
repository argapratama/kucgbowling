#pragma once

#include "Sprite.h"
#include "Sphere.h"
#include "Box.h"

namespace Virgin
{

class Pin : public Sprite
{
public:
    Sphere& CoveringSphere();
    Box& BoundingBox();

private:
    Sphere coverSphere_;
    Box box_;
};

}


