#pragma once

#include "Sprite.h"
#include "Sphere.h"
#include "Box.h"

namespace Virgin
{

enum 
{
    BoxVerticeCount = 8
};

class Pin : public Sprite
{
public:
    Sphere& CoveringSphere();

    //virtual void Update(TimeSpan time, TimeSpan timeDelta);
    void GetBox(Box& boxOut);
    void GetBox(Vector3 box[8]);
    Vector3* GetBox();

private:
    Sphere coverSphere_;
    Vector3 box_[BoxVerticeCount];
};

}


