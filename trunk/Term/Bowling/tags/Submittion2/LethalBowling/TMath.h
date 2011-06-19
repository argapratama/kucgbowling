#pragma once

#include <math.h>

namespace Virgin
{

class Math
{
public:
    // Wrappers to hide implementations of functions.  The ACos and ASin
    // functions clamp the input argument to [-1,1] to avoid NaN issues
    // when the input is slightly larger than 1 or slightly smaller than -1.
    // Other functions have the potential for using a fast and approximate
    // algorithm rather than calling the standard math library functions.
    static float ACos (float fValue);
    static float ASin (float fValue);
    static float ATan (float fValue);
    static float ATan2 (float fY, float fX);
    static float Ceil (float fValue);
    static float Cos (float fValue);
    static float Exp (float fValue);
    static float FAbs (float fValue);
    static float Floor (float fValue);
    static float FMod (float fX, float fY);
    static float InvSqrt (float fValue);
    static float Log (float fValue);
    static float Pow (float fBase, float fExponent);
    static float Sin (float fValue);
    static float Sqr (float fValue);
    static float Sqrt (float fValue);
    static float Tan (float fValue);

    // Return -1 if the input is negative, 0 if the input is zero, and +1
    // if the input is positive.
    static int Sign (int iValue);
    static float Sign (float fValue);

    // Generate a random number in [0,1).  The random number generator may
    // be seeded by a first call to UnitRandom with a positive seed.
    static float UnitRandom (float fSeed = (float)0.0);

    // Generate a random number in [-1,1).  The random number generator may
    // be seeded by a first call to SymmetricRandom with a positive seed.
    static float SymmetricRandom (float fSeed = (float)0.0);

    // Generate a random number in [min,max).  The random number generator may
    // be seeded by a first call to IntervalRandom with a positive seed.
    static float IntervalRandom (float fMin, float fMax, float fSeed = (float)0.0);

    // Fast evaluation of sin(angle) by polynomial approximations.  The angle
    // must be in [0,pi/2].  The maximum absolute error is about 1.7e-04 for
    // FastSin0 and about 2.3e-09 for FastSin1.  The speed up is about 2 for
    // FastSin0 and about 1.5 for FastSin1.
    static float FastSin0 (float fAngle);
    static float FastSin1 (float fAngle);

    // Fast evaluation of cos(angle) by polynomial approximations.  The angle
    // must be in [0,pi/2].  The maximum absolute error is about 1.2e-03 for
    // FastCos0 and about 2.3e-09 for FastCos1.  The speed up is about 2 for
    // FastCos0 and about 1.5 for FastCos1.
    static float FastCos0 (float fAngle);
    static float FastCos1 (float fAngle);

    // Fast evaluation of tan(angle) by polynomial approximations.  The angle
    // must be in [0,pi/4].  The maximum absolute error is about 8.1e-04 for
    // FastTan0 and about 1.9e-08 for FastTan1.  The speed up is about 2.5 for
    // FastTan0 and about 1.75 for FastTan1.
    static float FastTan0 (float fAngle);
    static float FastTan1 (float fAngle);

    // Fast evaluation of asin(value) by a sqrt times a polynomial.  The value
    // must be in [0,1].  The maximum absolute error is about 6.8e-05 and the
    // speed up is about 2.5.
    static float FastInvSin (float fValue);

    // Fast evaluation of acos(value) by a sqrt times a polynomial.  The value
    // must be in [0,1].  The maximum absolute error is about 6.8e-05 and the
    // speed up is about 2.5.
    static float FastInvCos (float fValue);

    // Fast evaluation of atan(value) by polynomial approximations.  The value
    // must be in [-1,1].  The maximum absolute error is about 1.2e-05 for
    // FastInvTan0 and about 1.43-08 for FastInvTan1.  The speed up is about
    // 2.2 for FastInvTan0 and about 1.5 for FastInvTan1.
    static float FastInvTan0 (float fValue);
    static float FastInvTan1 (float fValue);

    // A fast approximation to 1/sqrt.
    static float FastInvSqrt (float fValue);

    // gamma and related functions
    static float LogGamma (float fX);
    static float Gamma (float fX);
    static float IncompleteGamma (float fA, float fX);

    // error functions
    static float Erf (float fX);   // polynomial approximation
    static float Erfc (float fX);  // erfc(x) = 1-erf(x)

    // modified Bessel functions of order 0 and 1
    static float ModBessel0 (float fX);
    static float ModBessel1 (float fX);

    // common constants
    static const float EPSILON;
    static const float MAX_REAL;
    static const float PI;
    static const float TWO_PI;
    static const float HALF_PI;
    static const float INV_PI;
    static const float INV_TWO_PI;
    static const float DEG_TO_RAD;
    static const float RAD_TO_DEG;

    static double DegreesToRadians(double degrees)
    {
        return degrees / 57.29578;
    }

    static double RadiansToDegrees(double radians)
    {
        return radians * 57.29578;
    }

    template <typename T>
    static T Min(T value1, T value2)
    {
        return (value1 > value2) ? value2 : value1;
    }

    template <typename T>
    static T Max(T value1, T value2)
    {
        return (value1 > value2) ? value1 : value2;
    }



protected:
    // series form (used when fX < 1+fA)
    static float IncompleteGammaS (float fA, float fX);

    // continued fraction form (used when fX >= 1+fA)
    static float IncompleteGammaCF (float fA, float fX);
};


}
