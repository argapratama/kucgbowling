#include "Matrix.h"

#include "TMath.h"

namespace Virgin
{


//----------------------------------------------------------------------------

Matrix::Matrix ()
{
    // the matrix is uninitialized
}
//----------------------------------------------------------------------------

Matrix::Matrix (bool bZero)
{
    memset(m_afEntry,0,3*3*sizeof(float));

    if ( !bZero )
    {
        for (int i = 0; i < 3; i++)
            m_afEntry[I(i,i)] = (float)1.0;
    }
}
//----------------------------------------------------------------------------

Matrix::Matrix (const Matrix& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,3*3*sizeof(float));
}
//----------------------------------------------------------------------------

void Matrix::MakeZero ()
{
    memset(m_afEntry,0,3*3*sizeof(float));
}
//----------------------------------------------------------------------------

void Matrix::MakeIdentity ()
{
    memset(m_afEntry,0,3*3*sizeof(float));
    for (int i = 0; i < 3; i++)
        m_afEntry[I(i,i)] = (float)1.0;
}
//----------------------------------------------------------------------------

void Matrix::MakeDiagonal (const float* afDiag)
{
    memset(m_afEntry,0,3*3*sizeof(float));
    for (int i = 0; i < 3; i++)
        m_afEntry[I(i,i)] = afDiag[i];
}
//----------------------------------------------------------------------------

Matrix::operator const float* () const
{
    return m_afEntry;
}
//----------------------------------------------------------------------------

Matrix::operator float* ()
{
    return m_afEntry;
}
//----------------------------------------------------------------------------

const float* Matrix::operator[] (int iRow) const
{
    //assert( 0 <= iRow && iRow < 3 );
    return &m_afEntry[3*iRow];
}
//----------------------------------------------------------------------------

float* Matrix::operator[] (int iRow)
{
    //assert( 0 <= iRow && iRow < 3 );
    return &m_afEntry[3*iRow];
}
//----------------------------------------------------------------------------

float Matrix::operator() (int iRow, int iCol) const
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------

float& Matrix::operator() (int iRow, int iCol)
{
    return m_afEntry[I(iRow,iCol)];
}
//----------------------------------------------------------------------------

void Matrix::SetRow (int iRow, const Vector3& rkV)
{
    //assert( 0 <= iRow && iRow < 3 );
    for (int iCol = 0, i = 3*iRow; iCol < 3; iCol++, i++)
        m_afEntry[i] = rkV[iCol];
}
//----------------------------------------------------------------------------

Vector3 Matrix::GetRow (int iRow) const
{
    //assert( 0 <= iRow && iRow < 3 );
    Vector3 kV;
    for (int iCol = 0, i = 3*iRow; iCol < 3; iCol++, i++)
        kV[iCol] = m_afEntry[i];
    return kV;
}
//----------------------------------------------------------------------------

void Matrix::SetColumn (int iCol, const Vector3& rkV)
{
    //assert( 0 <= iCol && iCol < 3 );
    for (int iRow = 0, i = iCol; iRow < 3; iRow++, i += 3)
        m_afEntry[i] = rkV[iRow];
}
//----------------------------------------------------------------------------

Vector3 Matrix::GetColumn (int iCol) const
{
    //assert( 0 <= iCol && iCol < 3 );
    Vector3 kV;
    for (int iRow = 0, i = iCol; iRow < 3; iRow++, i += 3)
        kV[iRow] = m_afEntry[i];
    return kV;
}
//----------------------------------------------------------------------------

void Matrix::GetColumnMajor (float* afCMajor) const
{
    for (int iRow = 0, i = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
            afCMajor[i++] = m_afEntry[I(iCol,iRow)];
    }
}
//----------------------------------------------------------------------------

Matrix& Matrix::operator= (const Matrix& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,3*3*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

bool Matrix::operator== (const Matrix& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,3*3*sizeof(float)) == 0;
}
//----------------------------------------------------------------------------

bool Matrix::operator!= (const Matrix& rkM) const
{
    return memcmp(m_afEntry,rkM.m_afEntry,3*3*sizeof(float)) != 0;
}
//----------------------------------------------------------------------------

int Matrix::CompareArrays (const Matrix& rkM) const
{
    for (int i = 0; i < 3*3; i++)
    {
        unsigned int uiTest0 = *(unsigned int*)&m_afEntry[i];
        unsigned int uiTest1 = *(unsigned int*)&rkM.m_afEntry[i];
        if ( uiTest0 < uiTest1 )
            return -1;
        if ( uiTest0 > uiTest1 )
            return +1;
    }
    return 0;
}
//----------------------------------------------------------------------------

bool Matrix::operator<  (const Matrix& rkM) const
{
    return CompareArrays(rkM) < 0;
}
//----------------------------------------------------------------------------

bool Matrix::operator<= (const Matrix& rkM) const
{
    return CompareArrays(rkM) <= 0;
}
//----------------------------------------------------------------------------

bool Matrix::operator>  (const Matrix& rkM) const
{
    return CompareArrays(rkM) > 0;
}
//----------------------------------------------------------------------------

