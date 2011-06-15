#include "Quaternion.h"
#include "TMath.h"

namespace Virgin
{

const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion ()
{
    // the object is uninitialized
}
//----------------------------------------------------------------------------

Quaternion::Quaternion (float fW, float fX, float fY, float fZ)
{
    m_afTuple[0] = fW;
    m_afTuple[1] = fX;
    m_afTuple[2] = fY;
    m_afTuple[3] = fZ;
}
//----------------------------------------------------------------------------

Quaternion::Quaternion (const Quaternion& rkQ)
{
    memcpy(m_afTuple,rkQ.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------

Quaternion::Quaternion (const Matrix3& rkRot)
{
    FromRotationMatrix(rkRot);
}
//----------------------------------------------------------------------------

Quaternion::Quaternion (const Vector3& rkAxis, float fAngle)
{
    FromAxisAngle(rkAxis,fAngle);
}
//----------------------------------------------------------------------------

Quaternion::Quaternion (const Vector3 akRotColumn[3])
{
    FromRotationMatrix(akRotColumn);
}
//----------------------------------------------------------------------------

Quaternion::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

Quaternion::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------

float Quaternion::operator[] (int i) const
{
    //assert( 0 <= i && i < 4 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

float& Quaternion::operator[] (int i)
{
    //assert( 0 <= i && i < 4 );
    return m_afTuple[i];
}
//----------------------------------------------------------------------------

float Quaternion::W () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

float& Quaternion::W ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------

float Quaternion::X () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float& Quaternion::X ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------

float Quaternion::Y () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float& Quaternion::Y ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------

float Quaternion::Z () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

float& Quaternion::Z ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------

Quaternion& Quaternion::operator= (const Quaternion& rkQ)
{
    memcpy(m_afTuple,rkQ.m_afTuple,4*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

bool Quaternion::operator== (const Quaternion& rkQ) const
{
    for (int i = 0; i < 4; i++)
    {
        if ( m_afTuple[i] != rkQ.m_afTuple[i] )
            return false;
    }
    return true;
}
//----------------------------------------------------------------------------

bool Quaternion::operator!= (const Quaternion& rkQ) const
{
    return !operator==(rkQ);
}
//----------------------------------------------------------------------------

int Quaternion::CompareArrays (const Quaternion& rkQ) const
{
    for (int i = 0; i < 4; i++)
    {
        unsigned int uiTest0 = *(unsigned int*)&m_afTuple[i];
        unsigned int uiTest1 = *(unsigned int*)&rkQ.m_afTuple[i];
        if ( uiTest0 < uiTest1 )
            return -1;
        if ( uiTest0 > uiTest1 )
            return +1;
    }
    return 0;
}
//----------------------------------------------------------------------------

bool Quaternion::operator< (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) < 0;
}
//----------------------------------------------------------------------------

bool Quaternion::operator<= (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) <= 0;
}
//----------------------------------------------------------------------------

bool Quaternion::operator> (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) > 0;
}
//----------------------------------------------------------------------------

bool Quaternion::operator>= (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) >= 0;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
    Quaternion kSum;
    for (int i = 0; i < 4; i++)
        kSum.m_afTuple[i] = m_afTuple[i] + rkQ.m_afTuple[i];
    return kSum;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
    Quaternion kDiff;
    for (int i = 0; i < 4; i++)
        kDiff.m_afTuple[i] = m_afTuple[i] - rkQ.m_afTuple[i];
    return kDiff;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    Quaternion kProd;

    kProd.m_afTuple[0] =
        m_afTuple[0]*rkQ.m_afTuple[0] -
        m_afTuple[1]*rkQ.m_afTuple[1] -
        m_afTuple[2]*rkQ.m_afTuple[2] -
        m_afTuple[3]*rkQ.m_afTuple[3];

    kProd.m_afTuple[1] =
        m_afTuple[0]*rkQ.m_afTuple[1] +
        m_afTuple[1]*rkQ.m_afTuple[0] +
        m_afTuple[2]*rkQ.m_afTuple[3] -
        m_afTuple[3]*rkQ.m_afTuple[2];

    kProd.m_afTuple[2] =
        m_afTuple[0]*rkQ.m_afTuple[2] +
        m_afTuple[2]*rkQ.m_afTuple[0] +
        m_afTuple[3]*rkQ.m_afTuple[1] -
        m_afTuple[1]*rkQ.m_afTuple[3];

    kProd.m_afTuple[3] =
        m_afTuple[0]*rkQ.m_afTuple[3] +
        m_afTuple[3]*rkQ.m_afTuple[0] +
        m_afTuple[1]*rkQ.m_afTuple[2] -
        m_afTuple[2]*rkQ.m_afTuple[1];

    return kProd;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator* (float fScalar) const
{
    Quaternion kProd;
    for (int i = 0; i < 4; i++)
        kProd.m_afTuple[i] = fScalar*m_afTuple[i];
    return kProd;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator/ (float fScalar) const
{
    Quaternion kQuot;
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
            kQuot.m_afTuple[i] = fInvScalar*m_afTuple[i];
    }
    else
    {
        for (i = 0; i < 4; i++)
            kQuot.m_afTuple[i] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::operator- () const
{
    Quaternion kNeg;
    for (int i = 0; i < 4; i++)
        kNeg.m_afTuple[i] = -m_afTuple[i];
    return kNeg;
}
//----------------------------------------------------------------------------

Quaternion operator* (float fScalar, const Quaternion& rkQ)
{
    Quaternion kProd;
    for (int i = 0; i < 4; i++)
        kProd[i] = fScalar*rkQ[i];
    return kProd;
}
//----------------------------------------------------------------------------

Quaternion& Quaternion::operator+= (const Quaternion& rkQ)
{
    for (int i = 0; i < 4; i++)
        m_afTuple[i] += rkQ.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------

Quaternion& Quaternion::operator-= (const Quaternion& rkQ)
{
    for (int i = 0; i < 4; i++)
        m_afTuple[i] -= rkQ.m_afTuple[i];
    return *this;
}
//----------------------------------------------------------------------------

Quaternion& Quaternion::operator*= (float fScalar)
{
    for (int i = 0; i < 4; i++)
        m_afTuple[i] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------

Quaternion& Quaternion::operator/= (float fScalar)
{
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
            m_afTuple[i] *= fInvScalar;
    }
    else
    {
        for (i = 0; i < 4; i++)
            m_afTuple[i] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------

void Quaternion::FromRotationMatrix (const Matrix3& rkRot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternion Calculus and Fast Animation".

    float fTrace = rkRot(0,0) + rkRot(1,1) + rkRot(2,2);
    float fRoot;

    if ( fTrace > (float)0.0 )
    {
        // |w| > 1/2, may as well choose w > 1/2
        fRoot = Math::Sqrt(fTrace + (float)1.0);  // 2w
        m_afTuple[0] = ((float)0.5)*fRoot;
        fRoot = ((float)0.5)/fRoot;  // 1/(4w)
        m_afTuple[1] = (rkRot(2,1)-rkRot(1,2))*fRoot;
        m_afTuple[2] = (rkRot(0,2)-rkRot(2,0))*fRoot;
        m_afTuple[3] = (rkRot(1,0)-rkRot(0,1))*fRoot;
    }
    else
    {
        // |w| <= 1/2
        int i = 0;
        if ( rkRot(1,1) > rkRot(0,0) )
            i = 1;
        if ( rkRot(2,2) > rkRot(i,i) )
            i = 2;
        int j = ms_iNext[i];
        int k = ms_iNext[j];

        fRoot = Math::Sqrt(rkRot(i,i)-rkRot(j,j)-rkRot(k,k)+(float)1.0);
        float* apfQuat[3] = { &m_afTuple[1], &m_afTuple[2], &m_afTuple[3] };
        *apfQuat[i] = ((float)0.5)*fRoot;
        fRoot = ((float)0.5)/fRoot;
        m_afTuple[0] = (rkRot(k,j)-rkRot(j,k))*fRoot;
        *apfQuat[j] = (rkRot(j,i)+rkRot(i,j))*fRoot;
        *apfQuat[k] = (rkRot(k,i)+rkRot(i,k))*fRoot;
    }
}
//----------------------------------------------------------------------------

void Quaternion::ToRotationMatrix (Matrix3& rkRot) const
{
    float fTx  = ((float)2.0)*m_afTuple[1];
    float fTy  = ((float)2.0)*m_afTuple[2];
    float fTz  = ((float)2.0)*m_afTuple[3];
    float fTwx = fTx*m_afTuple[0];
    float fTwy = fTy*m_afTuple[0];
    float fTwz = fTz*m_afTuple[0];
    float fTxx = fTx*m_afTuple[1];
    float fTxy = fTy*m_afTuple[1];
    float fTxz = fTz*m_afTuple[1];
    float fTyy = fTy*m_afTuple[2];
    float fTyz = fTz*m_afTuple[2];
    float fTzz = fTz*m_afTuple[3];

    rkRot(0,0) = ((float)1.0)-(fTyy+fTzz);
    rkRot(0,1) = fTxy-fTwz;
    rkRot(0,2) = fTxz+fTwy;
    rkRot(1,0) = fTxy+fTwz;
    rkRot(1,1) = ((float)1.0)-(fTxx+fTzz);
    rkRot(1,2) = fTyz-fTwx;
    rkRot(2,0) = fTxz-fTwy;
    rkRot(2,1) = fTyz+fTwx;
    rkRot(2,2) = ((float)1.0)-(fTxx+fTyy);
}
//----------------------------------------------------------------------------

void Quaternion::FromRotationMatrix (const Vector3 akRotColumn[3])
{
    Matrix3 kRot;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        kRot(0,iCol) = akRotColumn[iCol][0];
        kRot(1,iCol) = akRotColumn[iCol][1];
        kRot(2,iCol) = akRotColumn[iCol][2];
    }
    FromRotationMatrix(kRot);
}
//----------------------------------------------------------------------------

void Quaternion::ToRotationMatrix (Vector3 akRotColumn[3]) const
{
    Matrix3 kRot;
    ToRotationMatrix(kRot);
    for (int iCol = 0; iCol < 3; iCol++)
    {
        akRotColumn[iCol][0] = kRot(0,iCol);
        akRotColumn[iCol][1] = kRot(1,iCol);
        akRotColumn[iCol][2] = kRot(2,iCol);
    }
}
//----------------------------------------------------------------------------

void Quaternion::FromAxisAngle (const Vector3& rkAxis,
    float fAngle)
{
    // //assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    float fHalfAngle = ((float)0.5)*fAngle;
    float fSin = Math::Sin(fHalfAngle);
    m_afTuple[0] = Math::Cos(fHalfAngle);
    m_afTuple[1] = fSin*rkAxis[0];
    m_afTuple[2] = fSin*rkAxis[1];
    m_afTuple[3] = fSin*rkAxis[2];
}
//----------------------------------------------------------------------------

void Quaternion::ToAxisAngle (Vector3& rkAxis, float& rfAngle)
    const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    float fSqrLength = m_afTuple[1]*m_afTuple[1] + m_afTuple[2]*m_afTuple[2]
        + m_afTuple[3]*m_afTuple[3];
    if ( fSqrLength > Math::EPSILON )
    {
        rfAngle = ((float)2.0)*Math::ACos(m_afTuple[0]);
        float fInvLength = Math::InvSqrt(fSqrLength);
        rkAxis[0] = m_afTuple[1]*fInvLength;
        rkAxis[1] = m_afTuple[2]*fInvLength;
        rkAxis[2] = m_afTuple[3]*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = (float)0.0;
        rkAxis[0] = (float)1.0;
        rkAxis[1] = (float)0.0;
        rkAxis[2] = (float)0.0;
    }
}
//----------------------------------------------------------------------------

float Quaternion::Dot (const Quaternion& rkQ) const
{
    float fDot = (float)0.0;
    for (int i = 0; i < 4; i++)
        fDot += m_afTuple[i]*rkQ.m_afTuple[i];
    return fDot;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Inverse () const
{
    Quaternion kInverse;

    float fNorm = (float)0.0;
    int i;
    for (i = 0; i < 4; i++)
        fNorm += m_afTuple[i]*m_afTuple[i];

    if ( fNorm > (float)0.0 )
    {
        float fInvNorm = ((float)1.0)/fNorm;
        kInverse.m_afTuple[0] = m_afTuple[0]*fInvNorm;
        kInverse.m_afTuple[1] = -m_afTuple[1]*fInvNorm;
        kInverse.m_afTuple[2] = -m_afTuple[2]*fInvNorm;
        kInverse.m_afTuple[3] = -m_afTuple[3]*fInvNorm;
    }
    else
    {
        // return an invalid result to flag the error
        for (i = 0; i < 4; i++)
            kInverse.m_afTuple[i] = (float)0.0;
    }

    return kInverse;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Conjugate () const
{
    // //assert:  'this' is unit length
    return Quaternion(m_afTuple[0],-m_afTuple[1],-m_afTuple[2],-m_afTuple[3]);
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Exp () const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    Quaternion kResult;

    float fAngle = Math::Sqrt(m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] + m_afTuple[3]*m_afTuple[3]);

    float fSin = Math::Sin(fAngle);
    kResult.m_afTuple[0] = Math::Cos(fAngle);

    int i;

    if ( Math::FAbs(fSin) >= Math::EPSILON )
    {
        float fCoeff = fSin/fAngle;
        for (i = 1; i <= 3; i++)
            kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
    }
    else
    {
        for (i = 1; i <= 3; i++)
            kResult.m_afTuple[i] = m_afTuple[i];
    }

    return kResult;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Log () const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    Quaternion kResult;
    kResult.m_afTuple[0] = (float)0.0;

    int i;

    if ( Math::FAbs(m_afTuple[0]) < (float)1.0 )
    {
        float fAngle = Math::ACos(m_afTuple[0]);
        float fSin = Math::Sin(fAngle);
        if ( Math::FAbs(fSin) >= Math::EPSILON )
        {
            float fCoeff = fAngle/fSin;
            for (i = 1; i <= 3; i++)
                kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
            return kResult;
        }
    }

    for (i = 1; i <= 3; i++)
        kResult.m_afTuple[i] = m_afTuple[i];
    return kResult;
}
//----------------------------------------------------------------------------

Vector3 Quaternion::operator* (const Vector3& rkVector)
    const
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in Quaternion::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    Matrix3 kRot;
    ToRotationMatrix(kRot);
    return kRot*rkVector;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Slerp (float fT, const Quaternion& rkP,
    const Quaternion& rkQ)
{
    float fCos = rkP.Dot(rkQ);
    float fAngle = Math::ACos(fCos);

    if ( Math::FAbs(fAngle) < Math::EPSILON )
        return rkP;

    float fSin = Math::Sin(fAngle);
    float fInvSin = ((float)1.0)/fSin;
    float fCoeff0 = Math::Sin((((float)1.0)-fT)*fAngle)*fInvSin;
    float fCoeff1 = Math::Sin(fT*fAngle)*fInvSin;
    return fCoeff0*rkP + fCoeff1*rkQ;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::SlerpExtraSpins (float fT,
    const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins)
{
    float fCos = rkP.Dot(rkQ);
    float fAngle = Math::ACos(fCos);

    if ( Math::FAbs(fAngle) < Math::EPSILON )
        return rkP;

    float fSin = Math::Sin(fAngle);
    float fPhase = Math::PI*iExtraSpins*fT;
    float fInvSin = ((float)1.0)/fSin;
    float fCoeff0 = Math::Sin((((float)1.0)-fT)*fAngle-fPhase)*fInvSin;
    float fCoeff1 = Math::Sin(fT*fAngle + fPhase)*fInvSin;
    return fCoeff0*rkP + fCoeff1*rkQ;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::GetIntermediate (const Quaternion& rkQ0,
    const Quaternion& rkQ1, const Quaternion& rkQ2)
{
    // //assert:  Q0, Q1, Q2 all unit-length
    Quaternion kQ1Inv = rkQ1.Conjugate();
    Quaternion kP0 = kQ1Inv*rkQ0;
    Quaternion kP2 = kQ1Inv*rkQ2;
    Quaternion kArg = -((float)0.25)*(kP0.Log()+kP2.Log());
    Quaternion kA = rkQ1*kArg.Exp();
    return kA;
}
//----------------------------------------------------------------------------

Quaternion Quaternion::Squad (float fT, const Quaternion& rkQ0,
    const Quaternion& rkA0, const Quaternion& rkA1, const Quaternion& rkQ1)
{
    float fSlerpT = ((float)2.0)*fT*(((float)1.0)-fT);
    Quaternion kSlerpP = Slerp(fT,rkQ0,rkQ1);
    Quaternion kSlerpQ = Slerp(fT,rkA0,rkA1);
    return Slerp(fSlerpT,kSlerpP,kSlerpQ);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
int Quaternion::ms_iNext[3] = { 1, 2, 0 };

}

