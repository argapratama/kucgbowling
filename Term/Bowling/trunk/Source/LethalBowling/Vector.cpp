#include "Vector.h"

#include "TMath.h"

namespace Virgin
{


//----------------------------------------------------------------------------

Vector::Vector ()
{
    // For efficiency in construction of large arrays of vectors, the
    // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------

Vector::Vector (const float* afTuple)
{
    memcpy(m_afTuple,afTuple,3*sizeof(float));
}
//----------------------------------------------------------------------------

Vector::Vector (const Vector& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,3*sizeof(float));
}
//----------------------------------------------------------------------------

Vector::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

Vector::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

float Vector::operator[] (int i) const
{
    //assert( 0 <= i && i < 3 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

float& Vector::operator[] (int i)
{
    //assert( 0 <= i && i < 3 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

Vector& Vector::operator= (const Vector& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,3*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

bool Vector::operator== (const Vector& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,3*sizeof(float)) == 0;
}
//----------------------------------------------------------------------------

bool Vector::operator!= (const Vector& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,3*sizeof(float)) != 0;
}
//----------------------------------------------------------------------------

int Vector::CompareArrays (const Vector& rkV) const
{
    for (int i = 0; i < 3; i++)
    {
        unsigned int uiTest0 = *(unsigned int*)&m_afTuple[i];
        unsigned int uiTest1 = *(unsigned int*)&rkV.m_afTuple[i];
        if ( uiTest0 < uiTest1 )
            return -1;
        if ( uiTest0 > uiTest1 )
            return +1;
    }
    return 0;
}
//----------------------------------------------------------------------------

bool Vector::operator< (const Vector& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------

bool Vector::operator<= (const Vector& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------

bool Vector::operator> (const Vector& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------

bool Vector::operator>= (const Vector& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------

Vector Vector::operator+ (const Vector& rkV) const
{
    Vector kSum;
    for (int i = 0; i < 3; i++)
        kSum.m_afTuple[i] = m_afTuple[i] + rkV.m_afTuple[i];
    return kSum;
}
//----------------------------------------------------------------------------

Vector Vector::operator- (const Vector& rkV) const
{
    Vector kDiff;
    for (int i = 0; i < 3; i++)
        kDiff.m_afTuple[i] = m_afTuple[i] - rkV.m_afTuple[i];
    return kDiff;
}
//----------------------------------------------------------------------------

Vector Vector::operator* (float fScalar) const
{
    Vector kProd;
    for (int i = 0; i < 3; i++)
        kProd.m_afTuple[i] = fScalar*m_afTuple[i];
    return kProd;
}
//----------------------------------------------------------------------------

Vector Vector::operator/ (float fScalar) const
{
    Vector kQuot;
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 3; i++)
            kQuot.m_afTuple[i] = fInvScalar*m_afTuple[i];
    }
    else
    {
        for (i = 0; i < 3; i++)
            kQuot.m_afTuple[i] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------

Vector Vector::operator- () const
{
    Vector kNeg;
    for (int i = 0; i < 3; i++)
        kNeg.m_afTuple[i] = -m_afTuple[i];
    return kNeg;
}
//----------------------------------------------------------------------------

Vector operator* (float fScalar, const Vector& rkV)
{
    Vector kProd;
    for (int i = 0; i < 3; i++)
        kProd[i] = fScalar*rkV[i];
    return kProd;
}
//----------------------------------------------------------------------------

Vector& Vector::operator+= (const Vector& rkV)
{
    for (int i = 0; i < 3; i++)
        m_afTuple[i] += rkV.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------

Vector& Vector::operator-= (const Vector& rkV)
{
    for (int i = 0; i < 3; i++)
        m_afTuple[i] -= rkV.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------

Vector& Vector::operator*= (float fScalar)
{
    for (int i = 0; i < 3; i++)
        m_afTuple[i] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------

Vector& Vector::operator/= (float fScalar)
{
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 3; i++)
            m_afTuple[i] *= fInvScalar;
    }
    else
    {
        for (i = 0; i < 3; i++)
            m_afTuple[i] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------

float Vector::Length () const
{
    float fSqrLen = (float)0.0;
    for (int i = 0; i < 3; i++)
        fSqrLen += m_afTuple[i]*m_afTuple[i];
    return Math::Sqrt(fSqrLen);
}
//----------------------------------------------------------------------------

float Vector::SquaredLength () const
{
    float fSqrLen = (float)0.0;
    for (int i = 0; i < 3; i++)
        fSqrLen += m_afTuple[i]*m_afTuple[i];
    return fSqrLen;
}
//----------------------------------------------------------------------------

float Vector::Dot (const Vector& rkV) const
{
    float fDot = (float)0.0;
    for (int i = 0; i < 3; i++)
        fDot += m_afTuple[i]*rkV.m_afTuple[i];
    return fDot;
}
//----------------------------------------------------------------------------

float Vector::Normalize ()
{
    float fLength = Length();
    int i;

    if ( fLength > Math::EPSILON )
    {
        float fInvLength = ((float)1.0)/fLength;
        for (i = 0; i < 3; i++)
            m_afTuple[i] *= fInvLength;
    }
    else
    {
        fLength = (float)0.0;
        for (i = 0; i < 3; i++)
            m_afTuple[i] = (float)0.0;
    }

    return fLength;
}
//----------------------------------------------------------------------------





//----------------------------------------------------------------------------

Vector3::Vector3 ()
{
    // the vector is uninitialized
}
//----------------------------------------------------------------------------

Vector3::Vector3 (float fX, float fY, float fZ)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
}
//----------------------------------------------------------------------------

Vector3::Vector3 (const Vector3& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,3*sizeof(float));
}
//----------------------------------------------------------------------------

Vector3::Vector3 (const Vector& rkV)
{
    memcpy(m_afTuple,(const float*)rkV,3*sizeof(float));
}
//----------------------------------------------------------------------------

Vector3& Vector3::operator= (const Vector3& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,3*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

Vector3& Vector3::operator= (const Vector& rkV)
{
    memcpy(m_afTuple,(const float*)rkV,3*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

float Vector3::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float& Vector3::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float Vector3::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float& Vector3::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float Vector3::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

float& Vector3::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

Vector3 Vector3::Cross (const Vector3& rkV) const
{
    return Vector3(
        m_afTuple[1]*rkV.m_afTuple[2] - m_afTuple[2]*rkV.m_afTuple[1],
        m_afTuple[2]*rkV.m_afTuple[0] - m_afTuple[0]*rkV.m_afTuple[2],
        m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0]);
}
//----------------------------------------------------------------------------

Vector3 Vector3::UnitCross (const Vector3& rkV) const
{
    Vector3 kCross(
        m_afTuple[1]*rkV.m_afTuple[2] - m_afTuple[2]*rkV.m_afTuple[1],
        m_afTuple[2]*rkV.m_afTuple[0] - m_afTuple[0]*rkV.m_afTuple[2],
        m_afTuple[0]*rkV.m_afTuple[1] - m_afTuple[1]*rkV.m_afTuple[0]);
    kCross.Normalize();
    return kCross;
}
//----------------------------------------------------------------------------

void Vector3::Orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW)
{
    // If the input vectors are v0, v1, and v2, then the Gram-Schmidt
    // orthonormalization produces vectors u0, u1, and u2 as follows,
    //
    //   u0 = v0/|v0|
    //   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
    //   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
    //
    // where |A| indicates length of vector A and A*B indicates dot
    // product of vectors A and B.

    // compute u0
    rkU.Normalize();

    // compute u1
    float fDot0 = rkU.Dot(rkV); 
    rkV -= fDot0*rkU;
    rkV.Normalize();

    // compute u2
    float fDot1 = rkV.Dot(rkW);
    fDot0 = rkU.Dot(rkW);
    rkW -= fDot0*rkU + fDot1*rkV;
    rkW.Normalize();
}
//----------------------------------------------------------------------------

void Vector3::Orthonormalize (Vector3 akV[/*3*/])
{
    Orthonormalize(akV[0],akV[1],akV[2]);
}
//----------------------------------------------------------------------------

void Vector3::GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
    Vector3& rkW, bool bUnitLengthW)
{
    if ( !bUnitLengthW )
        rkW.Normalize();

    float fInvLength;

    if ( Math::FAbs(rkW.m_afTuple[0]) >=
         Math::FAbs(rkW.m_afTuple[1]) )
    {
        // W.x or W.z is the largest magnitude component, swap them
        fInvLength = Math::InvSqrt(rkW.m_afTuple[0]*rkW.m_afTuple[0] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = -rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[1] = (float)0.0;
        rkU.m_afTuple[2] = +rkW.m_afTuple[0]*fInvLength;
    }
    else
    {
        // W.y or W.z is the largest magnitude component, swap them
        fInvLength = Math::InvSqrt(rkW.m_afTuple[1]*rkW.m_afTuple[1] +
            rkW.m_afTuple[2]*rkW.m_afTuple[2]);
        rkU.m_afTuple[0] = (float)0.0;
        rkU.m_afTuple[1] = +rkW.m_afTuple[2]*fInvLength;
        rkU.m_afTuple[2] = -rkW.m_afTuple[1]*fInvLength;
    }

    rkV = rkW.Cross(rkU);
}
//----------------------------------------------------------------------------

const Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_X(1.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_Y(0.0f,1.0f,0.0f);
const Vector3 Vector3::UNIT_Z(0.0f,0.0f,1.0f);


}
