#pragma once

#include <math.h>

namespace Virgin
{

class Vector
{
public:
    // construction
    Vector ();
    Vector (const float* afTuple);
    Vector (const Vector& rkV);

    // coordinate access
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);

    // assignment
    Vector& operator= (const Vector& rkV);

    // comparison
    bool operator== (const Vector& rkV) const;
    bool operator!= (const Vector& rkV) const;
    bool operator<  (const Vector& rkV) const;
    bool operator<= (const Vector& rkV) const;
    bool operator>  (const Vector& rkV) const;
    bool operator>= (const Vector& rkV) const;

    // arithmetic operations
    Vector operator+ (const Vector& rkV) const;
    Vector operator- (const Vector& rkV) const;
    Vector operator* (float fScalar) const;
    Vector operator/ (float fScalar) const;
    Vector operator- () const;

    // arithmetic updates
    Vector& operator+= (const Vector& rkV);
    Vector& operator-= (const Vector& rkV);
    Vector& operator*= (float fScalar);
    Vector& operator/= (float fScalar);

    // vector operations
    float Length () const;
    float SquaredLength () const;
    float Dot (const Vector& rkV) const;
    float Normalize ();

protected:
    // support for comparisons
    int CompareArrays (const Vector& rkV) const;

    float m_afTuple[3];
};

Vector operator* (float fScalar, const Vector& rkV);


/////////////////////////////////////////////////////////////

class Vector3 : public Vector
{
public:
    // construction
    Vector3 ();
    Vector3 (float fX, float fY, float fZ);
    Vector3 (const Vector3& rkV);
    Vector3 (const Vector& rkV);

    // member access
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();
    float Z () const;
    float& Z ();

    // assignment
    Vector3& operator= (const Vector3& rkV);
    Vector3& operator= (const Vector& rkV);

    // The cross products are computed using the right-handed rule.  Be aware
    // that some graphics APIs use a left-handed rule.  If you have to compute
    // a cross product with these functions and send the result to the API
    // that expects left-handed, you will need to change sign on the vector
    // (replace each component value c by -c).
    Vector3 Cross (const Vector3& rkV) const;
    Vector3 UnitCross (const Vector3& rkV) const;

    // Gram-Schmidt orthonormalization.  Take linearly independent vectors
    // U, V, and W and compute an orthonormal set (unit length, mutually
    // perpendicular).
    static void Orthonormalize (Vector3& rkU, Vector3& rkV, Vector3& rkW);
    static void Orthonormalize (Vector3 akV[/*3*/]);

    // Input W must be initialized to a nonzero vector, output is {U,V,W},
    // an orthonormal basis.  A hint is provided about whether or not W
    // is already unit length.
    static void GenerateOrthonormalBasis (Vector3& rkU, Vector3& rkV,
        Vector3& rkW, bool bUnitLengthW);

    // special vectors
    static const Vector3 ZERO;
    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
};


// 정수형 3차 벡터
struct Vector3D
{
public:
    Vector3D()
        : X(0), Y(0), Z(0)
    {
    }

    Vector3D(int x, int y, int z)
        : X(x), Y(y), Z(z)
    {
    }

public:
    int X;
    int Y;
    int Z;
};

}
