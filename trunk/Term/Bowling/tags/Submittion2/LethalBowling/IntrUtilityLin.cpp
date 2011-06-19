#include "IntrUtilityLin.h"
#include "TMath.h"

namespace Virgin
{

void LineProjection (const Vector3& rkD,
    const Vector3 akV[2], float& rfMin, float& rfMax)
{
    float afDot[2] = { rkD.Dot(akV[0]), rkD.Dot(akV[1]) };

    rfMin = afDot[0];
    rfMax = rfMin;

    if ( afDot[1] < rfMin )
        rfMin = afDot[1];
    else if ( afDot[1] > rfMax )
        rfMax = afDot[1];
}
//----------------------------------------------------------------------------

void GetLineConfiguration (const Vector3& rkAxis, 
    const Vector3 akU[2], ContactConfig& rkConfig)
{
    float afDot[2] = { rkAxis.Dot(akU[0]), rkAxis.Dot(akU[1]) };

    if ( Math::FAbs(afDot[1]-afDot[0]) < Math::EPSILON )
        rkConfig.m_kMap = m2;
    else
        rkConfig.m_kMap = m11;

    if ( afDot[0] < afDot[1] )
    {
        rkConfig.m_fMin = afDot[0];
        rkConfig.m_fMax = afDot[1];
        rkConfig.m_aiIndex[0] = 0;
        rkConfig.m_aiIndex[1] = 1;
    }
    else
    {
        rkConfig.m_fMin = afDot[1];
        rkConfig.m_fMax = afDot[0];
        rkConfig.m_aiIndex[0] = 1;
        rkConfig.m_aiIndex[1] = 0;
    }
}
//----------------------------------------------------------------------------

void FindContactSetColinearLines (const Vector3 akU[2],
    const Vector3 akV[2], int& riQuantity, Vector3* akP)
{
    // The potential intersection is initialized to the line segment U
    // and clipped against the endpoints of V

    riQuantity = 2;
    memcpy(akP,akU,2*sizeof(Vector3));

    // point 0
    Vector3 kV = akV[1] - akV[0];
    float fC = kV.Dot(akV[0]);
    ClipConvexPolygonAgainstPlane(kV,fC,riQuantity,akP);

    // point 1
    kV = -kV;
    fC = kV.Dot(akV[1]);
    ClipConvexPolygonAgainstPlane(kV,fC,riQuantity,akP);
}
//----------------------------------------------------------------------------

void FindContactSetLineThroughPlane (const Vector3 akV[2], 
    const Vector3& rkU, const Vector3& rkNormU,
    int& riQuantity, Vector3* akP)
{
    riQuantity = 1;

    float fU = rkNormU.Dot(rkU);
    float fV0 = rkNormU.Dot(akV[0]);
    float fV1 = rkNormU.Dot(akV[1]);

    // Now that there it has been reduced to a 1-dimensional problem via
    // projection, it becomes easy to find the ratio along V that V 
    // intersects with U.
    float fRatio = (fU - fV0)/(fV1 - fV0);
    akP[0] = akV[0] + fRatio*(akV[1] - akV[0]);
}
//----------------------------------------------------------------------------

void FindContactSetLinLin (const Vector3 akU[2], 
    const Vector3 akV[2], int& riQuantity, Vector3* akP)
{
    Vector3 kDirU = akU[1] - akU[0];
    Vector3 kDirV = akV[1] - akV[0];
    Vector3 kNorm = kDirU.Cross(kDirV);

    // the comparison is sin(kDirU,kDirV) < epsilon
    float fUSqrLen = kDirU.SquaredLength();
    float fVSqrLen = kDirV.SquaredLength();
    float fNSqrLen = kNorm.SquaredLength();
    if ( fNSqrLen < Math::EPSILON*fUSqrLen*fVSqrLen )
    {
        FindContactSetColinearLines(akU,akV,riQuantity,akP);
    }
    else
    {
        FindContactSetLineThroughPlane(akV,akU[0],
            kNorm.Cross(akU[1]-akU[0]),riQuantity,akP);
    }
}

}
