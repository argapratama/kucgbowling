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
    Vector3* GetBox();

    //virtual void Update(TimeSpan time, TimeSpan timeDelta);
    void GetBox(Vector3 box[8]);

private:
    Sphere coverSphere_;
    Vector3 box_[BoxVerticeCount];
};

}


