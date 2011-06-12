#pragma once

#include "Vector.h"

namespace Virgin
{

class Matrix3
{
public:
    Matrix3()
    {
        Values[0][0] = 0.0;
        Values[0][1] = 0.0;
        Values[0][2] = 0.0;
        Values[1][0] = 0.0;
        Values[1][1] = 0.0;
        Values[1][2] = 0.0;
        Values[2][0] = 0.0;
        Values[2][1] = 0.0;
        Values[2][2] = 0.0;
    }

    Matrix3(float r1c1, float r1c2, float r1c3,
            float r2c1, float r2c2, float r2c3,
            float r3c1, float r3c2, float r3c3)
    {
        Values[0][0] = r1c1;
        Values[0][1] = r1c2;
        Values[0][2] = r1c3;
        Values[1][0] = r2c1;
        Values[1][1] = r2c2;
        Values[1][2] = r2c3;
        Values[2][0] = r3c1;
        Values[2][1] = r3c2;
        Values[2][2] = r3c3;
    }

    //Matrix3(const Matrix3& rhs);

    float Determinant() const;
    Matrix3 Transpose();
    Matrix3 Inverse();

    Matrix3 operator+=(const Matrix3& rhs);
    Matrix3 operator-=(const Matrix3& rhs);
    Matrix3 operator*=(const Matrix3& rhs);
    Matrix3 operator/=(const Matrix3& rhs);

public:
    union
    {
        struct
        {
            float M11;
            float M12;
            float M13;
            float M21;
            float M22;
            float M23;
            float M31;
            float M32;
            float M33;
        };

        float Values[3][3];
    };
};

inline Matrix3 operator*(const Matrix3& m1, const Matrix3& m2)
{
    return Matrix3(m1.M11*m2.M11 + m1.M12*m2.M21 + m1.M13*m2.M31, m1.M11*m2.M12 + m1.M12*m2.M22 + m1.M13*m2.M32, m1.M11*m2.M13 + m1.M12*m2.M23 + m1.M13*m2.M33,
                   m1.M21*m2.M11 + m1.M22*m2.M21 + m1.M23*m2.M31, m1.M21*m2.M12 + m1.M22*m2.M22 + m1.M23*m2.M32, m1.M21*m2.M13 + m1.M22*m2.M23 + m1.M23*m2.M33,
                   m1.M31*m2.M11 + m1.M32*m2.M21 + m1.M33*m2.M31, m1.M31*m2.M12 + m1.M32*m2.M22 + m1.M33*m2.M32, m1.M31*m2.M13 + m1.M32*m2.M23 + m1.M33*m2.M33);
}

inline Vector3 operator*(const Matrix3& m, const Vector3& u)
{
    return Vector3(m.M11*u.X + m.M12*u.Y + m.M13*u.Z,
                   m.M21*u.X + m.M22*u.Y + m.M23*u.Z,
                   m.M31*u.X + m.M32*u.Y + m.M33*u.Z);
}

inline Vector3 operator*(const Vector3& u, const Matrix3& m)
{
    return Vector3(u.X*m.M11 + u.Y*m.M21 + u.Z*m.M31, 
                   u.X*m.M12 + u.Y*m.M22 + u.Z*m.M32,
                   u.X*m.M13 + u.Y*m.M23 + u.Z*m.M33);
}

}
