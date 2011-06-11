#pragma once

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
    ~Matrix3();

    float det();
    Matrix3 Transpose();
    Matrix3 Inverse();

    Matrix3 operator+=(const Matrix3& rhs);
    Matrix3 operator-=(const Matrix3& rhs);
    Matrix3 operator*=(const Matrix3& rhs);
    Matrix3 operator/=(const Matrix3& rhs);


public:
    float Values[3][3];
};

}
