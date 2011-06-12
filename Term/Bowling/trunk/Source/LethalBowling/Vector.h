#pragma once

#include <math.h>

namespace Virgin
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

    Vector3 operator*(float value) const
    {
        return Vector3(X*value, Y*value, Z*value);
    }

    Vector3 operator/(float value) const
    {
        return Vector3(X/value, Y/value, Z/value);
    }

    Vector3& operator+=(const Vector3& rhs)
    {
        X += rhs.X;
        Y += rhs.Y;
        Z += rhs.Z;
        return *this;
    }

    Vector3& operator-=(const Vector3& rhs)
    {
        X -= rhs.X;
        Y -= rhs.Y;
        Z -= rhs.Z;
        return *this;
    }

    Vector3& operator*=(float value)
    {
        X *= value;
        Y *= value;
        Z *= value;
        return *this;
    }

    Vector3& operator/=(float value)
    {
        X /= value;
        Y /= value;
        Z /= value;
        return *this;
    }

    Vector3 operator-() const
    {
        return Vector3(-X, -Y, -Z);
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

    // X^2 + Y^2 + Z^2
    float SquareSize() const
    {
        return X*X + Y*Y + Z*Z;
    }

    float Size() const
    {
        return sqrt(SquareSize());
    }


public:
    float X;
    float Y;
    float Z;
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
