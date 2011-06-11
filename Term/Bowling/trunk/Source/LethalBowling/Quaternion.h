#pragma once

#include "Vector.h"

namespace Virgin
{

class Quaternion
{
public:
    Quaternion();
    Quaternion(float e0, float e1, float e2, float e3);

    float Size() const;
    Vector3 GetVector() const;
    float GetScalar() const;
    Quaternion operator+=(const Quaternion& q);
    Quaternion operator-=(const Quaternion& q);
    Quaternion operator*=(float s);
    Quaternion operator/=(float s);
    Quaternion operator~() const;

    float GetAngle() const;
    Vector3 GetAxis() const;
    Quaternion Rotate(const Quaternion& rhs) const;
    Vector3 VRotate(const Vector3& v) const;

    static Quaternion FromEulerAngles(float x, float y, float z);
    Vector3 ToEulerAngles() const;

public:
    float n;
    Vector3 v;
};

//
// Quaterion 다룰 때 사용할 함수들
//
inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.n + q2.n, q1.v.X + q2.v.X, q1.v.Y + q2.v.Y, q1.v.Z + q2.v.Z);
}

inline Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.n - q2.n, q1.v.X - q2.v.X, q1.v.Y - q2.v.Y, q1.v.Z - q2.v.Z);
}

inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.n*q2.n - q1.v.X*q2.v.X - q1.v.Y*q2.v.Y - q1.v.Z*q2.v.Z,
                      q1.n*q2.v.X + q1.v.X*q2.n + q1.v.Y*q2.v.Z - q1.v.Z*q2.v.Y,
                      q1.n*q2.v.Y + q1.v.Y*q2.n + q1.v.Z*q2.v.X - q1.v.X*q2.v.Z,
                      q1.n*q2.v.Z + q1.v.Z*q2.n + q1.v.X*q2.v.Y - q1.v.Y*q2.v.X);
}

inline Quaternion operator*(const Quaternion& q, float s)
{
    return Quaternion(q.n*s, q.v.X*s, q.v.Y*s, q.v.Z*s);
}

inline Quaternion operator*(float s, const Quaternion& q)
{
    return Quaternion(q.n*s, q.v.X*s, q.v.Y*s, q.v.Z*s);
}

inline Quaternion operator*(const Quaternion& q, const Vector3& v)
{
    return Quaternion( -(q.v.X*v.X + q.v.Y*v.Y + q.v.Z*v.Z),
                         q.n*v.X + q.v.Y*v.Z - q.v.Z*v.Y,
                         q.n*v.Y + q.v.Z*v.X - q.v.X*v.Z,
                         q.n*v.Z + q.v.X*v.Y - q.v.Y*v.X);
}

inline Quaternion operator*(const Vector3& v, const Quaternion& q)
{
    return Quaternion( -(q.v.X*v.X + q.v.Y*v.Y + q.v.Z*v.Z),
                         q.n*v.X + q.v.Z*v.Y - q.v.Y*v.Z,
                         q.n*v.Y + q.v.X*v.Z - q.v.Z*v.X,
                         q.n*v.Z + q.v.Y*v.X - q.v.X*v.Y);
}

inline Quaternion operator/(const Quaternion& q, float s)
{
    return Quaternion(q.n/s, q.v.X/s, q.v.Y/s, q.v.Z/s);
}



}
