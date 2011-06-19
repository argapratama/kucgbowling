#include "Plane.h"
#include "Vector.h"
#include "TMath.h"

namespace Virgin
{

//----------------------------------------------------------------------------

Plane3::Plane3 ()
{
    for (int i = 0; i < 4; i++)
        m_afTuple[i] = (float)0.0;
}
//----------------------------------------------------------------------------

Plane3::Plane3 (const Vector3& rkNormal, float fConstant)
{
    m_afTuple[0] = rkNormal.X();
    m_afTuple[1] = rkNormal.Y();
    m_afTuple[2] = rkNormal.Z();
    m_afTuple[3] = fConstant;
}
//----------------------------------------------------------------------------

Plane3::Plane3 (const Vector3& rkNormal,
    const Vector3& rkPoint)
{
    m_afTuple[0] = rkNormal.X();
    m_afTuple[1] = rkNormal.Y();
    m_afTuple[2] = rkNormal.Z();
    m_afTuple[3] = rkNormal.Dot(rkPoint);
}
//----------------------------------------------------------------------------

Plane3::Plane3 (const Vector3& rkPoint0,
    const Vector3& rkPoint1, const Vector3& rkPoint2)
{
    Vector3 kEdge1 = rkPoint1 - rkPoint0;
    Vector3 kEdge2 = rkPoint2 - rkPoint0;
    Vector3 kNormal = kEdge1.UnitCross(kEdge2);
    m_afTuple[0] = kNormal.X();
    m_afTuple[1] = kNormal.Y();
    m_afTuple[2] = kNormal.Z();
    m_afTuple[3] = kNormal.Dot(rkPoint0);
}
//----------------------------------------------------------------------------

Plane3::Plane3 (const Plane3& rkPlane)
{
    memcpy(m_afTuple,rkPlane.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------

void Plane3::SetNormal (const Vector3& rkNormal)
{
    m_afTuple[0] = rkNormal.X();
    m_afTuple[1] = rkNormal.Y();
    m_afTuple[2] = rkNormal.Z();
}
//----------------------------------------------------------------------------

Vector3 Plane3::GetNormal () const
{
    return Vector3(m_afTuple[0],m_afTuple[1],m_afTuple[2]);
}
//----------------------------------------------------------------------------

void Plane3::SetConstant (float fConstant)
{
    m_afTuple[3] = fConstant;
}
//----------------------------------------------------------------------------

float Plane3::GetConstant () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

void Plane3::Set (const Vector3& rkNormal, float fConstant)
{
    m_afTuple[0] = rkNormal.X();
    m_afTuple[1] = rkNormal.Y();
    m_afTuple[2] = rkNormal.Z();
    m_afTuple[3] = fConstant;
}
//----------------------------------------------------------------------------

void Plane3::Get (Vector3& rkNormal, float& rfConstant) const
{
    rkNormal.X() = m_afTuple[0];
    rkNormal.Y() = m_afTuple[1];
    rkNormal.Z() = m_afTuple[2];
    rfConstant = m_afTuple[3];
}
//----------------------------------------------------------------------------

Plane3::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

Plane3::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

float Plane3::operator[] (int i) const
{
    //assert( 0 <= i && i < 4 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

float& Plane3::operator[] (int i)
{
    //assert( 0 <= i && i < 4 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

Plane3::operator Point4()
{
    return Point4(m_afTuple[0],m_afTuple[1],m_afTuple[2],-m_afTuple[3]);
}
//----------------------------------------------------------------------------

Plane3& Plane3::operator= (const Plane3& rkPlane)
{
    memcpy(m_afTuple,rkPlane.m_afTuple,4*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

float Plane3::DistanceTo (const Vector3& rkPoint) const
{
    return m_afTuple[0]*rkPoint.X() + m_afTuple[1]*rkPoint.Y() +
        m_afTuple[2]*rkPoint.Z() - m_afTuple[3];
}
//----------------------------------------------------------------------------

Plane3::Side Plane3::WhichSide
    (const Vector3& rkPoint) const
{
    float fDistance = DistanceTo(rkPoint);

    if ( fDistance < (float)0.0 )
        return Plane3::NEGATIVE_SIDE;

    if ( fDistance > (float)0.0 )
        return Plane3::POSITIVE_SIDE;

    return Plane3::NO_SIDE;
}
//----------------------------------------------------------------------------

void Plane3::Normalize ()
{
    // //assert:  |N| > 0
    float fSqrLength = m_afTuple[0]*m_afTuple[0] + m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2];
    float fInvLength = Math::InvSqrt(fSqrLength);
    for (int i = 0; i < 4; i++)
        m_afTuple[i] *= fInvLength;
}

}