bool Matrix::operator>= (const Matrix& rkM) const
{
    return CompareArrays(rkM) >= 0;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator+ (const Matrix& rkM) const
{
    Matrix kSum;
    for (int i = 0; i < 3*3; i++)
        kSum.m_afEntry[i] = m_afEntry[i] + rkM.m_afEntry[i];
    return kSum;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator- (const Matrix& rkM) const
{
    Matrix kDiff;
    for (int i = 0; i < 3*3; i++)
        kDiff.m_afEntry[i] = m_afEntry[i] - rkM.m_afEntry[i];
    return kDiff;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator* (const Matrix& rkM) const
{
    Matrix kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0f;
            for (int iMid = 0; iMid < 3; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator* (float fScalar) const
{
    Matrix kProd;
    for (int i = 0; i < 3*3; i++)
        kProd.m_afEntry[i] = fScalar*m_afEntry[i];
    return kProd;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator/ (float fScalar) const
{
    Matrix kQuot;
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 3*3; i++)
            kQuot.m_afEntry[i] = fInvScalar*m_afEntry[i];
    }
    else
    {
        for (i = 0; i < 3*3; i++)
            kQuot.m_afEntry[i] = Math::MAX_REAL;
    }

    return kQuot;
}
//----------------------------------------------------------------------------

Matrix Matrix::operator- () const
{
    Matrix kNeg;
    for (int i = 0; i < 3*3; i++)
        kNeg.m_afEntry[i] = -m_afEntry[i];
    return kNeg;
}
//----------------------------------------------------------------------------

Matrix operator* (float fScalar, const Matrix& rkM)
{
    Matrix kProd;
    const float* afMEntry = rkM;
    float* afPEntry = kProd;
    for (int i = 0; i < 3*3; i++)
        afPEntry[i] = fScalar*afMEntry[i];
    return kProd;
}
//----------------------------------------------------------------------------

Matrix& Matrix::operator+= (const Matrix& rkM)
{
    for (int i = 0; i < 3*3; i++)
        m_afEntry[i] += rkM.m_afEntry[i];
    return *this;
}
//----------------------------------------------------------------------------

Matrix& Matrix::operator-= (const Matrix& rkM)
{
    for (int i = 0; i < 3*3; i++)
        m_afEntry[i] -= rkM.m_afEntry[i];
    return *this;
}
//----------------------------------------------------------------------------

Matrix& Matrix::operator*= (float fScalar)
{
    for (int i = 0; i < 3*3; i++)
        m_afEntry[i] *= fScalar;
    return *this;
}
//----------------------------------------------------------------------------

Matrix& Matrix::operator/= (float fScalar)
{
    int i;

    if ( fScalar != (float)0.0 )
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 3*3; i++)
            m_afEntry[i] *= fInvScalar;
    }
    else
    {
        for (i = 0; i < 3*3; i++)
            m_afEntry[i] = Math::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------

Matrix Matrix::Transpose () const
{
    Matrix kTranspose;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
            kTranspose.m_afEntry[I(iRow,iCol)] = m_afEntry[I(iCol,iRow)];
    }
    return kTranspose;
}
//----------------------------------------------------------------------------

Matrix Matrix::TransposeTimes (const Matrix& rkM) const
{
    // P = A^T*B, P[r][c] = sum_m A[m][r]*B[m][c]
    Matrix kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 3; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iMid,iRow)]*rkM.m_afEntry[I(iMid,iCol)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

Matrix Matrix::TimesTranspose (const Matrix& rkM) const
{
    // P = A*B^T, P[r][c] = sum_m A[r][m]*B[c][m]
    Matrix kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        for (int iCol = 0; iCol < 3; iCol++)
        {
            int i = I(iRow,iCol);
            kProd.m_afEntry[i] = (float)0.0;
            for (int iMid = 0; iMid < 3; iMid++)
            {
                kProd.m_afEntry[i] +=
                    m_afEntry[I(iRow,iMid)]*rkM.m_afEntry[I(iCol,iRow)];
            }
        }
    }
    return kProd;
}
//----------------------------------------------------------------------------

Vector3 Matrix::operator* (const Vector3& rkV) const
{
    Vector3 kProd;
    for (int iRow = 0; iRow < 3; iRow++)
    {
        kProd[iRow] = (float)0.0;
        for (int iCol = 0; iCol < 3; iCol++)
            kProd[iRow] += m_afEntry[I(iRow,iCol)]*rkV[iCol];
            
    }
    return kProd;
}
//----------------------------------------------------------------------------

Vector3 Virgin::operator* (const Vector3& rkV,
    const Matrix& rkM)
{
    Vector3 kProd;
    const float* afMEntry = rkM;
    float* afPEntry = kProd;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        afPEntry[iCol] = (float)0.0;
        for (int iRow = 0; iRow < 3; iRow++)
            afPEntry[iCol] += rkV[iRow]*afMEntry[iCol + 3*iRow];
            
    }
    return kProd;
}
//----------------------------------------------------------------------------

float Matrix::QForm (const Vector3& rkU,
    const Vector3& rkV) const
{
    return rkU.Dot((*this)*rkV);
}
//----------------------------------------------------------------------------

int Matrix::I (int iRow, int iCol)
{
    //assert( 0 <= iRow && iRow < 3 && 0 <= iCol && iCol < 3 );
    return iCol + 3*iRow;
}
//----------------------------------------------------------------------------








//----------------------------------------------------------------------------

Matrix3::Matrix3 ()
{
    // the matrix is uninitialized
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Matrix3& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,9*sizeof(float));
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Matrix& rkM)
{
    memcpy(m_afEntry,(const float*)rkM,9*sizeof(float));
}
//----------------------------------------------------------------------------

Matrix3& Matrix3::operator= (const Matrix3& rkM)
{
    memcpy(m_afEntry,rkM.m_afEntry,9*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

Matrix3& Matrix3::operator= (const Matrix& rkM)
{
    memcpy(m_afEntry,(const float*)rkM,9*sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (float fM00, float fM01, float fM02, float fM10,
    float fM11, float fM12, float fM20, float fM21, float fM22)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = fM01;
    m_afEntry[2] = fM02;
    m_afEntry[3] = fM10;
    m_afEntry[4] = fM11;
    m_afEntry[5] = fM12;
    m_afEntry[6] = fM20;
    m_afEntry[7] = fM21;
    m_afEntry[8] = fM22;
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const float afEntry[9], bool bRowMajor)
{
    if ( bRowMajor )
    {
        memcpy(m_afEntry,afEntry,9*sizeof(float));
    }
    else
    {
        m_afEntry[0] = afEntry[0];
        m_afEntry[1] = afEntry[3];
        m_afEntry[2] = afEntry[6];
        m_afEntry[3] = afEntry[1];
        m_afEntry[4] = afEntry[4];
        m_afEntry[5] = afEntry[7];
        m_afEntry[6] = afEntry[2];
        m_afEntry[7] = afEntry[5];
        m_afEntry[8] = afEntry[8];
    }
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Vector3& rkU,
    const Vector3& rkV, const Vector3& rkW, bool bColumns)
{
    if ( bColumns )
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkV[0];
        m_afEntry[2] = rkW[0];
        m_afEntry[3] = rkU[1];
        m_afEntry[4] = rkV[1];
        m_afEntry[5] = rkW[1];
        m_afEntry[6] = rkU[2];
        m_afEntry[7] = rkV[2];
        m_afEntry[8] = rkW[2];
    }
    else
    {
        m_afEntry[0] = rkU[0];
        m_afEntry[1] = rkU[1];
        m_afEntry[2] = rkU[2];
        m_afEntry[3] = rkV[0];
        m_afEntry[4] = rkV[1];
        m_afEntry[5] = rkV[2];
        m_afEntry[6] = rkW[0];
        m_afEntry[7] = rkW[1];
        m_afEntry[8] = rkW[2];
    }
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Vector3* akV, bool bColumns)
{
    if ( bColumns )
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[1][0];
        m_afEntry[2] = akV[2][0];
        m_afEntry[3] = akV[0][1];
        m_afEntry[4] = akV[1][1];
        m_afEntry[5] = akV[2][1];
        m_afEntry[6] = akV[0][2];
        m_afEntry[7] = akV[1][2];
        m_afEntry[8] = akV[2][2];
    }
    else
    {
        m_afEntry[0] = akV[0][0];
        m_afEntry[1] = akV[0][1];
        m_afEntry[2] = akV[0][2];
        m_afEntry[3] = akV[1][0];
        m_afEntry[4] = akV[1][1];
        m_afEntry[5] = akV[1][2];
        m_afEntry[6] = akV[2][0];
        m_afEntry[7] = akV[2][1];
        m_afEntry[8] = akV[2][2];
    }
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Vector3& rkU,
    const Vector3& rkV)
{
    MakeTensorProduct(rkU,rkV);
}
//----------------------------------------------------------------------------

void Matrix3::MakeTensorProduct (const Vector3& rkU,
    const Vector3& rkV)
{
    m_afEntry[0] = rkU[0]*rkV[0];
    m_afEntry[1] = rkU[0]*rkV[1];
    m_afEntry[2] = rkU[0]*rkV[2];
    m_afEntry[3] = rkU[1]*rkV[0];
    m_afEntry[4] = rkU[1]*rkV[1];
    m_afEntry[5] = rkU[1]*rkV[2];
    m_afEntry[6] = rkU[2]*rkV[0];
    m_afEntry[7] = rkU[2]*rkV[1];
    m_afEntry[8] = rkU[2]*rkV[2];
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (float fM00, float fM11, float fM22)
{
    MakeDiagonal(fM00,fM11,fM22);
}
//----------------------------------------------------------------------------

void Matrix3::MakeDiagonal (float fM00, float fM11, float fM22)
{
    m_afEntry[0] = fM00;
    m_afEntry[1] = (float)0.0;
    m_afEntry[2] = (float)0.0;
    m_afEntry[3] = (float)0.0;
    m_afEntry[4] = fM11;
    m_afEntry[5] = (float)0.0;
    m_afEntry[6] = (float)0.0;
    m_afEntry[7] = (float)0.0;
    m_afEntry[8] = fM22;
}
//----------------------------------------------------------------------------

Matrix3::Matrix3 (const Vector3& rkAxis, float fAngle)
{
    FromAxisAngle(rkAxis,fAngle);
}
//----------------------------------------------------------------------------

void Matrix3::FromAxisAngle (const Vector3& rkAxis, float fAngle)
{
    float fCos = Math::Cos(fAngle);
    float fSin = Math::Sin(fAngle);
    float fOneMinusCos = ((float)1.0)-fCos;
    float fX2 = rkAxis[0]*rkAxis[0];
    float fY2 = rkAxis[1]*rkAxis[1];
    float fZ2 = rkAxis[2]*rkAxis[2];
    float fXYM = rkAxis[0]*rkAxis[1]*fOneMinusCos;
    float fXZM = rkAxis[0]*rkAxis[2]*fOneMinusCos;
    float fYZM = rkAxis[1]*rkAxis[2]*fOneMinusCos;
    float fXSin = rkAxis[0]*fSin;
    float fYSin = rkAxis[1]*fSin;
    float fZSin = rkAxis[2]*fSin;
    
    m_afEntry[0] = fX2*fOneMinusCos+fCos;
    m_afEntry[1] = fXYM-fZSin;
    m_afEntry[2] = fXZM+fYSin;
    m_afEntry[3] = fXYM+fZSin;
    m_afEntry[4] = fY2*fOneMinusCos+fCos;
    m_afEntry[5] = fYZM-fXSin;
    m_afEntry[6] = fXZM-fYSin;
    m_afEntry[7] = fYZM+fXSin;
    m_afEntry[8] = fZ2*fOneMinusCos+fCos;
}
//----------------------------------------------------------------------------

Matrix3 Matrix3::Inverse () const
{
    // Invert a 3x3 using cofactors.  This is faster than using a generic
    // Gaussian elimination because of the loop overhead of such a method.

    Matrix3 kInverse;

    kInverse[0][0] = m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7];
    kInverse[0][1] = m_afEntry[2]*m_afEntry[7] - m_afEntry[1]*m_afEntry[8];
    kInverse[0][2] = m_afEntry[1]*m_afEntry[5] - m_afEntry[2]*m_afEntry[4];
    kInverse[1][0] = m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8];
    kInverse[1][1] = m_afEntry[0]*m_afEntry[8] - m_afEntry[2]*m_afEntry[6];
    kInverse[1][2] = m_afEntry[2]*m_afEntry[3] - m_afEntry[0]*m_afEntry[5];
    kInverse[2][0] = m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6];
    kInverse[2][1] = m_afEntry[1]*m_afEntry[6] - m_afEntry[0]*m_afEntry[7];
    kInverse[2][2] = m_afEntry[0]*m_afEntry[4] - m_afEntry[1]*m_afEntry[3];

    float fDet = m_afEntry[0]*kInverse[0][0] + m_afEntry[1]*kInverse[1][0]+
        m_afEntry[2]*kInverse[2][0];

    if ( Math::FAbs(fDet) <= Math::EPSILON )
        return Matrix3::ZERO;

    kInverse /= fDet;
    return kInverse;
}
//----------------------------------------------------------------------------

