#include "RigidBody.h"

#include "Collision.h"
#include "World.h"
#include "Physics.h"
#include "TMath.h"
#include "Geometric.h"
#include "Edge.h"

namespace Virgin
{

RigidBody::RigidBody ()
{
    // default body is immovable
    m_fMass = Math::MAX_REAL;
    m_fInvMass = (float)0.0;
    m_kInertia = Matrix3::IDENTITY;
    m_kInvInertia = Matrix3::ZERO;
    m_kQOrient = Quaternion::IDENTITY;
    m_kLinMom = Vector3::ZERO;
    m_kAngMom = Vector3::ZERO;
    m_kROrient = Matrix3::IDENTITY;
    m_kLinVel = Vector3::ZERO;
    m_kAngVel = Vector3::ZERO;
}
//----------------------------------------------------------------------------

RigidBody::~RigidBody ()
{
}
//----------------------------------------------------------------------------

Vector3& RigidBody::Position ()
{
    return m_kPos;
}
//----------------------------------------------------------------------------

void RigidBody::SetMass (float fMass)
{
    if ( (float)0.0 < fMass && fMass < Math::MAX_REAL )
    {
        m_fMass = fMass;
        m_fInvMass = ((float)1.0)/fMass;
    }
    else
    {
        // assume the body as immovable
        m_fMass = Math::MAX_REAL;
        m_fInvMass = (float)0.0;
        m_kInertia = Matrix3::IDENTITY;
        m_kInvInertia = Matrix3::ZERO;
        m_kQOrient = Quaternion::IDENTITY;
        m_kLinMom = Vector3::ZERO;
        m_kAngMom = Vector3::ZERO;
        m_kROrient = Matrix3::IDENTITY;
        m_kLinVel = Vector3::ZERO;
        m_kAngVel = Vector3::ZERO;
    }
}
//----------------------------------------------------------------------------

void RigidBody::SetBodyInertia (const Matrix3& rkInertia)
{
    m_kInertia = rkInertia;
    m_kInvInertia = m_kInertia.Inverse();
}
//----------------------------------------------------------------------------

void RigidBody::SetPosition (const Vector3& rkPos)
{
    m_kPos = rkPos;
}
//----------------------------------------------------------------------------

void RigidBody::SetQOrientation (const Quaternion& rkQOrient)
{
    m_kQOrient = rkQOrient;
    m_kQOrient.ToRotationMatrix(m_kROrient);
}
//----------------------------------------------------------------------------

void RigidBody::SetLinearMomentum (const Vector3& rkLinMom)
{
    m_kLinMom = rkLinMom;
    m_kLinVel = m_fInvMass*m_kLinMom;
}
//----------------------------------------------------------------------------

void RigidBody::SetAngularMomentum (const Vector3& rkAngMom)
{
    m_kAngMom = rkAngMom;
    m_kAngVel = m_kROrient*m_kInvInertia*m_kROrient.Transpose()*m_kAngMom;
}
//----------------------------------------------------------------------------

void RigidBody::SetROrientation (const Matrix3& rkROrient)
{
    m_kROrient = rkROrient;
    m_kQOrient.FromRotationMatrix(m_kROrient);
}
//----------------------------------------------------------------------------

void RigidBody::SetLinearVelocity (const Vector3& rkLinVel)
{
    m_kLinVel = rkLinVel;
    m_kLinMom = m_fMass*m_kLinVel;
}
//----------------------------------------------------------------------------

void RigidBody::SetAngularVelocity (const Vector3& rkAngVel)
{
    m_kAngVel = rkAngVel;
    m_kAngMom = m_kROrient*m_kInertia*m_kROrient.Transpose()*m_kAngVel;
}
//----------------------------------------------------------------------------

float RigidBody::GetMass () const
{
    return m_fMass;
}
//----------------------------------------------------------------------------

float RigidBody::GetInverseMass () const
{
    return m_fInvMass;
}
//----------------------------------------------------------------------------

const Matrix3& RigidBody::GetBodyInertia () const
{
    return m_kInertia;
}
//----------------------------------------------------------------------------

const Matrix3& RigidBody::GetBodyInverseInertia () const
{
    return m_kInvInertia;
}
//----------------------------------------------------------------------------

Matrix3 RigidBody::GetWorldInertia () const
{
    return m_kROrient*m_kInertia*m_kROrient.Transpose();
}
//----------------------------------------------------------------------------

Matrix3 RigidBody::GetWorldInverseInertia () const
{
    return m_kROrient*m_kInvInertia*m_kROrient.Transpose();
}
//----------------------------------------------------------------------------

const Vector3& RigidBody::GetPosition () const
{
    return m_kPos;
}
//----------------------------------------------------------------------------

const Quaternion& RigidBody::GetQOrientation () const
{
    return m_kQOrient;
}
//----------------------------------------------------------------------------

const Vector3& RigidBody::GetLinearMomentum () const
{
    return m_kLinMom;
}
//----------------------------------------------------------------------------

const Vector3& RigidBody::GetAngularMomentum () const
{
    return m_kAngMom;
}
//----------------------------------------------------------------------------

const Matrix3& RigidBody::GetROrientation () const
{
    return m_kROrient;
}
//----------------------------------------------------------------------------

const Vector3& RigidBody::GetLinearVelocity () const
{
    return m_kLinVel;
}
//----------------------------------------------------------------------------

const Vector3& RigidBody::GetAngularVelocity () const
{
    return m_kAngVel;
}
//----------------------------------------------------------------------------

void RigidBody::SetInternalForce (const Vector3& rkForce)
{
    m_kInternalForce = rkForce;
}
//----------------------------------------------------------------------------

void RigidBody::SetInternalTorque (const Vector3& rkTorque)
{
    m_kInternalTorque = rkTorque;
}
//----------------------------------------------------------------------------

void RigidBody::SetExternalForce (const Vector3& rkForce)
{
    m_kExternalForce = rkForce;
}
//----------------------------------------------------------------------------

void RigidBody::SetExternalTorque (const Vector3& rkTorque)
{
    m_kExternalTorque = rkTorque;
}
//----------------------------------------------------------------------------

void RigidBody::AppendInternalForce (const Vector3& rkForce)
{
    m_kInternalForce += rkForce;
}
//----------------------------------------------------------------------------

void RigidBody::AppendInternalTorque (const Vector3& rkTorque)
{
    m_kInternalTorque += rkTorque;
}
//----------------------------------------------------------------------------

void RigidBody::Update (float fT, float fDT)
{
    float fHalfDT = ((float)0.5)*fDT;
    float fSixthDT = fDT/((float)6.0);
    float fTpHalfDT = fT + fHalfDT;
    float fTpDT = fT + fDT;

    Vector3 kNewPos, kNewLinMom, kNewAngMom, kNewLinVel, kNewAngVel;
    Quaternion kNewQOrient;
    Matrix3 kNewROrient;

    // A1 = G(T,S0), B1 = S0 + (DT/2)*A1
    Vector3 kA1DXDT = m_kLinVel;
    Quaternion kW = Quaternion((float)0.0,m_kAngVel.X(),
        m_kAngVel.Y(),m_kAngVel.Z());
    Quaternion kA1DQDT = ((float)0.5)*kW*m_kQOrient;
    Vector3 kA1DPDT = m_kExternalForce + m_kInternalForce;
    Vector3 kA1DLDT = m_kExternalTorque + m_kInternalTorque;
    m_kInternalForce = Vector3::ZERO;
    m_kInternalTorque = Vector3::ZERO;
    kNewPos = m_kPos + fHalfDT*kA1DXDT;
    kNewQOrient = m_kQOrient + fHalfDT*kA1DQDT;
    kNewLinMom = m_kLinMom + fHalfDT*kA1DPDT;
    kNewAngMom = m_kAngMom + fHalfDT*kA1DLDT;
    kNewQOrient.ToRotationMatrix(kNewROrient);
    kNewLinVel = m_fInvMass*kNewLinMom;
    kNewAngVel = kNewROrient*m_kInvInertia*kNewROrient.Transpose()*kNewAngMom;

    // A2 = G(T+DT/2,B1), B2 = S0 + (DT/2)*A2
    Vector3 kA2DXDT = kNewLinVel;
    kW = Quaternion((float)0.0,kNewAngVel.X(),kNewAngVel.Y(),
        kNewAngVel.Z());
    Quaternion kA2DQDT = ((float)0.5)*kW*kNewQOrient;
    Vector3 kA2DPDT = Force(fTpHalfDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    Vector3 kA2DLDT = Torque(fTpHalfDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    kNewPos = m_kPos + fHalfDT*kA2DXDT;
    kNewQOrient = m_kQOrient + fHalfDT*kA2DQDT;
    kNewLinMom = m_kLinMom + fHalfDT*kA2DPDT;
    kNewAngMom = m_kAngMom + fHalfDT*kA2DLDT;
    kNewQOrient.ToRotationMatrix(kNewROrient);
    kNewLinVel = m_fInvMass*kNewLinMom;
    kNewAngVel = kNewROrient*m_kInvInertia*kNewROrient.Transpose()*kNewAngMom;

    // A3 = G(T+DT/2,B2), B3 = S0 + DT*A3
    Vector3 kA3DXDT = kNewLinVel;
    kW = Quaternion((float)0.0,kNewAngVel.X(),kNewAngVel.Y(),
        kNewAngVel.Z());
    Quaternion kA3DQDT = ((float)0.5)*kW*kNewQOrient;
    Vector3 kA3DPDT = Force(fTpHalfDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    Vector3 kA3DLDT = Torque(fTpHalfDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    kNewPos = m_kPos + fDT*kA3DXDT;
    kNewQOrient = m_kQOrient + fDT*kA3DQDT;
    kNewLinMom = m_kLinMom + fDT*kA3DPDT;
    kNewAngMom = m_kAngMom + fDT*kA3DLDT;
    kNewQOrient.ToRotationMatrix(kNewROrient);
    kNewLinVel = m_fInvMass*kNewLinMom;
    kNewAngVel = kNewROrient*m_kInvInertia*kNewROrient.Transpose()*kNewAngMom;

    // A4 = G(T+DT,B3), S1 = S0 + (DT/6)*(A1+2*(A2+A3)+A4)
    Vector3 kA4DXDT = kNewLinVel;
    kW = Quaternion((float)0.0,kNewAngVel.X(),kNewAngVel.Y(),
        kNewAngVel.Z());
    Quaternion kA4DQDT = ((float)0.5)*kW*kNewQOrient;
    Vector3 kA4DPDT = Force(fTpDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    Vector3 kA4DLDT = Torque(fTpDT,m_fMass,kNewPos,kNewQOrient,
        kNewLinMom,kNewAngMom,kNewROrient,kNewLinVel,kNewAngVel);
    m_kPos = m_kPos + fSixthDT*(kA1DXDT + ((float)2.0)*(kA2DXDT +
        kA3DXDT) + kA4DXDT);
    m_kQOrient = m_kQOrient + fSixthDT*(kA1DQDT + ((float)2.0)*(kA2DQDT +
        kA3DQDT) + kA4DQDT);
    m_kLinMom = m_kLinMom + fSixthDT*(kA1DPDT + ((float)2.0)*(kA2DPDT +
        kA3DPDT) + kA4DPDT);
    m_kAngMom = m_kAngMom + fSixthDT*(kA1DLDT + ((float)2.0)*(kA2DLDT +
        kA3DLDT) + kA4DLDT);
    m_kQOrient.ToRotationMatrix(m_kROrient);
    m_kLinVel = m_fInvMass*m_kLinMom;
    m_kAngVel = m_kROrient*m_kInvInertia*m_kROrient.Transpose()*m_kAngMom;

    // make force and torque correspond to new time T+DT
    m_kExternalForce = Force(fTpDT,m_fMass,m_kPos,m_kQOrient,m_kLinMom,
        m_kAngMom,m_kROrient,m_kLinVel,m_kAngVel);
    m_kExternalTorque = Torque(fTpDT,m_fMass,m_kPos,m_kQOrient,m_kLinMom,
        m_kAngMom,m_kROrient,m_kLinVel,m_kAngVel);
}
//----------------------------------------------------------------------------

bool& RigidBody::Moved ()
{
    return m_bMoved;
}
//----------------------------------------------------------------------------


}
