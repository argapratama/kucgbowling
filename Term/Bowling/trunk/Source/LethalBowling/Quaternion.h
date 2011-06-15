#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace Virgin
{

class Quaternion
{
public:
    // A quaternion is q = w + x*i + y*j + z*k where (w,x,y,z) is not
    // necessarily a unit length vector in 4D.

    // construction
    Quaternion ();  // uninitialized
    Quaternion (float fW, float fX, float fY, float fZ);
    Quaternion (const Quaternion& rkQ);

    // quaternion for the input rotation matrix
    Quaternion (const Matrix3& rkRot);

    // quaternion for the rotation of the axis-angle pair
    Quaternion (const Vector3& rkAxis, float fAngle);

    // quaternion for the rotation matrix with specified columns
    Quaternion (const Vector3 akRotColumn[3]);

    // member access:  0 = w, 1 = x, 2 = y, 3 = z
    operator const float* () const;
    operator float* ();
    float operator[] (int i) const;
    float& operator[] (int i);
    float W () const;
    float& W ();
    float X () const;
    float& X ();
    float Y () const;
    float& Y ();
    float Z () const;
    float& Z ();

    // assignment and comparison
    Quaternion& operator= (const Quaternion& rkQ);
    bool operator== (const Quaternion& rkQ) const;
    bool operator!= (const Quaternion& rkQ) const;
    bool operator<  (const Quaternion& rkQ) const;
    bool operator<= (const Quaternion& rkQ) const;
    bool operator>  (const Quaternion& rkQ) const;
    bool operator>= (const Quaternion& rkQ) const;

    // arithmetic operations
    Quaternion operator+ (const Quaternion& rkQ) const;
    Quaternion operator- (const Quaternion& rkQ) const;
    Quaternion operator* (const Quaternion& rkQ) const;
    Quaternion operator* (float fScalar) const;
    Quaternion operator/ (float fScalar) const;
    Quaternion operator- () const;

    // arithmetic updates
    Quaternion& operator+= (const Quaternion& rkQ);
    Quaternion& operator-= (const Quaternion& rkQ);
    Quaternion& operator*= (float fScalar);
    Quaternion& operator/= (float fScalar);

    // conversion between quaternions, matrices, and axis-angle
    void FromRotationMatrix (const Matrix3& rkRot);
    void ToRotationMatrix (Matrix3& rkRot) const;
    void FromRotationMatrix (const Vector3 akRotColumn[3]);
    void ToRotationMatrix (Vector3 akRotColumn[3]) const;
    void FromAxisAngle (const Vector3& rkAxis,float fAngle);
    void ToAxisAngle (Vector3& rkAxis, float& rfAngle) const;

    // functions of a quaternion
    float Dot (const Quaternion& rkQ) const;  // dot product
    Quaternion Inverse () const;  // apply to non-zero quaternion
    Quaternion Conjugate () const;
    Quaternion Exp () const;  // apply to quaternion with w = 0
    Quaternion Log () const;  // apply to unit-length quaternion

    // rotation of a vector by a quaternion
    Vector3 operator* (const Vector3& rkVector) const;

    // spherical linear interpolation
    static Quaternion Slerp (float fT, const Quaternion& rkP,
        const Quaternion& rkQ);

    static Quaternion SlerpExtraSpins (float fT, const Quaternion& rkP,
        const Quaternion& rkQ, int iExtraSpins);

    // intermediate terms for spherical quadratic interpolation
    static Quaternion GetIntermediate (const Quaternion& rkQ0,
        const Quaternion& rkQ1,  const Quaternion& rkQ2);

    // spherical quadratic interpolation
    static Quaternion Squad (float fT, const Quaternion& rkQ0,
        const Quaternion& rkA0, const Quaternion& rkA1,
        const Quaternion& rkQ1);

    // special values
    static const Quaternion IDENTITY;  // the identity rotation
    static const Quaternion ZERO;

protected:
    // support for comparisons
    int CompareArrays (const Quaternion& rkQ) const;

    // support for FromRotationMatrix
    static int ms_iNext[3];

    float m_afTuple[4];
};

Quaternion operator* (float fScalar, const Quaternion& rkQ);


}