Matrix3 Matrix3::Adjoint () const
{
    Matrix3 kAdjoint;

    kAdjoint[0][0] = m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7];
    kAdjoint[0][1] = m_afEntry[2]*m_afEntry[7] - m_afEntry[1]*m_afEntry[8];
    kAdjoint[0][2] = m_afEntry[1]*m_afEntry[5] - m_afEntry[2]*m_afEntry[4];
    kAdjoint[1][0] = m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8];
    kAdjoint[1][1] = m_afEntry[0]*m_afEntry[8] - m_afEntry[2]*m_afEntry[6];
    kAdjoint[1][2] = m_afEntry[2]*m_afEntry[3] - m_afEntry[0]*m_afEntry[5];
    kAdjoint[2][0] = m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6];
    kAdjoint[2][1] = m_afEntry[1]*m_afEntry[6] - m_afEntry[0]*m_afEntry[7];
    kAdjoint[2][2] = m_afEntry[0]*m_afEntry[4] - m_afEntry[1]*m_afEntry[3];

    return kAdjoint;
}
//----------------------------------------------------------------------------

float Matrix3::Determinant () const
{
    float fCo00 = m_afEntry[4]*m_afEntry[8] - m_afEntry[5]*m_afEntry[7];
    float fCo10 = m_afEntry[5]*m_afEntry[6] - m_afEntry[3]*m_afEntry[8];
    float fCo20 = m_afEntry[3]*m_afEntry[7] - m_afEntry[4]*m_afEntry[6];
    float fDet = m_afEntry[0]*fCo00 + m_afEntry[1]*fCo10 + m_afEntry[2]*fCo20;
    return fDet;
}
//----------------------------------------------------------------------------

