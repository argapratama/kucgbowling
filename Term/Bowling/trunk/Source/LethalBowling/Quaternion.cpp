#include "Quaternion.h"
#include "TMath.h"

namespace Virgin
{

Quaternion::Quaternion()
    : n(0.0)
{
}

Quaternion::Quaternion(float e0, float e1, float e2, float e3)
    : n(e0)
    , v(e1, e2, e3)
{
}

float Quaternion::Size() const
{
    return Math::Sqrt(n*n + v.SquareSize());
}

Vector3 Quaternion::GetVector() const
{
    return v;
}

float Quaternion::GetScalar() const
{
    return n;
}

Quaternion Quaternion::operator+=(const Quaternion& q)
{
    n += q.n;
    v += q.v;
    return *this;
}

Quaternion Quaternion::operator-=(const Quaternion& q)
{
    n -= q.n;
    v -= q.v;
    return *this;
}

Quaternion Quaternion::operator*=(float s)
{
    n *= s;
    v *= s;
    return *this;
}

Quaternion Quaternion::operator/=(float s)
{
    n /= s;
    v /= s;
    return *this;
}

Quaternion Quaternion::operator~() const
{
    return Quaternion(n, -v.X, -v.Y, -v.Z);
}

float Quaternion::GetAngle() const
{
    return 2*Math::Acos(n);
}

Vector3 Quaternion::GetAxis() const
{
    float magnitude = Size();

    if(magnitude <= Math::Epsilon)
    {
        return Vector3();
    }
    else
    {
        return v/magnitude;
    }
}

Quaternion Quaternion::Rotate(const Quaternion& rhs) const
{
    return (*this)*rhs*(~(*this));
}

Vector3 Quaternion::VRotate(const Vector3& v) const
{
    Quaternion t;

    t = (*this)*v*(~(*this));
    return t.GetVector();
}

Quaternion Quaternion::FromEulerAngles(float x, float y, float z)
{
    double roll = Math::DegreesToRadians(x);
    double pitch = Math::DegreesToRadians(y);
    double yaw = Math::DegreesToRadians(z);

    double cyaw = Math::Cos(0.5 * yaw);
    double cpitch = Math::Cos(0.5 * pitch);
    double croll = Math::Cos(0.5 * roll);
    double syaw = Math::Sin(0.5 * yaw);
    double spitch = Math::Sin(0.5 * pitch);
    double sroll = Math::Sin(0.5 * roll);

    double cyawcpitch = cyaw * cpitch;
    double syawspitch = syaw * spitch;
    double cyawspitch = cyaw * spitch;
    double syawcpitch = syaw * cpitch;

    return Quaternion(static_cast<float>(cyawcpitch * croll + syawspitch * sroll),
                      static_cast<float>(cyawcpitch * sroll - syawspitch * croll),
                      static_cast<float>(cyawspitch * croll + syawcpitch * sroll),
                      static_cast<float>(syawcpitch * croll - cyawspitch * sroll));
}

Vector3 Quaternion::ToEulerAngles() const
{
    double q00 = n * n;
    double q11 = v.X * v.X;
    double q22 = v.Y * v.Y;
    double q33 = v.Z * v.Z;

    double r11 = q00 + q11 - q22 - q33;
    double r21 = 2 * (v.X*v.Y + n*v.Z);
    double r31 = 2 * (v.X*v.Z - n*v.Y);
    double r32 = 2 * (v.Y*v.Z + n*v.X);
    double r33 = q00 - q11 - q22 + q33;

    Vector3 u;
    double r12;
    double r13;
    double tmp = Math::Abs(r31);
    if(tmp > 0.999999)
    {
        r12 = 2 * (v.X*v.Y - n*v.Z);
        r13 = 2 * (v.X*v.Z + n*v.Y);

        u.X = static_cast<float>(Math::RadiansToDegrees(0.0));
        u.Y = static_cast<float>(Math::RadiansToDegrees((-(Math::PI/2) * r31/tmp)));
        u.Z = static_cast<float>(Math::RadiansToDegrees(Math::Atan2(-r12, -r31*r13)));
        return u;
    }

    u.X = static_cast<float>(Math::RadiansToDegrees(Math::Atan2(r32, r33)));
    u.Y = static_cast<float>(Math::RadiansToDegrees(Math::Asin(-r31)));
    u.Z = static_cast<float>(Math::RadiansToDegrees(Math::Atan2(r21, r11)));
    return u;
}

Matrix3 Quaternion::ToMatrix() const
{
	double	q00, q11, q22, q33;
	
	Matrix3 m;

	q00 = n * n;
	q11 = v.X * v.X;
	q22 = v.Y * v.Y;
	q33 = v.Z * v.Z;

	m.M11 = q00 + q11 - q22 - q33;
	m.M21 = 2 * (v.X*v.Y + n*v.Z);
	m.M31 = 2 * (v.X*v.Z - n*v.Y);
	
	m.M12 = 2 * (v.X*v.Y - n*v.Z);
	m.M22 = q00 - q11 + q22 - q33;
	m.M32 = 2 * (v.Y*v.Z + n*v.X);
	
	m.M13 = 2 * (v.X*v.Z + n*v.Y);
	m.M23 = 2 * (v.Y*v.Z - n*v.X);
	m.M33 = q00 - q11 - q22 + q33;

	return m;
}

}