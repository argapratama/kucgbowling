#include "TMath.h"

#include <float.h>

namespace Virgin
{


//----------------------------------------------------------------------------

float Math::ACos (float fValue)
{
    if ( -(float)1.0 < fValue )
    {
        if ( fValue < (float)1.0 )
            return (float)acos((double)fValue);
        else
            return (float)0.0;
    }
    else
    {
        return PI;
    }
}
//----------------------------------------------------------------------------

float Math::ASin (float fValue)
{
    if ( -(float)1.0 < fValue )
    {
        if ( fValue < (float)1.0 )
            return (float)asin((double)fValue);
        else
            return -HALF_PI;
    }
    else
    {
        return HALF_PI;
    }
}
//----------------------------------------------------------------------------

float Math::ATan (float fValue)
{
    return (float)atan((double)fValue);
}
//----------------------------------------------------------------------------

float Math::ATan2 (float fY, float fX)
{
    return (float)atan2((double)fY,(double)fX);
}
//----------------------------------------------------------------------------

float Math::Ceil (float fValue)
{
    return (float)ceil((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Cos (float fValue)
{
    return (float)cos((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Exp (float fValue)
{
    return (float)exp((double)fValue);
}
//----------------------------------------------------------------------------

float Math::FAbs (float fValue)
{
    return (float)fabs((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Floor (float fValue)
{
    return (float)floor((double)fValue);
}
//----------------------------------------------------------------------------

float Math::FMod (float fX, float fY)
{
    return (float)fmod((double)fX,(double)fY);
}
//----------------------------------------------------------------------------

float Math::InvSqrt (float fValue)
{
    return (float)(1.0/sqrt((double)fValue));
}
//----------------------------------------------------------------------------

float Math::Log (float fValue)
{
    return (float)log((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Pow (float fBase, float fExponent)
{
    return (float)pow((double)fBase,(double)fExponent);
}
//----------------------------------------------------------------------------

float Math::Sin (float fValue)
{
    return (float)sin((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Sqr (float fValue)
{
    return fValue*fValue;
}
//----------------------------------------------------------------------------

float Math::Sqrt (float fValue)
{
    return (float)sqrt((double)fValue);
}
//----------------------------------------------------------------------------

float Math::Tan (float fValue)
{
    return (float)tan((double)fValue);
}
//----------------------------------------------------------------------------

int Math::Sign (int iValue)
{
    if ( iValue > 0 )
        return 1;

    if ( iValue < 0 )
        return -1;

    return 0;
}
//----------------------------------------------------------------------------

float Math::Sign (float fValue)
{
    if ( fValue > (float)0.0 )
        return (float)1.0;

    if ( fValue < (float)0.0 )
        return -(float)1.0;

    return (float)0.0;
}
//----------------------------------------------------------------------------

float Math::UnitRandom (float fSeed)
{
    if ( fSeed > (float)0.0 )
        srand((unsigned int)fSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (float)dRatio;
}
//----------------------------------------------------------------------------

float Math::SymmetricRandom (float fSeed)
{
    if ( fSeed > (float)0.0 )
        srand((unsigned int)fSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return (float)(2.0*dRatio - 1.0);
}
//----------------------------------------------------------------------------

float Math::IntervalRandom (float fMin, float fMax, float fSeed)
{
    if ( fSeed > (float)0.0 )
        srand((unsigned int)fSeed);

    double dRatio = ((double)rand())/((double)(RAND_MAX));
    return fMin+(fMax-fMin)*((float)dRatio);
}
//----------------------------------------------------------------------------

float Math::FastSin0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)7.61e-03;
    fResult *= fASqr;
    fResult -= (float)1.6605e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastSin1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = -(float)2.39e-08;
    fResult *= fASqr;
    fResult += (float)2.7526e-06;
    fResult *= fASqr;
    fResult -= (float)1.98409e-04;
    fResult *= fASqr;
    fResult += (float)8.3333315e-03;
    fResult *= fASqr;
    fResult -= (float)1.666666664e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastCos0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)3.705e-02;
    fResult *= fASqr;
    fResult -= (float)4.967e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastCos1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = -(float)2.605e-07;
    fResult *= fASqr;
    fResult += (float)2.47609e-05;
    fResult *= fASqr;
    fResult -= (float)1.3888397e-03;
    fResult *= fASqr;
    fResult += (float)4.16666418e-02;
    fResult *= fASqr;
    fResult -= (float)4.999999963e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastTan0 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)2.033e-01;
    fResult *= fASqr;
    fResult += (float)3.1755e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastTan1 (float fAngle)
{
    float fASqr = fAngle*fAngle;
    float fResult = (float)9.5168091e-03;
    fResult *= fASqr;
    fResult += (float)2.900525e-03;
    fResult *= fASqr;
    fResult += (float)2.45650893e-02;
    fResult *= fASqr;
    fResult += (float)5.33740603e-02;
    fResult *= fASqr;
    fResult += (float)1.333923995e-01;
    fResult *= fASqr;
    fResult += (float)3.333314036e-01;
    fResult *= fASqr;
    fResult += (float)1.0;
    fResult *= fAngle;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastInvSin (float fValue)
{
    float fRoot = Math::Sqrt(((float)1.0)-fValue);
    float fResult = -(float)0.0187293;
    fResult *= fValue;
    fResult += (float)0.0742610;
    fResult *= fValue;
    fResult -= (float)0.2121144;
    fResult *= fValue;
    fResult += (float)1.5707288;
    fResult = HALF_PI - fRoot*fResult;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastInvCos (float fValue)
{
    float fRoot = Math::Sqrt(((float)1.0)-fValue);
    float fResult = -(float)0.0187293;
    fResult *= fValue;
    fResult += (float)0.0742610;
    fResult *= fValue;
    fResult -= (float)0.2121144;
    fResult *= fValue;
    fResult += (float)1.5707288;
    fResult *= fRoot;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastInvTan0 (float fValue)
{
    float fVSqr = fValue*fValue;
    float fResult = (float)0.0208351;
    fResult *= fVSqr;
    fResult -= (float)0.085133;
    fResult *= fVSqr;
    fResult += (float)0.180141;
    fResult *= fVSqr;
    fResult -= (float)0.3302995;
    fResult *= fVSqr;
    fResult += (float)0.999866;
    fResult *= fValue;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastInvTan1 (float fValue)
{
    float fVSqr = fValue*fValue;
    float fResult = (float)0.0028662257;
    fResult *= fVSqr;
    fResult -= (float)0.0161657367;
    fResult *= fVSqr;
    fResult += (float)0.0429096138;
    fResult *= fVSqr;
    fResult -= (float)0.0752896400;
    fResult *= fVSqr;
    fResult += (float)0.1065626393;
    fResult *= fVSqr;
    fResult -= (float)0.1420889944;
    fResult *= fVSqr;
    fResult += (float)0.1999355085;
    fResult *= fVSqr;
    fResult -= (float)0.3333314528;
    fResult *= fVSqr;
    fResult += (float)1.0;
    fResult *= fValue;
    return fResult;
}
//----------------------------------------------------------------------------

float Math::FastInvSqrt (float fValue)
{
    // TO DO.  This routine was designed for 'float'.  Come up with an
    // equivalent one for 'double' and specialize the templates for 'float'
    // and 'double'.
    float fFValue = (float)fValue;
    float fHalf = 0.5f*fFValue;
    int i  = *(int*)&fFValue;
    i = 0x5f3759df - (i >> 1);
    fFValue = *(float*)&i;
    fFValue = fFValue*(1.5f - fHalf*fFValue*fFValue);
    return (float)fFValue;
}
//----------------------------------------------------------------------------

float Math::LogGamma (float fX)
{
    const float afCoeff[6] =
    {
        +(float)76.18009173,
        -(float)86.50532033,
        +(float)24.01409822,
        -(float)1.231739516,
        +(float)0.120858003e-02,
        -(float)0.536382000e-05
    };

    fX -= (float)1.0;
    float fTmp = fX + (float)5.5;
    fTmp -= (fX+((float)0.5))*Math::Log(fTmp);
    float fSeries = (float)1.0;
    for (int j = 0; j <= 5; j++)
    {
        fX += (float)1.0;
        fSeries += afCoeff[j]/fX;
    }
    return -fTmp + Math::Log(((float)2.50662827465)*fSeries);
}
//----------------------------------------------------------------------------

float Math::Gamma (float fX)
{
    return Math::Exp(LogGamma(fX));
}
//----------------------------------------------------------------------------

float Math::IncompleteGammaS (float fA, float fX)
{
    const int iMaxIterations = 100;
    const float fTolerance = (float)3e-07;

    if ( fX > (float)0.0 )
    {
        float fAp = fA;
        float fSum = ((float)1.0)/fA, fDel = fSum;
        for (int i = 1; i <= iMaxIterations; i++)
        {
            fAp += (float)1.0;
            fDel *= fX/fAp;
            fSum += fDel;
            if ( Math::FAbs(fDel) < Math::FAbs(fSum)*fTolerance )
            {
                float fArg = -fX+fA*Math::Log(fX)-LogGamma(fA);
                return fSum*Math::Exp(fArg);
            }
        }
    }

    if ( fX == (float)0.0 )
        return (float)0.0;

    return Math::MAX_REAL; // LogGamma not defined for x < 0
}
//----------------------------------------------------------------------------

float Math::IncompleteGammaCF (float fA, float fX)
{
    const int iMaxIterations = 100;
    const float fTolerance = (float)3e-07;

    float fA0 = (float)1.0, fA1 = fX;
    float fB0 = 0, fB1 = (float)1.0;
    float fGold = (float)0.0, fFac = (float)1.0;

    for (int i = 1; i <= iMaxIterations; i++)
    {
        float fI = (float) i;
        float fImA = fI - fA;
        fA0 = (fA1 + fA0*fImA)*fFac;
        fB0 = (fB1 + fB0*fImA)*fFac;
        float fItF = fI*fFac;
        fA1 = fX*fA0 + fItF*fA1;
        fB1 = fX*fB0 + fItF*fB1;
        if ( fA1 != (float)0.0 )
        {
            fFac = ((float)1.0)/fA1;
            float fG = fB1*fFac;
            if ( Math::FAbs((fG-fGold)/fG) < fTolerance)
            {
                float fArg = -fX + fA*Math::Log(fX) - LogGamma(fA);
                return fG*Math::Exp(fArg);
            }
            fGold = fG;
        }
    }

    return Math::MAX_REAL;  // numerical error if you get here
}
//----------------------------------------------------------------------------

float Math::IncompleteGamma (float fA, float fX)
{
    if ( fX < (float)1.0 + fA )
        return IncompleteGammaS(fA,fX);
    else
        return (float)1.0-IncompleteGammaCF(fA,fX);
}
//----------------------------------------------------------------------------

float Math::Erf (float fX)
{
    return (float)1.0-Erfc(fX);
}
//----------------------------------------------------------------------------

float Math::Erfc (float fX)
{
    const float afCoeff[10] =
    {
        -(float)1.26551223,
        +(float)1.00002368,
        +(float)0.37409196,
        +(float)0.09678418,
        -(float)0.18628806,
        +(float)0.27886807,
        -(float)1.13520398,
        +(float)1.48851587,
        -(float)0.82215223,
        +(float)0.17087277
    };

    float fZ = Math::FAbs(fX);
    float fT = ((float)1.0)/((float)1.0+((float)0.5)*fZ);
    float fSum = afCoeff[9];

    for (int i = 9; i >= 0; i--)
        fSum = fT*fSum + afCoeff[i];

    float fResult = fT*Math::Exp(-fZ*fZ + fSum);

    return ( fX >= (float)0.0 ? fResult : (float)2.0 - fResult );
}
//----------------------------------------------------------------------------

float Math::ModBessel0 (float fX)
{
    if ( fX < (float)0.0 )  // function is even
        fX = -fX;

    float fT, fResult;
    int i;

    if ( fX <= (float)3.75 )
    {
        const float afCoeff[7] =
        {
            (float)1.0000000,
            (float)3.5156229,
            (float)3.0899424,
            (float)1.2067492,
            (float)0.2659732,
            (float)0.0360768,
            (float)0.0045813
        };

        fT = fX/(float)3.75;
        float fT2 = fT*fT;
        fResult = afCoeff[6];
        for (i = 5; i >= 0; i--)
        {
            fResult *= fT2;
            fResult += afCoeff[i];
        }
        // |error| < 1.6e-07
    }
    else
    {
        const float afCoeff[9] =
        {
            +(float)0.39894228,
            +(float)0.01328592,
            +(float)0.00225319,
            -(float)0.00157565,
            +(float)0.00916281,
            -(float)0.02057706,
            +(float)0.02635537,
            -(float)0.01647633,
            +(float)0.00392377
        };

        fT = fX/(float)3.75;
        float fInvT = ((float)1.0)/fT;
        fResult = afCoeff[8];
        for (i = 7; i >= 0; i--)
        {
            fResult *= fInvT;
            fResult += afCoeff[i];
        }
        fResult *= Math::Exp(fX);
        fResult /= Math::Sqrt(fX);
        // |error| < 1.9e-07
    }

    return fResult;
}
//----------------------------------------------------------------------------

float Math::ModBessel1 (float fX)
{
    int iSign;
    if ( fX > (float)0.0 )
    {
        iSign = 1;
    }
    else if ( fX < (float)0.0 )
    {
        fX = -fX;
        iSign = -1;
    }
    else
    {
        return (float)0.0;
    }

    float fT, fResult;
    int i;

    if ( fX <= (float)3.75 )
    {
        const float afCoeff[7] =
        {
            (float)0.50000000,
            (float)0.87890549,
            (float)0.51498869,
            (float)0.15084934,
            (float)0.02658733,
            (float)0.00301532,
            (float)0.00032411
        };

        fT = fX/(float)3.75;
        float fT2 = fT*fT;
        fResult = afCoeff[6];
        for (i = 5; i >= 0; i--)
        {
            fResult *= fT2;
            fResult += afCoeff[i];
        }
        fResult *= fX;
        // |error| < 8e-09
    }
    else
    {
        const float afCoeff[9] =
        {
            +(float)0.39894228,
            -(float)0.03988024,
            -(float)0.00362018,
            +(float)0.00163801,
            -(float)0.01031555,
            +(float)0.02282967,
            -(float)0.02895312,
            +(float)0.01787654,
            -(float)0.00420059
        };

        fT = fX/(float)3.75;
        float fInvT = ((float)1.0)/fT;
        fResult = afCoeff[8];
        for (i = 7; i >= 0; i--)
        {
            fResult *= fInvT;
            fResult += afCoeff[i];
        }
        fResult *= Math::Exp(fX);
        fResult /= Math::Sqrt(fX);
        // |error| < 2.2e-07
    }

    fResult *= iSign;
    return fResult;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
const float Math::EPSILON = FLT_EPSILON;
const float Math::MAX_REAL = FLT_MAX;
const float Math::PI = (float)(4.0*atan(1.0));
const float Math::TWO_PI = 2.0f*Math::PI;
const float Math::HALF_PI = 0.5f*Math::PI;
const float Math::INV_PI = 1.0f/Math::PI;
const float Math::INV_TWO_PI = 1.0f/Math::TWO_PI;
const float Math::DEG_TO_RAD = Math::PI/180.0f;
const float Math::RAD_TO_DEG = 180.0f/Math::PI;

}