void Matrix3::ToAxisAngle (Vector3& rkAxis, float& rfAngle) const
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    float fTrace = m_afEntry[0] + m_afEntry[4] + m_afEntry[8];
    float fCos = ((float)0.5)*(fTrace-((float)1.0));
    rfAngle = Math::ACos(fCos);  // in [0,PI]

    if ( rfAngle > (float)0.0 )
    {
        if ( rfAngle < Math::PI )
        {
            rkAxis[0] = m_afEntry[7]-m_afEntry[5];
            rkAxis[1] = m_afEntry[2]-m_afEntry[6];
            rkAxis[2] = m_afEntry[3]-m_afEntry[1];
            rkAxis.Normalize();
        }
        else
        {
            // angle is PI
            float fHalfInverse;
            if ( m_afEntry[0] >= m_afEntry[4] )
            {
                // r00 >= r11
                if ( m_afEntry[0] >= m_afEntry[8] )
                {
                    // r00 is maximum diagonal term
                    rkAxis[0] = ((float)0.5)*Math::Sqrt(m_afEntry[0] -
                        m_afEntry[4] - m_afEntry[8] + (float)1.0);
                    fHalfInverse = ((float)0.5)/rkAxis[0];
                    rkAxis[1] = fHalfInverse*m_afEntry[1];
                    rkAxis[2] = fHalfInverse*m_afEntry[2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis[2] = ((float)0.5)*Math::Sqrt(m_afEntry[8] -
                        m_afEntry[0] - m_afEntry[4] + (float)1.0);
                    fHalfInverse = ((float)0.5)/rkAxis[2];
                    rkAxis[0] = fHalfInverse*m_afEntry[2];
                    rkAxis[1] = fHalfInverse*m_afEntry[5];
                }
            }
            else
            {
                // r11 > r00
                if ( m_afEntry[4] >= m_afEntry[8] )
                {
                    // r11 is maximum diagonal term
                    rkAxis[1] = ((float)0.5)*Math::Sqrt(m_afEntry[4] -
                        m_afEntry[0] - m_afEntry[8] + (float)1.0);
                    fHalfInverse  = ((float)0.5)/rkAxis[1];
                    rkAxis[0] = fHalfInverse*m_afEntry[1];
                    rkAxis[2] = fHalfInverse*m_afEntry[5];
                }
                else
                {
                    // r22 is maximum diagonal term
                    rkAxis[2] = ((float)0.5)*Math::Sqrt(m_afEntry[8] -
                        m_afEntry[0] - m_afEntry[4] + (float)1.0);
                    fHalfInverse = ((float)0.5)/rkAxis[2];
                    rkAxis[0] = fHalfInverse*m_afEntry[2];
                    rkAxis[1] = fHalfInverse*m_afEntry[5];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        rkAxis[0] = (float)1.0;
        rkAxis[1] = (float)0.0;
        rkAxis[2] = (float)0.0;
    }
}
//----------------------------------------------------------------------------

void Matrix3::Orthonormalize ()
{
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    float fInvLength = Math::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[3]*m_afEntry[3] + m_afEntry[6]*m_afEntry[6]);

    m_afEntry[0] *= fInvLength;
    m_afEntry[3] *= fInvLength;
    m_afEntry[6] *= fInvLength;

    // compute q1
    float fDot0 = m_afEntry[0]*m_afEntry[1] + m_afEntry[3]*m_afEntry[4] +
        m_afEntry[6]*m_afEntry[7];

    m_afEntry[1] -= fDot0*m_afEntry[0];
    m_afEntry[4] -= fDot0*m_afEntry[3];
    m_afEntry[7] -= fDot0*m_afEntry[6];

    fInvLength = Math::InvSqrt(m_afEntry[1]*m_afEntry[1] +
        m_afEntry[4]*m_afEntry[4] + m_afEntry[7]*m_afEntry[7]);

    m_afEntry[1] *= fInvLength;
    m_afEntry[4] *= fInvLength;
    m_afEntry[7] *= fInvLength;

    // compute q2
    float fDot1 = m_afEntry[1]*m_afEntry[2] + m_afEntry[4]*m_afEntry[5] +
        m_afEntry[7]*m_afEntry[8];

    fDot0 = m_afEntry[0]*m_afEntry[2] + m_afEntry[3]*m_afEntry[5] +
        m_afEntry[6]*m_afEntry[8];

    m_afEntry[2] -= fDot0*m_afEntry[0] + fDot1*m_afEntry[1];
    m_afEntry[5] -= fDot0*m_afEntry[3] + fDot1*m_afEntry[4];
    m_afEntry[8] -= fDot0*m_afEntry[6] + fDot1*m_afEntry[7];

    fInvLength = Math::InvSqrt(m_afEntry[2]*m_afEntry[2] +
        m_afEntry[5]*m_afEntry[5] + m_afEntry[8]*m_afEntry[8]);

    m_afEntry[2] *= fInvLength;
    m_afEntry[5] *= fInvLength;
    m_afEntry[8] *= fInvLength;
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesXYZ (float& rfXAngle, float& rfYAngle,
    float& rfZAngle) const
{
    // rot =  cy*cz          -cy*sz           sy
    //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
    //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

    if ( m_afEntry[2] < (float)1.0 )
    {
        if ( m_afEntry[2] > -(float)1.0 )
        {
            rfXAngle = Math::ATan2(-m_afEntry[5],m_afEntry[8]);
            rfYAngle = (float)asin((double)m_afEntry[2]);
            rfZAngle = Math::ATan2(-m_afEntry[1],m_afEntry[0]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  XA - ZA = -atan2(r10,r11)
            rfXAngle = -Math::ATan2(m_afEntry[3],m_afEntry[4]);
            rfYAngle = -Math::HALF_PI;
            rfZAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  XAngle + ZAngle = atan2(r10,r11)
        rfXAngle = Math::ATan2(m_afEntry[3],m_afEntry[4]);
        rfYAngle = Math::HALF_PI;
        rfZAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesXZY (float& rfXAngle, float& rfZAngle,
    float& rfYAngle) const
{
    // rot =  cy*cz          -sz              cz*sy
    //        sx*sy+cx*cy*sz  cx*cz          -cy*sx+cx*sy*sz
    //       -cx*sy+cy*sx*sz  cz*sx           cx*cy+sx*sy*sz

    if ( m_afEntry[1] < (float)1.0 )
    {
        if ( m_afEntry[1] > -(float)1.0 )
        {
            rfXAngle = Math::ATan2(m_afEntry[7],m_afEntry[4]);
            rfZAngle = (float)asin(-(double)m_afEntry[1]);
            rfYAngle = Math::ATan2(m_afEntry[2],m_afEntry[0]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  XA - YA = atan2(r20,r22)
            rfXAngle = Math::ATan2(m_afEntry[6],m_afEntry[8]);
            rfZAngle = Math::HALF_PI;
            rfYAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  XA + YA = atan2(-r20,r22)
        rfXAngle = Math::ATan2(-m_afEntry[6],m_afEntry[8]);
        rfZAngle = -Math::HALF_PI;
        rfYAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesYXZ (float& rfYAngle, float& rfXAngle,
    float& rfZAngle) const
{
    // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
    //        cx*sz           cx*cz          -sx
    //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy

    if ( m_afEntry[5] < (float)1.0 )
    {
        if ( m_afEntry[5] > -(float)1.0 )
        {
            rfYAngle = Math::ATan2(m_afEntry[2],m_afEntry[8]);
            rfXAngle = (float)asin(-(double)m_afEntry[5]);
            rfZAngle = Math::ATan2(m_afEntry[3],m_afEntry[4]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
            rfYAngle = Math::ATan2(m_afEntry[1],m_afEntry[0]);
            rfXAngle = Math::HALF_PI;
            rfZAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
        rfYAngle = Math::ATan2(-m_afEntry[1],m_afEntry[0]);
        rfXAngle = -Math::HALF_PI;
        rfZAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesYZX (float& rfYAngle, float& rfZAngle,
    float& rfXAngle) const
{
    // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
    //        sz              cx*cz          -cz*sx
    //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz

    if ( m_afEntry[3] < (float)1.0 )
    {
        if ( m_afEntry[3] > -(float)1.0 )
        {
            rfYAngle = Math::ATan2(-m_afEntry[6],m_afEntry[0]);
            rfZAngle = (float)asin((double)m_afEntry[3]);
            rfXAngle = Math::ATan2(-m_afEntry[5],m_afEntry[4]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  YA - XA = -atan2(r21,r22);
            rfYAngle = -Math::ATan2(m_afEntry[7],m_afEntry[8]);
            rfZAngle = -Math::HALF_PI;
            rfXAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  YA + XA = atan2(r21,r22)
        rfYAngle = Math::ATan2(m_afEntry[7],m_afEntry[8]);
        rfZAngle = Math::HALF_PI;
        rfXAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesZXY (float& rfZAngle, float& rfXAngle,
    float& rfYAngle) const
{
    // rot =  cy*cz-sx*sy*sz -cx*sz           cz*sy+cy*sx*sz
    //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
    //       -cx*sy           sx              cx*cy

    if ( m_afEntry[7] < (float)1.0 )
    {
        if ( m_afEntry[7] > -(float)1.0 )
        {
            rfZAngle = Math::ATan2(-m_afEntry[1],m_afEntry[4]);
            rfXAngle = (float)asin((double)m_afEntry[7]);
            rfYAngle = Math::ATan2(-m_afEntry[6],m_afEntry[8]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  ZA - YA = -atan(r02,r00)
            rfZAngle = -Math::ATan2(m_afEntry[2],m_afEntry[0]);
            rfXAngle = -Math::HALF_PI;
            rfYAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  ZA + YA = atan2(r02,r00)
        rfZAngle = Math::ATan2(m_afEntry[2],m_afEntry[0]);
        rfXAngle = Math::HALF_PI;
        rfYAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::ToEulerAnglesZYX (float& rfZAngle, float& rfYAngle,
    float& rfXAngle) const
{
    // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
    //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
    //       -sy              cy*sx           cx*cy

    if ( m_afEntry[6] < (float)1.0 )
    {
        if ( m_afEntry[6] > -(float)1.0 )
        {
            rfZAngle = Math::ATan2(m_afEntry[3],m_afEntry[0]);
            rfYAngle = (float)asin(-(double)m_afEntry[6]);
            rfXAngle = Math::ATan2(m_afEntry[7],m_afEntry[8]);
            return true;
        }
        else
        {
            // WARNING.  Not unique.  ZA - XA = -atan2(r01,r02)
            rfZAngle = -Math::ATan2(m_afEntry[1],m_afEntry[2]);
            rfYAngle = Math::HALF_PI;
            rfXAngle = (float)0.0;
            return false;
        }
    }
    else
    {
        // WARNING.  Not unique.  ZA + XA = atan2(-r01,-r02)
        rfZAngle = Math::ATan2(-m_afEntry[1],-m_afEntry[2]);
        rfYAngle = -Math::HALF_PI;
        rfXAngle = (float)0.0;
        return false;
    }
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesXYZ (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    *this = kXMat*(kYMat*kZMat);
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesXZY (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    *this = kXMat*(kZMat*kYMat);
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesYXZ (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    *this = kYMat*(kXMat*kZMat);
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesYZX (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    *this = kYMat*(kZMat*kXMat);
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesZXY (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    *this = kZMat*(kXMat*kYMat);
}
//----------------------------------------------------------------------------

void Matrix3::FromEulerAnglesZYX (float fYAngle, float fPAngle,
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math::Cos(fYAngle);
    fSin = Math::Sin(fYAngle);
    Matrix3 kZMat(
        fCos,-fSin,(float)0.0,
        fSin,fCos,(float)0.0,
        (float)0.0,(float)0.0,(float)1.0);

    fCos = Math::Cos(fPAngle);
    fSin = Math::Sin(fPAngle);
    Matrix3 kYMat(
        fCos,(float)0.0,fSin,
        (float)0.0,(float)1.0,(float)0.0,
        -fSin,(float)0.0,fCos);

    fCos = Math::Cos(fRAngle);
    fSin = Math::Sin(fRAngle);
    Matrix3 kXMat(
        (float)1.0,(float)0.0,(float)0.0,
        (float)0.0,fCos,-fSin,
        (float)0.0,fSin,fCos);

    *this = kZMat*(kYMat*kXMat);
}
//----------------------------------------------------------------------------

Matrix3 Matrix3::Slerp (float fT, const Matrix3& rkR0,
    const Matrix3& rkR1)
{
    Vector3 kAxis;
    float fAngle;
    Matrix3 kProd = rkR0.TransposeTimes(rkR1);
    kProd.ToAxisAngle(kAxis,fAngle);
    return Matrix3(kAxis,fT*fAngle);
}
//----------------------------------------------------------------------------

void Matrix3::Tridiagonalize (float afDiag[3], float afSubDiag[3])
{
    // Householder reduction T = Q^t M Q
    //   Input:   
    //     mat, symmetric 3x3 matrix M
    //   Output:  
    //     mat, orthogonal matrix Q (a reflection)
    //     diag, diagonal entries of T
    //     subd, subdiagonal entries of T (T is symmetric)

    float fA = m_afEntry[0];
    float fB = m_afEntry[1];
    float fC = m_afEntry[2];
    float fD = m_afEntry[4];
    float fE = m_afEntry[5];
    float fF = m_afEntry[8];

    afDiag[0] = fA;
    afSubDiag[2] = (float)0.0;
    if ( Math::FAbs(fC) >= Math::EPSILON )
    {
        float fLength = Math::Sqrt(fB*fB+fC*fC);
        float fInvLength = ((float)1.0)/fLength;
        fB *= fInvLength;
        fC *= fInvLength;
        float fQ = ((float)2.0)*fB*fE+fC*(fF-fD);
        afDiag[1] = fD+fC*fQ;
        afDiag[2] = fF-fC*fQ;
        afSubDiag[0] = fLength;
        afSubDiag[1] = fE-fB*fQ;

        m_afEntry[0] = (float)1.0;
        m_afEntry[1] = (float)0.0;
        m_afEntry[2] = (float)0.0;
        m_afEntry[3] = (float)0.0;
        m_afEntry[4] = fB;
        m_afEntry[5] = fC;
        m_afEntry[6] = (float)0.0;
        m_afEntry[7] = fC;
        m_afEntry[8] = -fB;
    }
    else
    {
        afDiag[1] = fD;
        afDiag[2] = fF;
        afSubDiag[0] = fB;
        afSubDiag[1] = fE;

        m_afEntry[0] = (float)1.0;
        m_afEntry[1] = (float)0.0;
        m_afEntry[2] = (float)0.0;
        m_afEntry[3] = (float)0.0;
        m_afEntry[4] = (float)1.0;
        m_afEntry[5] = (float)0.0;
        m_afEntry[6] = (float)0.0;
        m_afEntry[7] = (float)0.0;
        m_afEntry[8] = -(float)1.0;
    }
}
//----------------------------------------------------------------------------

bool Matrix3::QLAlgorithm (float afDiag[3], float afSubDiag[3])
{
    // QL iteration with implicit shifting to reduce matrix from tridiagonal
    // to diagonal

    for (int i0 = 0; i0 < 3; i0++)
    {
        const int iMaxIter = 32;
        int iIter;
        for (iIter = 0; iIter < iMaxIter; iIter++)
        {
            int i1;
            for (i1 = i0; i1 <= 1; i1++)
            {
                float fSum = Math::FAbs(afDiag[i1]) +
                    Math::FAbs(afDiag[i1+1]);
                if ( Math::FAbs(afSubDiag[i1]) + fSum == fSum )
                    break;
            }
            if ( i1 == i0 )
                break;

            float fTmp0 = (afDiag[i0+1] - afDiag[i0]) /
                (((float)2.0)*afSubDiag[i0]);
            float fTmp1 = Math::Sqrt(fTmp0*fTmp0+(float)1.0);
            if ( fTmp0 < (float)0.0 )
                fTmp0 = afDiag[i1]-afDiag[i0]+afSubDiag[i0]/(fTmp0-fTmp1);
            else
                fTmp0 = afDiag[i1]-afDiag[i0]+afSubDiag[i0]/(fTmp0+fTmp1);
            float fSin = (float)1.0;
            float fCos = (float)1.0;
            float fTmp2 = (float)0.0;
            for (int i2 = i1-1; i2 >= i0; i2--)
            {
                float fTmp3 = fSin*afSubDiag[i2];
                float fTmp4 = fCos*afSubDiag[i2];
                if ( Math::FAbs(fTmp3) >= Math::FAbs(fTmp0) )
                {
                    fCos = fTmp0/fTmp3;
                    fTmp1 = Math::Sqrt(fCos*fCos+(float)1.0);
                    afSubDiag[i2+1] = fTmp3*fTmp1;
                    fSin = ((float)1.0)/fTmp1;
                    fCos *= fSin;
                }
                else
                {
                    fSin = fTmp3/fTmp0;
                    fTmp1 = Math::Sqrt(fSin*fSin+(float)1.0);
                    afSubDiag[i2+1] = fTmp0*fTmp1;
                    fCos = ((float)1.0)/fTmp1;
                    fSin *= fCos;
                }
                fTmp0 = afDiag[i2+1]-fTmp2;
                fTmp1 = (afDiag[i2]-fTmp0)*fSin+((float)2.0)*fTmp4*fCos;
                fTmp2 = fSin*fTmp1;
                afDiag[i2+1] = fTmp0+fTmp2;
                fTmp0 = fCos*fTmp1-fTmp4;

                for (int iRow = 0; iRow < 3; iRow++)
                {
                    fTmp3 = m_afEntry[I(iRow,i2+1)];
                    m_afEntry[I(iRow,i2+1)] = fSin*m_afEntry[I(iRow,i2)] +
                        fCos*fTmp3;
                    m_afEntry[I(iRow,i2)] = fCos*m_afEntry[I(iRow,i2)] -
                        fSin*fTmp3;
                }
            }
            afDiag[i0] -= fTmp2;
            afSubDiag[i0] = fTmp0;
            afSubDiag[i1] = (float)0.0;
        }

        if ( iIter == iMaxIter )
        {
            // should not get here under normal circumstances
            //assert( false );
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------

void Matrix3::EigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag)
    const
{
    // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
    // diagonal entries of D are the corresponding eigenvalues.
    float afDiag[3], afSubDiag[3];
    rkRot = *this;
    rkRot.Tridiagonalize(afDiag,afSubDiag);
    rkRot.QLAlgorithm(afDiag,afSubDiag);

    // The Householder transformation is a reflection.  Make the eigenvectors
    // a right--handed system by changing sign on the last column.
    rkRot[2][0] = -rkRot[2][0];
    rkRot[2][1] = -rkRot[2][1];
    rkRot[2][2] = -rkRot[2][2];

    // (insertion) sort eigenvalues in increasing order, d0 <= d1 <= d2
    int i;
    float fSave;

    if ( afDiag[1] < afDiag[0] )
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
    }

    if ( afDiag[2] < afDiag[1] )
    {
        // swap d1 and d2
        fSave = afDiag[1];
        afDiag[1] = afDiag[2];
        afDiag[2] = fSave;

        // swap V1 and V2
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][1];
            rkRot[i][1] = rkRot[i][2];
            rkRot[i][2] = fSave;
        }
    }

    if ( afDiag[1] < afDiag[0] )
    {
        // swap d0 and d1
        fSave = afDiag[0];
        afDiag[0] = afDiag[1];
        afDiag[1] = fSave;

        // swap V0 and V1
        for (i = 0; i < 3; i++)
        {
            fSave = rkRot[i][0];
            rkRot[i][0] = rkRot[i][1];
            rkRot[i][1] = fSave;
        }
    }

    rkDiag.MakeDiagonal(afDiag[0],afDiag[1],afDiag[2]);
}
//----------------------------------------------------------------------------

void Matrix3::Bidiagonalize (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR)
{
    float afV[3], afW[3];
    float fLength, fSign, fT1, fInvT1, fT2;
    bool bIdentity;

    // map first column to (*,0,0)
    fLength = Math::Sqrt(rkA[0][0]*rkA[0][0] + rkA[1][0]*rkA[1][0] +
        rkA[2][0]*rkA[2][0]);
    if ( fLength > (float)0.0 )
    {
        fSign = (rkA[0][0] > (float)0.0 ? (float)1.0 : -(float)1.0);
        fT1 = rkA[0][0] + fSign*fLength;
        fInvT1 = ((float)1.0)/fT1;
        afV[1] = rkA[1][0]*fInvT1;
        afV[2] = rkA[2][0]*fInvT1;

        fT2 = -((float)2.0)/(((float)1.0)+afV[1]*afV[1]+afV[2]*afV[2]);
        afW[0] = fT2*(rkA[0][0]+rkA[1][0]*afV[1]+rkA[2][0]*afV[2]);
        afW[1] = fT2*(rkA[0][1]+rkA[1][1]*afV[1]+rkA[2][1]*afV[2]);
        afW[2] = fT2*(rkA[0][2]+rkA[1][2]*afV[1]+rkA[2][2]*afV[2]);
        rkA[0][0] += afW[0];
        rkA[0][1] += afW[1];
        rkA[0][2] += afW[2];
        rkA[1][1] += afV[1]*afW[1];
        rkA[1][2] += afV[1]*afW[2];
        rkA[2][1] += afV[2]*afW[1];
        rkA[2][2] += afV[2]*afW[2];

        rkL[0][0] = ((float)1.0)+fT2;
        rkL[0][1] = fT2*afV[1];
        rkL[1][0] = rkL[0][1];
        rkL[0][2] = fT2*afV[2];
        rkL[2][0] = rkL[0][2];
        rkL[1][1] = ((float)1.0)+fT2*afV[1]*afV[1];
        rkL[1][2] = fT2*afV[1]*afV[2];
        rkL[2][1] = rkL[1][2];
        rkL[2][2] = ((float)1.0)+fT2*afV[2]*afV[2];
        bIdentity = false;
    }
    else
    {
        rkL = Matrix3::IDENTITY;
        bIdentity = true;
    }

    // map first row to (*,*,0)
    fLength = Math::Sqrt(rkA[0][1]*rkA[0][1]+rkA[0][2]*rkA[0][2]);
    if ( fLength > (float)0.0 )
    {
        fSign = (rkA[0][1] > (float)0.0 ? (float)1.0 : -(float)1.0);
        fT1 = rkA[0][1] + fSign*fLength;
        afV[2] = rkA[0][2]/fT1;

        fT2 = -((float)2.0)/(((float)1.0)+afV[2]*afV[2]);
        afW[0] = fT2*(rkA[0][1]+rkA[0][2]*afV[2]);
        afW[1] = fT2*(rkA[1][1]+rkA[1][2]*afV[2]);
        afW[2] = fT2*(rkA[2][1]+rkA[2][2]*afV[2]);
        rkA[0][1] += afW[0];
        rkA[1][1] += afW[1];
        rkA[1][2] += afW[1]*afV[2];
        rkA[2][1] += afW[2];
        rkA[2][2] += afW[2]*afV[2];
        
        rkR[0][0] = (float)1.0;
        rkR[0][1] = (float)0.0;
        rkR[1][0] = (float)0.0;
        rkR[0][2] = (float)0.0;
        rkR[2][0] = (float)0.0;
        rkR[1][1] = ((float)1.0)+fT2;
        rkR[1][2] = fT2*afV[2];
        rkR[2][1] = rkR[1][2];
        rkR[2][2] = ((float)1.0)+fT2*afV[2]*afV[2];
    }
    else
    {
        rkR = Matrix3::IDENTITY;
    }

    // map second column to (*,*,0)
    fLength = Math::Sqrt(rkA[1][1]*rkA[1][1]+rkA[2][1]*rkA[2][1]);
    if ( fLength > (float)0.0 )
    {
        fSign = (rkA[1][1] > (float)0.0 ? (float)1.0 : -(float)1.0);
        fT1 = rkA[1][1] + fSign*fLength;
        afV[2] = rkA[2][1]/fT1;

        fT2 = -((float)2.0)/(((float)1.0)+afV[2]*afV[2]);
        afW[1] = fT2*(rkA[1][1]+rkA[2][1]*afV[2]);
        afW[2] = fT2*(rkA[1][2]+rkA[2][2]*afV[2]);
        rkA[1][1] += afW[1];
        rkA[1][2] += afW[2];
        rkA[2][2] += afV[2]*afW[2];

        float fA = ((float)1.0)+fT2;
        float fB = fT2*afV[2];
        float fC = ((float)1.0)+fB*afV[2];

        if ( bIdentity )
        {
            rkL[0][0] = (float)1.0;
            rkL[0][1] = (float)0.0;
            rkL[1][0] = (float)0.0;
            rkL[0][2] = (float)0.0;
            rkL[2][0] = (float)0.0;
            rkL[1][1] = fA;
            rkL[1][2] = fB;
            rkL[2][1] = fB;
            rkL[2][2] = fC;
        }
        else
        {
            for (int iRow = 0; iRow < 3; iRow++)
            {
                float fTmp0 = rkL[iRow][1];
                float fTmp1 = rkL[iRow][2];
                rkL[iRow][1] = fA*fTmp0+fB*fTmp1;
                rkL[iRow][2] = fB*fTmp0+fC*fTmp1;
            }
        }
    }
}
//----------------------------------------------------------------------------

void Matrix3::GolubKahanStep (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR)
{
    float fT11 = rkA[0][1]*rkA[0][1]+rkA[1][1]*rkA[1][1];
    float fT22 = rkA[1][2]*rkA[1][2]+rkA[2][2]*rkA[2][2];
    float fT12 = rkA[1][1]*rkA[1][2];
    float fTrace = fT11+fT22;
    float fDiff = fT11-fT22;
    float fDiscr = Math::Sqrt(fDiff*fDiff+((float)4.0)*fT12*fT12);
    float fRoot1 = ((float)0.5)*(fTrace+fDiscr);
    float fRoot2 = ((float)0.5)*(fTrace-fDiscr);

    // adjust right
    float fY = rkA[0][0] - (Math::FAbs(fRoot1-fT22) <=
        Math::FAbs(fRoot2-fT22) ? fRoot1 : fRoot2);
    float fZ = rkA[0][1];
    float fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
    float fSin = fZ*fInvLength;
    float fCos = -fY*fInvLength;

    float fTmp0 = rkA[0][0];
    float fTmp1 = rkA[0][1];
    rkA[0][0] = fCos*fTmp0-fSin*fTmp1;
    rkA[0][1] = fSin*fTmp0+fCos*fTmp1;
    rkA[1][0] = -fSin*rkA[1][1];
    rkA[1][1] *= fCos;

    int iRow;
    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = rkR[0][iRow];
        fTmp1 = rkR[1][iRow];
        rkR[0][iRow] = fCos*fTmp0-fSin*fTmp1;
        rkR[1][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = rkA[0][0];
    fZ = rkA[1][0];
    fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[0][0] = fCos*rkA[0][0]-fSin*rkA[1][0];
    fTmp0 = rkA[0][1];
    fTmp1 = rkA[1][1];
    rkA[0][1] = fCos*fTmp0-fSin*fTmp1;
    rkA[1][1] = fSin*fTmp0+fCos*fTmp1;
    rkA[0][2] = -fSin*rkA[1][2];
    rkA[1][2] *= fCos;

    int iCol;
    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = rkL[iCol][0];
        fTmp1 = rkL[iCol][1];
        rkL[iCol][0] = fCos*fTmp0-fSin*fTmp1;
        rkL[iCol][1] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust right
    fY = rkA[0][1];
    fZ = rkA[0][2];
    fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[0][1] = fCos*rkA[0][1]-fSin*rkA[0][2];
    fTmp0 = rkA[1][1];
    fTmp1 = rkA[1][2];
    rkA[1][1] = fCos*fTmp0-fSin*fTmp1;
    rkA[1][2] = fSin*fTmp0+fCos*fTmp1;
    rkA[2][1] = -fSin*rkA[2][2];
    rkA[2][2] *= fCos;

    for (iRow = 0; iRow < 3; iRow++)
    {
        fTmp0 = rkR[1][iRow];
        fTmp1 = rkR[2][iRow];
        rkR[1][iRow] = fCos*fTmp0-fSin*fTmp1;
        rkR[2][iRow] = fSin*fTmp0+fCos*fTmp1;
    }

    // adjust left
    fY = rkA[1][1];
    fZ = rkA[2][1];
    fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
    fSin = fZ*fInvLength;
    fCos = -fY*fInvLength;

    rkA[1][1] = fCos*rkA[1][1]-fSin*rkA[2][1];
    fTmp0 = rkA[1][2];
    fTmp1 = rkA[2][2];
    rkA[1][2] = fCos*fTmp0-fSin*fTmp1;
    rkA[2][2] = fSin*fTmp0+fCos*fTmp1;

    for (iCol = 0; iCol < 3; iCol++)
    {
        fTmp0 = rkL[iCol][1];
        fTmp1 = rkL[iCol][2];
        rkL[iCol][1] = fCos*fTmp0-fSin*fTmp1;
        rkL[iCol][2] = fSin*fTmp0+fCos*fTmp1;
    }
}
//----------------------------------------------------------------------------

void Matrix3::SingularValueDecomposition (Matrix3& rkL, Matrix3& rkS,
    Matrix3& rkR) const
{
    int iRow, iCol;

    Matrix3 kA = *this;
    Bidiagonalize(kA,rkL,rkR);
    rkS.MakeZero();

    const int iMax = 32;
    const float fEpsilon = (float)1e-04;
    for (int i = 0; i < iMax; i++)
    {
        float fTmp, fTmp0, fTmp1;
        float fSin0, fCos0, fTan0;
        float fSin1, fCos1, fTan1;

        bool bTest1 = (Math::FAbs(kA[0][1]) <=
            fEpsilon*(Math::FAbs(kA[0][0]) +
            Math::FAbs(kA[1][1])));
        bool bTest2 = (Math::FAbs(kA[1][2]) <=
            fEpsilon*(Math::FAbs(kA[1][1]) +
            Math::FAbs(kA[2][2])));
        if ( bTest1 )
        {
            if ( bTest2 )
            {
                rkS[0][0] = kA[0][0];
                rkS[1][1] = kA[1][1];
                rkS[2][2] = kA[2][2];
                break;
            }
            else
            {
                // 2x2 closed form factorization
                fTmp = (kA[1][1]*kA[1][1] - kA[2][2]*kA[2][2] +
                    kA[1][2]*kA[1][2])/(kA[1][2]*kA[2][2]);
                fTan0 = ((float)0.5)*(fTmp + Math::Sqrt(fTmp*fTmp +
                    ((float)4.0)));
                fCos0 = Math::InvSqrt(((float)1.0)+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = rkL[iCol][1];
                    fTmp1 = rkL[iCol][2];
                    rkL[iCol][1] = fCos0*fTmp0-fSin0*fTmp1;
                    rkL[iCol][2] = fSin0*fTmp0+fCos0*fTmp1;
                }
                
                fTan1 = (kA[1][2]-kA[2][2]*fTan0)/kA[1][1];
                fCos1 = Math::InvSqrt(((float)1.0)+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = rkR[1][iRow];
                    fTmp1 = rkR[2][iRow];
                    rkR[1][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    rkR[2][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                rkS[0][0] = kA[0][0];
                rkS[1][1] = fCos0*fCos1*kA[1][1] -
                    fSin1*(fCos0*kA[1][2]-fSin0*kA[2][2]);
                rkS[2][2] = fSin0*fSin1*kA[1][1] +
                    fCos1*(fSin0*kA[1][2]+fCos0*kA[2][2]);
                break;
            }
        }
        else 
        {
            if ( bTest2 )
            {
                // 2x2 closed form factorization 
                fTmp = (kA[0][0]*kA[0][0] + kA[1][1]*kA[1][1] -
                    kA[0][1]*kA[0][1])/(kA[0][1]*kA[1][1]);
                fTan0 = ((float)0.5)*(-fTmp + Math::Sqrt(fTmp*fTmp +
                    ((float)4.0)));
                fCos0 = Math::InvSqrt(((float)1.0)+fTan0*fTan0);
                fSin0 = fTan0*fCos0;

                for (iCol = 0; iCol < 3; iCol++)
                {
                    fTmp0 = rkL[iCol][0];
                    fTmp1 = rkL[iCol][1];
                    rkL[iCol][0] = fCos0*fTmp0-fSin0*fTmp1;
                    rkL[iCol][1] = fSin0*fTmp0+fCos0*fTmp1;
                }
                
                fTan1 = (kA[0][1]-kA[1][1]*fTan0)/kA[0][0];
                fCos1 = Math::InvSqrt(((float)1.0)+fTan1*fTan1);
                fSin1 = -fTan1*fCos1;

                for (iRow = 0; iRow < 3; iRow++)
                {
                    fTmp0 = rkR[0][iRow];
                    fTmp1 = rkR[1][iRow];
                    rkR[0][iRow] = fCos1*fTmp0-fSin1*fTmp1;
                    rkR[1][iRow] = fSin1*fTmp0+fCos1*fTmp1;
                }

                rkS[0][0] = fCos0*fCos1*kA[0][0] -
                    fSin1*(fCos0*kA[0][1]-fSin0*kA[1][1]);
                rkS[1][1] = fSin0*fSin1*kA[0][0] +
                    fCos1*(fSin0*kA[0][1]+fCos0*kA[1][1]);
                rkS[2][2] = kA[2][2];
                break;
            }
            else
            {
                GolubKahanStep(kA,rkL,rkR);
            }
        }
    }

    // positize diagonal
    for (iRow = 0; iRow < 3; iRow++)
    {
        if ( rkS[iRow][iRow] < (float)0.0 )
        {
            rkS[iRow][iRow] = -rkS[iRow][iRow];
            for (iCol = 0; iCol < 3; iCol++)
                rkR[iRow][iCol] = -rkR[iRow][iCol];
        }
    }
}
//----------------------------------------------------------------------------

void Matrix3::SingularValueComposition (const Matrix3& rkL,
    const Matrix3& rkS, const Matrix3& rkR)
{
    *this = rkL*(rkS*rkR);
}
//----------------------------------------------------------------------------

void Matrix3::QDUDecomposition (Matrix3& rkQ, Matrix3& rkD,
    Matrix3& rkU) const
{
    // Factor M = QR = QDU where Q is orthogonal (rotation), D is diagonal
    // (scaling),  and U is upper triangular with ones on its diagonal
    // (shear).  Algorithm uses Gram-Schmidt orthogonalization (the QR
    // algorithm).
    //
    // If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.  The matrix R has entries
    //
    //   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
    //   r10 = 0      r11 = q1*m1  r12 = q1*m2
    //   r20 = 0      r21 = 0      r22 = q2*m2
    //
    // so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
    // u02 = r02/r00, and u12 = r12/r11.

    // build orthogonal matrix Q
    float fInvLength = Math::InvSqrt(m_afEntry[0]*m_afEntry[0] +
        m_afEntry[3]*m_afEntry[3] + m_afEntry[6]*m_afEntry[6]);
    rkQ[0][0] = m_afEntry[0]*fInvLength;
    rkQ[1][0] = m_afEntry[3]*fInvLength;
    rkQ[2][0] = m_afEntry[6]*fInvLength;

    float fDot = rkQ[0][0]*m_afEntry[1] + rkQ[1][0]*m_afEntry[4] +
        rkQ[2][0]*m_afEntry[7];
    rkQ[0][1] = m_afEntry[1]-fDot*rkQ[0][0];
    rkQ[1][1] = m_afEntry[4]-fDot*rkQ[1][0];
    rkQ[2][1] = m_afEntry[7]-fDot*rkQ[2][0];
    fInvLength = Math::InvSqrt(rkQ[0][1]*rkQ[0][1] +
        rkQ[1][1]*rkQ[1][1] + rkQ[2][1]*rkQ[2][1]);
    rkQ[0][1] *= fInvLength;
    rkQ[1][1] *= fInvLength;
    rkQ[2][1] *= fInvLength;

    fDot = rkQ[0][0]*m_afEntry[2] + rkQ[1][0]*m_afEntry[5] +
        rkQ[2][0]*m_afEntry[8];
    rkQ[0][2] = m_afEntry[2]-fDot*rkQ[0][0];
    rkQ[1][2] = m_afEntry[5]-fDot*rkQ[1][0];
    rkQ[2][2] = m_afEntry[8]-fDot*rkQ[2][0];
    fDot = rkQ[0][1]*m_afEntry[2] + rkQ[1][1]*m_afEntry[5] +
        rkQ[2][1]*m_afEntry[8];
    rkQ[0][2] -= fDot*rkQ[0][1];
    rkQ[1][2] -= fDot*rkQ[1][1];
    rkQ[2][2] -= fDot*rkQ[2][1];
    fInvLength = Math::InvSqrt(rkQ[0][2]*rkQ[0][2] +
        rkQ[1][2]*rkQ[1][2] + rkQ[2][2]*rkQ[2][2]);
    rkQ[0][2] *= fInvLength;
    rkQ[1][2] *= fInvLength;
    rkQ[2][2] *= fInvLength;

    // guarantee that orthogonal matrix has determinant 1 (no reflections)
    float fDet = rkQ[0][0]*rkQ[1][1]*rkQ[2][2] + rkQ[0][1]*rkQ[1][2]*rkQ[2][0]
        +  rkQ[0][2]*rkQ[1][0]*rkQ[2][1] - rkQ[0][2]*rkQ[1][1]*rkQ[2][0]
        -  rkQ[0][1]*rkQ[1][0]*rkQ[2][2] - rkQ[0][0]*rkQ[1][2]*rkQ[2][1];

    if ( fDet < (float)0.0 )
    {
        for (int iRow = 0; iRow < 3; iRow++)
        {
            for (int iCol = 0; iCol < 3; iCol++)
                rkQ[iRow][iCol] = -rkQ[iRow][iCol];
        }
    }

    // build "right" matrix R
    Matrix3 kR;
    kR[0][0] = rkQ[0][0]*m_afEntry[0] + rkQ[1][0]*m_afEntry[3] +
        rkQ[2][0]*m_afEntry[6];
    kR[0][1] = rkQ[0][0]*m_afEntry[1] + rkQ[1][0]*m_afEntry[4] +
        rkQ[2][0]*m_afEntry[7];
    kR[1][1] = rkQ[0][1]*m_afEntry[1] + rkQ[1][1]*m_afEntry[4] +
        rkQ[2][1]*m_afEntry[7];
    kR[0][2] = rkQ[0][0]*m_afEntry[2] + rkQ[1][0]*m_afEntry[5] +
        rkQ[2][0]*m_afEntry[8];
    kR[1][2] = rkQ[0][1]*m_afEntry[2] + rkQ[1][1]*m_afEntry[5] +
        rkQ[2][1]*m_afEntry[8];
    kR[2][2] = rkQ[0][2]*m_afEntry[2] + rkQ[1][2]*m_afEntry[5] +
        rkQ[2][2]*m_afEntry[8];

    // the scaling component
    rkD.MakeDiagonal(kR[0][0],kR[1][1],kR[2][2]);

    // the shear component
    float fInvD0 = ((float)1.0)/rkD[0][0];
    rkU[0][0] = (float)1.0;
    rkU[0][1] = kR[0][1]*fInvD0;
    rkU[0][2] = kR[0][2]*fInvD0;
    rkU[1][0] = (float)0.0;
    rkU[1][1] = (float)1.0;
    rkU[1][2] = kR[1][2]/rkD[1][1];
    rkU[2][0] = (float)0.0;
    rkU[2][1] = (float)0.0;
    rkU[2][2] = (float)1.0;
}
//----------------------------------------------------------------------------

const Matrix3 Matrix3::ZERO(
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f);
const Matrix3 Matrix3::IDENTITY(
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f);

}
