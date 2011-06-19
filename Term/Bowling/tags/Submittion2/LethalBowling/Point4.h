#pragma once

#include "Vector.h"

namespace Virgin
{

template <int N>
class Point
{
public:
    // construction
    Point ();
    Point (const float* afTuple);
    Point (const Point& rkP);

    // coordinate access
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);

    // assignment
    Point& operator= (const Point& rkP);

    // comparison
    bool operator== (const Point& rkP) const;
    bool operator!= (const Point& rkP) const;
    bool operator<  (const Point& rkP) const;
    bool operator<= (const Point& rkP) const;
    bool operator>  (const Point& rkP) const;
    bool operator>= (const Point& rkP) const;

    // arithmetic operations
    Point operator+ (const Vector<N>& rkV) const;
    Vector<N> operator- (const Point& rkP) const;

    // result = (1-t)*this + t*P
    Point AffineSum (float fT, const Point& rkP) const;

protected:
    // support for comparisons
    int CompareArrays (const Point& rkP) const;

    float m_afTuple[N];
};


class Point4 : public Point<4>
{
public:
    // construction
    Point4 ();
    Point4 (float fX, float fY, float fZ, float fW);
    Point4 (const Point4& rkP);
    Point4 (const Point<4>& rkP);

    // member access
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();
    float Z () const;
    float& Z ();
    float W () const;
    float& W ();

    // special point
    static const Point4 ZERO;
};

}
