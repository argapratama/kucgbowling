#pragma once

#include "Vector.h"
#include "Box.h"
#include "IntrUtility.h"

namespace Virgin
{

void BoxProjection (const Vector3& rkAxis,
    const Box& rkBox, float& rfMin, float& rfMax);

void GetBoxConfiguration (const Vector3& rkAxis, 
    const Box& rkBox, ContactConfig& rkConfig);

void FindContactSetCoplanarLineRect (const Vector3 akSeg[2],
    const Vector3 akFace[4], int& riQuantity, Vector3* akP);

// translates an index into the box back into float coordinates
Vector3 GetPoint (int iIndex, const Box& rkBox);

}

