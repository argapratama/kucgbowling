#pragma once

#include "Box.h"
#include "Vector.h"
#include "Sphere.h"

namespace Virgin
{

// The box is treated as a solid.  The extents must be positive; that is, no
// flat boxes are allowed.  The FindIntersection query returns 0 or 1 point.
// An initially intersecting box and sphere returns 'false'.  (The set of
// intersection can be quite complicated in this configuration.)

// box and sphere are stationary
bool TestIntersection (const Box& rkBox,
    const Sphere& rkSphere);

// box and sphere are moving
bool FindIntersection (const Box& rkBox,
    const Vector3& rkBoxVelocity, const Sphere& rkSphere,
    const Vector3& rkSphVelocity, float& rfTFirst, float fTMax,
    int& riQuantity, Vector3& rkP);


}
