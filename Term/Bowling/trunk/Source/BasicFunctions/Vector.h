#pragma once

#include <math.h>

namespace OpenGl
{

struct Vector3
{
public:
    Vector3()
        : X(0.0), Y(0.0), Z(0.0)
    {
    }

    Vector3(float x, float y, float z)
        : X(x), Y(y), Z(z)
    {
    }

    void Reset()
    {
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
    }

    Vector3 Cross(const Vector3& rhs) const
    {
        return Vector3(Y*rhs.Z - Z*rhs.Y, Z*rhs.X - X*rhs.Z, X*rhs.Y - Y*rhs.X);
    }

    Vector3 operator-(const Vector3& rhs) const
    {
        return Vector3(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
    }

    Vector3 operator+(const Vector3& rhs) const
    {
        return Vector3(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
    }

    Vector3 operator*(float magnitude) const
    {
        return Vector3(X*magnitude, Y*magnitude, Z*magnitude);
    }

    Vector3& operator+=(const Vector3& rhs)
    {
        X += rhs.X;
        Y += rhs.Y;
        Z += rhs.Z;
        return *this;
    }

    Vector3& operator*=(float value)
    {
        X *= value;
        Y *= value;
        Z *= value;
        return *this;
    }

    void Normalize()
    {
        const float size = Size();
        if(size != 0.0)
        {
            X /= size;
            Y /= size;
            Z /= size;
        }
    }

    float Size() const
    {
        return sqrt(X*X + Y*Y + Z*Z);
    }


public:
    float X;
    float Y;
    float Z;
};

}
