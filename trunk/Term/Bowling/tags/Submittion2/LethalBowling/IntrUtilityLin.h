#pragma once

#include "Vector.h"
#include "IntrUtility.h"

namespace Virgin
{

void LineProjection (const Vector3& rkD,
    const Vector3 akV[2], float& rfMin, float& rfMax);


void GetLineConfiguration (const Vector3& rkAxis, 
    const Vector3 akU[2], ContactConfig& rkConfig);

// This is the case for a static/dynamic contact set (currently touching and
// colinear).

void FindContactSetColinearLines (const Vector3 akU[2],
    const Vector3 akV[2], int& riQuantity, Vector3* akP);

// This is the case for a static/dynamic contact set (currently touching and
// non-colinear).
//   kNormU is the normal of U in the plane of UxV ((UxV)xU)
//   U here is any point on the plane whose normal is NormU
//   V here is a line
//   returns the point where the line crosses that plane

void FindContactSetLineThroughPlane (const Vector3 akV[2], 
    const Vector3& rkU, const Vector3& rkNormU,
    int& riQuantity, Vector3* akP);

// for two statically intersecting lines

void FindContactSetLinLin (const Vector3 akU[2], 
    const Vector3 akV[2], int& riQuantity, Vector3* akP);

}

