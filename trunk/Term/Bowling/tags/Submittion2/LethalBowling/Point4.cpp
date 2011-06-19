#include "Point4.h"

namespace Virgin
{

//----------------------------------------------------------------------------
template <int N>
Point<N>::Point ()
{
    // For efficiency in construction of large arrays of points, the
    // default constructor does not initialize the point.
}
//----------------------------------------------------------------------------
template <int N>
Point<N>::Point (const float* afTuple)
{
    memcpy(m_afTuple,afTuple,N*sizeof(float));
}
//----------------------------------------------------------------------------
template <int N>
Point<N>::Point (const Point& rkP)
{
    memcpy(m_afTuple,rkP.m_afTuple,N*sizeof(float));
}
//----------------------------------------------------------------------------
template <int N>
Point<N>::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <int N>
Point<N>::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
template <int N>
float Point<N>::operator[] (int i) const
{
    assert( 0 <= i && i < N );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <int N>
float& Point<N>::operator[] (int i)
{
    assert( 0 <= i && i < N );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
template <int N>
Point<N>& Point<N>::operator= (const Point& rkP)
{
    memcpy(m_afTuple,rkP.m_afTuple,N*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator== (const Point& rkP) const
{
    for (int i = 0; i < N; i++)
    {
        if ( m_afTuple[i] != rkP.m_afTuple[i] )
            return false;
    }
    return true;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator!= (const Point& rkP) const
{
    return !operator==(rkP);
}
//----------------------------------------------------------------------------
template <int N>
int Point<N>::CompareArrays (const Point& rkP) const
{
    for (int i = 0; i < N; i++)
    {
        unsigned int uiTest0 = *(unsigned int*)&m_afTuple[i];
        unsigned int uiTest1 = *(unsigned int*)&rkP.m_afTuple[i];
        if ( uiTest0 < uiTest1 )
            return -1;
        if ( uiTest0 > uiTest1 )
            return +1;
    }
    return 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator<  (const Point& rkP) const
{
    return CompareArrays(rkP) < 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator<= (const Point& rkP) const
{
    return CompareArrays(rkP) <= 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator>  (const Point& rkP) const
{
    return CompareArrays(rkP) > 0;
}
//----------------------------------------------------------------------------
template <int N>
bool Point<N>::operator>= (const Point& rkP) const
{
    return CompareArrays(rkP) >= 0;
}
//----------------------------------------------------------------------------
template <int N>
Point<N> Point<N>::operator+ (const Vector<N>& rkV) const
{
    Point<N> kSum;
    for (int i = 0; i < N; i++)
        kSum.m_afTuple[i] = m_afTuple[i] + rkV[i];
    return kSum;
}
//----------------------------------------------------------------------------
template <int N>
Vector<N> Point<N>::operator- (const Point& rkP) const
{
    Vector<N> kDiff;
    for (int i = 0; i < N; i++)
        kDiff[i] = m_afTuple[i] - rkP.m_afTuple[i];
    return kDiff;
}
//----------------------------------------------------------------------------
template <int N>
Point<N> Point<N>::AffineSum (float fT, const Point& rkP) const
{
    Point<N> kSum;
    for (int i = 0; i < N; i++)
        kSum.m_afTuple[i] = m_afTuple[i]+fT*(rkP.m_afTuple[i]-m_afTuple[i]);
    return kSum;
}









//----------------------------------------------------------------------------

Point4::Point4 ()
{
    // the point is uninitialized
}
//----------------------------------------------------------------------------

Point4::Point4 (float fX, float fY, float fZ, float fW)
{
    m_afTuple[0] = fX;
    m_afTuple[1] = fY;
    m_afTuple[2] = fZ;
    m_afTuple[3] = fW;
}
//----------------------------------------------------------------------------

Point4::Point4 (const Point4& rkP)
{
    memcpy(m_afTuple,rkP.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------

Point4::Point4 (const Point<4>& rkP)
{
    memcpy(m_afTuple,(const float*)rkP,4*sizeof(float));
}
//----------------------------------------------------------------------------

float Point4::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float& Point4::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float Point4::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float& Point4::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float Point4::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

float& Point4::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

float Point4::W () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

float& Point4::W ()
{
    return m_afTuple[3];
}

}

