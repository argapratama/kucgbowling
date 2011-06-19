#include "Vector.h"

#include "TMath.h"

namespace Virgin
{


//----------------------------------------------------------------------------
template <int N>
Vector<N>::Vector ()
{
    // For efficiency in construction of large arrays of vectors, the
    // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>::Vector (const float* afTuple)
{
    memcpy(m_afTuple,afTuple,N*sizeof(float));
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>::Vector (const Vector<N>& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,N*sizeof(float));
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <int N>
float Vector<N>::operator[] (int i) const
{
    //assert( 0 <= i && i < N );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <int N>
float& Vector<N>::operator[] (int i)
{
    //assert( 0 <= i && i < N );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>& Vector<N>::operator= (const Vector<N>& rkV)
{
    memcpy(m_afTuple,rkV.m_afTuple,N*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------
template <int N>
bool Vector<N>::operator== (const Vector<N>& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,N*sizeof(float)) == 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Vector<N>::operator!= (const Vector<N>& rkV) const
{
    return memcmp(m_afTuple,rkV.m_afTuple,N*sizeof(float)) != 0;
}
//----------------------------------------------------------------------------
template <int N>
int Vector<N>::CompareArrays (const Vector<N>& rkV) const
{
    for (int i = 0; i < N; i++)
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
template <int N>
bool Vector<N>::operator< (const Vector<N>& rkV) const
{
    return CompareArrays(rkV) < 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Vector<N>::operator<= (const Vector<N>& rkV) const
{
    return CompareArrays(rkV) <= 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Vector<N>::operator> (const Vector<N>& rkV) const
{
    return CompareArrays(rkV) > 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Vector<N>::operator>= (const Vector<N>& rkV) const
{
    return CompareArrays(rkV) >= 0;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Vector<N>::operator+ (const Vector<N>& rkV) const
{
    Vector<N> kSum;
    for (int i = 0; i < N; i++)
        kSum.m_afTuple[i] = m_afTuple[i] + rkV.m_afTuple[i];
    return kSum;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Vector<N>::operator- (const Vector<N>& rkV) const
{
    Vector<N> kDiff;
    for (int i = 0; i < N; i++)
        kDiff.m_afTuple[i] = m_afTuple[i] - rkV.m_afTuple[i];
    return kDiff;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Vector<N>::operator* (float fScalar) const
{
    Vector<N> kProd;
    for (int i = 0; i < N; i++)
        kProd.m_afTuple[i] = fScalar*m_afTuple[i];
    return kProd;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Vector<N>::operator/ (float fScalar) const
{
    Vector<N> kQuot;
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < N; i++)
            kQuot.m_afTuple[i] = fInvScalar*m_afTuple[i];
    }
    else
    {
        for (i = 0; i < N; i++)
            kQuot.m_afTuple[i] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Vector<N>::operator- () const
{
    Vector<N> kNeg;
    for (int i = 0; i < N; i++)
        kNeg.m_afTuple[i] = -m_afTuple[i];
    return kNeg;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> operator* (float fScalar, const Vector<N>& rkV)
{
    Vector<N> kProd;
    for (int i = 0; i < N; i++)
        kProd[i] = fScalar*rkV[i];
    return kProd;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>& Vector<N>::operator+= (const Vector<N>& rkV)
{
    for (int i = 0; i < N; i++)
        m_afTuple[i] += rkV.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>& Vector<N>::operator-= (const Vector<N>& rkV)
{
    for (int i = 0; i < N; i++)
        m_afTuple[i] -= rkV.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>& Vector<N>::operator*= (float fScalar)
{
    for (int i = 0; i < N; i++)
        m_afTuple[i] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N>& Vector<N>::operator/= (float fScalar)
{
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < N; i++)
            m_afTuple[i] *= fInvScalar;
    }
    else
    {
        for (i = 0; i < N; i++)
            m_afTuple[i] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int N>
float Vector<N>::Length () const
{
    float fSqrLen = (float)0.0;
    for (int i = 0; i < N; i++)
        fSqrLen += m_afTuple[i]*m_afTuple[i];
    return Math::Sqrt(fSqrLen);
}
//----------------------------------------------------------------------------
template <int N>
float Vector<N>::SquaredLength () const
{
    float fSqrLen = (float)0.0;
    for (int i = 0; i < N; i++)
        fSqrLen += m_afTuple[i]*m_afTuple[i];
    return fSqrLen;
}
//----------------------------------------------------------------------------
template <int N>
float Vector<N>::Dot (const Vector<N>& rkV) const
{
    float fDot = (float)0.0;
    for (int i = 0; i < N; i++)
        fDot += m_afTuple[i]*rkV.m_afTuple[i];
    return fDot;
}
//----------------------------------------------------------------------------
template <int N>
float Vector<N>::Normalize ()
{
    float fLength = Length();
    int i;

    if ( fLength > Math::EPSILON )
    {
        float fInvLength = ((float)1.0)/fLength;
        for (i = 0; i < N; i++)
            m_afTuple[i] *= fInvLength;
    }
    else
    {
        fLength = (float)0.0;
        for (i = 0; i < N; i++)
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

Vector3::Vector3 (const Vector<3>& rkV)
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

Vector3& Vector3::operator= (const Vector<3>& rkV)
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

template class Vector<3>;

const Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_X(1.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_Y(0.0f,1.0f,0.0f);
const Vector3 Vector3::UNIT_Z(0.0f,0.0f,1.0f);


}
