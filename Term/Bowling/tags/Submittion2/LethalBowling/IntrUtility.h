#pragma once

#include "Vector.h"

namespace Virgin
{

enum VertexProjectionMap
{
    m2, m11,                // lines
    m3, m21, m12, m111,     // triangles
    m44, m2_2, m1_1         // boxes
};

enum ContactSide
{
    LEFT,
    RIGHT,
    NONE
};


class ContactConfig
{
public:
    // The number/configuration of vertices in Index
    VertexProjectionMap m_kMap;

    // Order of vertices
    int m_aiIndex[8];

    // Interval
    float m_fMin, m_fMax;
};


bool AxisTest (const Vector3& rkVelocity,
    const Vector3& rkTestAxis, float fUMin, float fUMax, float fVMin,
    float fVMax, float& rfTFirst, float& rfTLast, float fTMax);


bool AxisFind (const Vector3& rkVelocity, 
    const Vector3& rkTestAxis, const ContactConfig& rrkUC, 
    const ContactConfig& rrkVC, ContactSide& rkSide,
    ContactConfig& rkTUC, ContactConfig& rkTVC, float& rfTFirst,
    float& rfTLast, float fTMax);

// The input and output polygons are stored in akP.  The size of akP is
// assumed to be large enough to store the clipped convex polygon vertices.
// For now the maximum array size is 8 to support the current intersection
// algorithms.

void ClipConvexPolygonAgainstPlane (const Vector3& rkNormal,
    float fConstant, int& riQuantity, Vector3* akP);

}



