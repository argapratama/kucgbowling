#pragma once

#include "Vector.h"

namespace Virgin
{
 
class Sphere
{
public:
    Sphere ();

    Vector3& Center ();
    const Vector3& Center () const;

    float& Radius ();
    const float& Radius () const;

protected:
    Vector3 m_kCenter;
    float m_fRadius;
};

}

