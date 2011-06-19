#pragma once

#include "Box.h"

namespace Virgin
{


// boxes are stationary

bool TestIntersection (const Box& rkBox0,
    const Box& rkBox1);

// boxes have constant linear velocity

bool TestIntersection (float fTime, const Box& rkBox0,
    const Vector3& rkVel0, const Box& rkBox1,
    const Vector3& rkVel1);

// boxes have constant linear velocities and angular velocities

bool TestIntersection (float fTime, int iNumSteps,
    const Box& rkBox0,  const Vector3& rkVel0,
    const Vector3& rkRotCen0, const Vector3& rkRotAxis0,
    const Box& rkBox1, const Vector3& rkVel1,
    const Vector3& rkRotCen1, const Vector3& rkRotAxis1);

// boxes are have constant linear velocities

bool FindIntersection (const Box& rkBox0,
    const Vector3& rkVel0, const Box& rkBox1,
    const Vector3& rkVel1, float& rfTFirst, float fTMax, int& riQuantity,
    Vector3* akP);

}
