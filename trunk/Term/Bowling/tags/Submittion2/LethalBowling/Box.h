#pragma once

#include "Vector.h"

namespace Virgin
{

class Box
{
public:
    Box ();

    Vector3& Center ();
    const Vector3& Center () const;

    Vector3& Axis (int i);
    const Vector3& Axis (int i) const;
    Vector3* Axes ();
    const Vector3* Axes () const;

    float& Extent (int i);
    const float& Extent (int i) const;
    float* Extents ();
    const float* Extents () const;

    void ComputeVertices (Vector3 akVertex[8]) const;

protected:
    Vector3 m_kCenter;
    Vector3 m_akAxis[3];
    float m_afExtent[3];
};

}