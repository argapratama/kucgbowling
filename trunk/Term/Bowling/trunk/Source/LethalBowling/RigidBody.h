#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"
#include "TimeSpan.h"
#include "Collision.h"

namespace Virgin
{

class RigidBody
{
public:
    // construction and destruction
    RigidBody ();  // uninitialized, use SetState before using
    virtual ~RigidBody ();

    // set/get position
    Vector3& Position ();

    // set rigid body state
    void SetMass (float fMass);
    void SetBodyInertia (const Matrix3& rkInertia);
    void SetPosition (const Vector3& rkPos);
    void SetQOrientation (const Quaternion& rkQOrient);
    void SetLinearMomentum (const Vector3& rkLinMom);
    void SetAngularMomentum (const Vector3& rkAngMom);
    void SetROrientation (const Matrix3& rkROrient);
    void SetLinearVelocity (const Vector3& rkLinVel);
    void SetAngularVelocity (const Vector3& rkAngVel);

    // get rigid body state
    float GetMass () const;
    float GetInverseMass () const;
    const Matrix3& GetBodyInertia () const;
    const Matrix3& GetBodyInverseInertia () const;
    Matrix3 GetWorldInertia () const;
    Matrix3 GetWorldInverseInertia () const;
    const Vector3& GetPosition () const;
    const Quaternion& GetQOrientation () const;
    const Vector3& GetLinearMomentum () const;
    const Vector3& GetAngularMomentum () const;
    const Matrix3& GetROrientation () const;
    const Vector3& GetLinearVelocity () const;
    const Vector3& GetAngularVelocity () const;

    // force/torque function format
    typedef Vector3 (*Function)
    (
        float,                    // time of application
        float,                    // mass
        const Vector3&,    // position
        const Quaternion&, // orientation
        const Vector3&,    // linear momentum
        const Vector3&,    // angular momentum
        const Matrix3&,    // orientation
        const Vector3&,    // linear velocity
        const Vector3&     // angular velocity
    );

    // for computing external forces and torques
    void SetInternalForce (const Vector3& rkForce);
    void SetInternalTorque (const Vector3& rkTorque);
    void SetExternalForce (const Vector3& rkForce);
    void SetExternalTorque (const Vector3& rkTorque);

    // for computing internal forces and torques
    void AppendInternalForce (const Vector3& rkForce);
    void AppendInternalTorque (const Vector3& rkTorque);

    // Runge-Kutta fourth-order differential equation solver
    void Update (float fT, float fDT);
    bool& Moved ();

    // force and torque functions
    Function Force;
    Function Torque;

protected:
    // constant quantities (matrices in body coordinates)
    float m_fMass, m_fInvMass;
    Matrix3 m_kInertia, m_kInvInertia;

    // state variables
    Vector3 m_kPos;         // position
    Quaternion m_kQOrient;  // orientation
    Vector3 m_kLinMom;      // linear momentum
    Vector3 m_kAngMom;      // angular momentum

    // derived state variables
    Matrix3 m_kROrient;    // orientation matrix
    Vector3 m_kLinVel;     // linear velocity
    Vector3 m_kAngVel;     // angular velocity

    bool m_bMoved;

    // external force/torque at current time of simulation
    Vector3 m_kExternalForce, m_kExternalTorque;

    // Resting contact force/torque. Initially zero, changed by simulator
    // before call to ODE solver, ODE solver uses for motion of bodies,
    // then reset to zero for next pass.
    Vector3 m_kInternalForce, m_kInternalTorque;
};

}
