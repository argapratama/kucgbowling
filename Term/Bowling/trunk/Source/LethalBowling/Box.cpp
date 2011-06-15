#include "Box.h"

namespace Virgin
{

//----------------------------------------------------------------------------

Box::Box ()
{
    // no initialization for efficiency
}
//----------------------------------------------------------------------------

Vector3& Box::Center ()
{
    return m_kCenter;
}
//----------------------------------------------------------------------------

const Vector3& Box::Center () const
{
    return m_kCenter;
}
//----------------------------------------------------------------------------

Vector3& Box::Axis (int i)
{
    //assert( 0 <= i && i < 3 );
    return m_akAxis[i];
}
//----------------------------------------------------------------------------

const Vector3& Box::Axis (int i) const
{
    //assert( 0 <= i && i < 3 );
    return m_akAxis[i];
}
//----------------------------------------------------------------------------

Vector3* Box::Axes ()
{
    return m_akAxis;
}
//----------------------------------------------------------------------------

const Vector3* Box::Axes () const
{
    return m_akAxis;
}
//----------------------------------------------------------------------------

float& Box::Extent (int i)
{
    //assert( 0 <= i && i < 3 );
    return m_afExtent[i];
}
//----------------------------------------------------------------------------

const float& Box::Extent (int i) const
{
    //assert( 0 <= i && i < 3 );
    return m_afExtent[i];
}
//----------------------------------------------------------------------------

float* Box::Extents ()
{
    return m_afExtent;
}
//----------------------------------------------------------------------------

const float* Box::Extents () const
{
    return m_afExtent;
}
//----------------------------------------------------------------------------

void Box::ComputeVertices (Vector3 akVertex[8]) const
{
    Vector3 akEAxis[3] =
    {
        m_afExtent[0]*m_akAxis[0],
        m_afExtent[1]*m_akAxis[1],
        m_afExtent[2]*m_akAxis[2]
    };

    akVertex[0] = m_kCenter - akEAxis[0] - akEAxis[1] - akEAxis[2];
    akVertex[1] = m_kCenter + akEAxis[0] - akEAxis[1] - akEAxis[2];
    akVertex[2] = m_kCenter + akEAxis[0] + akEAxis[1] - akEAxis[2];
    akVertex[3] = m_kCenter - akEAxis[0] + akEAxis[1] - akEAxis[2];
    akVertex[4] = m_kCenter - akEAxis[0] - akEAxis[1] + akEAxis[2];
    akVertex[5] = m_kCenter + akEAxis[0] - akEAxis[1] + akEAxis[2];
    akVertex[6] = m_kCenter + akEAxis[0] + akEAxis[1] + akEAxis[2];
    akVertex[7] = m_kCenter - akEAxis[0] + akEAxis[1] + akEAxis[2];
}
}