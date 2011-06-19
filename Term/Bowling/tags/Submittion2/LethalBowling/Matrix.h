#pragma once

#include "Vector.h"

namespace Virgin
{

class Matrix
{
public:
    // Construction.  In the second constructor, if bZero is 'true', the
    // matrix is set to the zero matrix.  If bZero is 'false', the matrix
    // is set to the identity matrix.
    Matrix ();
    Matrix (bool bZero);
    Matrix (const Matrix& rkM);

    void MakeZero ();
    void MakeIdentity ();
    void MakeDiagonal (const float* afDiag);

    // member access
    operator const float* () const;
    operator float* ();
    const float* operator[] (int iRow) const;
    float* operator[] (int iRow);
    float operator() (int iRow, int iCol) const;
    float& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector3& rkV);
    Vector3 GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector3& rkV);
    Vector3 GetColumn (int iCol) const;
    void GetColumnMajor (float* afCMajor) const;

    // assignment
    Matrix& operator= (const Matrix& rkM);

    // comparison
    bool operator== (const Matrix& rkM) const;
    bool operator!= (const Matrix& rkM) const;
    bool operator<  (const Matrix& rkM) const;
    bool operator<= (const Matrix& rkM) const;
    bool operator>  (const Matrix& rkM) const;
    bool operator>= (const Matrix& rkM) const;

    // arithmetic operations
    Matrix operator+ (const Matrix& rkM) const;
    Matrix operator- (const Matrix& rkM) const;
    Matrix operator* (const Matrix& rkM) const;
    Matrix operator* (float fScalar) const;
    Matrix operator/ (float fScalar) const;
    Matrix operator- () const;

    // arithmetic updates
    Matrix& operator+= (const Matrix& rkM);
    Matrix& operator-= (const Matrix& rkM);
    Matrix& operator*= (float fScalar);
    Matrix& operator/= (float fScalar);

    // matrix products
    Matrix Transpose () const;  // M^T
    Matrix TransposeTimes (const Matrix& rkM) const;  // this^T * M
    Matrix TimesTranspose (const Matrix& rkM) const;  // this * M^T

    // matrix-vector operations
    Vector3 operator* (const Vector3& rkV) const;  // M * v
    float QForm (const Vector3& rkU, const Vector3& rkV)
        const;  // u^T*M*v

protected:
    // for indexing into the 1D array of the matrix, iCol+3*iRow
    static int I (int iRow, int iCol);

    // support for comparisons
    int CompareArrays (const Matrix& rkM) const;

    float m_afEntry[3*3];
};

// c * M
Matrix operator* (float fScalar, const Matrix& rkM);

// v^T * M
Vector3 operator* (const Vector3& rkV, const Matrix& rkM);


////////////////////////////////////////////////////////////
class Matrix3 : public Matrix
{
public:
    // construction
    Matrix3 ();
    Matrix3 (const Matrix3& rkM);
    Matrix3 (const Matrix& rkM);

    // input Mrc is in row r, column c.
    Matrix3 (float fM00, float fM01, float fM02,
             float fM10, float fM11, float fM12,
             float fM20, float fM21, float fM22);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} [row major]
    //   false: entry[0..8]={m00,m10,m20,m01,m11,m21,m02,m12,m22} [col major]
    Matrix3 (const float afEntry[9], bool bRowMajor);

    // Create matrices based on vector input.  The Boolean is interpreted as
    //   true: vectors are columns of the matrix
    //   false: vectors are rows of the matrix
    Matrix3 (const Vector3& rkU, const Vector3& rkV,
        const Vector3& rkW, bool bColumns);
    Matrix3 (const Vector3* akV, bool bColumns);

    // create a tensor product U*V^T
    Matrix3 (const Vector3& rkU, const Vector3& rkV);
    void MakeTensorProduct (const Vector3& rkU,
        const Vector3& rkV);

    // create a diagonal matrix
    Matrix3 (float fM00, float fM11, float fM22);
    void MakeDiagonal (float fM00, float fM11, float fM22);

    // Create rotation matrices (positive angle - counterclockwise).  The
    // angle must be in radians, not degrees.
    Matrix3 (const Vector3& rkAxis, float fAngle);
    void FromAxisAngle (const Vector3& rkAxis, float fAngle);

    // assignment
    Matrix3& operator= (const Matrix3& rkM);
    Matrix3& operator= (const Matrix& rkM);

    // matrix operations
    Matrix3 Inverse () const;
    Matrix3 Adjoint () const;
    float Determinant () const;

    // The matrix must be a rotation for these functions to be valid.  The
    // last function uses Gram-Schmidt orthonormalization applied to the
    // columns of the rotation matrix.  The angle must be in radians, not
    // degrees.
    void ToAxisAngle (Vector3& rkAxis, float& rfAngle) const;
    void Orthonormalize ();

    // The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
    // where yaw is rotation about the Up vector, pitch is rotation about the
    // Right axis, and roll is rotation about the Direction axis.
    bool ToEulerAnglesXYZ (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesXZY (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesYXZ (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesYZX (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesZXY (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesZYX (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    void FromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);
    void FromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);
    void FromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);
    void FromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);
    void FromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);
    void FromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);

    // SLERP (spherical linear interpolation) without quaternions.  Computes
    // R(t) = R0*(Transpose(R0)*R1)^t.  If Q is a rotation matrix with
    // unit-length axis U and angle A, then Q^t is a rotation matrix with
    // unit-length axis U and rotation angle t*A.
    static Matrix3 Slerp (float fT, const Matrix3& rkR0, const Matrix3& rkR1);

    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
    // D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
    // d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
    // The eigenvalues are ordered as d0 <= d1 <= d2.
    void EigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag) const;

    // Singular value decomposition, M = L*S*R, where L and R are orthogonal
    // and S is a diagonal matrix whose diagonal entries are nonnegative.
    void SingularValueDecomposition (Matrix3& rkL, Matrix3& rkS,
        Matrix3& rkR) const;
    void SingularValueComposition (const Matrix3& rkL, const Matrix3& rkS,
        const Matrix3& rkR);

    // factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U
    void QDUDecomposition (Matrix3& rkQ, Matrix3& rkD, Matrix3& rkU) const;

    // special matrices
    static const Matrix3 ZERO;
    static const Matrix3 IDENTITY;

protected:
    // support for eigendecomposition
    void Tridiagonalize (float afDiag[3], float afSubDiag[3]);
    bool QLAlgorithm (float afDiag[3], float afSubDiag[3]);

    // support for singular value decomposition
    static void Bidiagonalize (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);
    static void GolubKahanStep (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);
};

}
