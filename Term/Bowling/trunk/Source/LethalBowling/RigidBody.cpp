#include "RigidBody.h"

#include "Collision.h"
#include "World.h"
#include "Physics.h"
#include "TMath.h"

namespace Virgin
{

RigidBody::RigidBody()
    : mass_(0.0f)
    , speed_(0.0f)
    , radius_(0.0f)
{
}

void RigidBody::Update(TimeSpan timeSpan)
{
    float dTime = static_cast<float>(timeSpan.TotalSeconds());

    // 일단 테스트용으로 속도만 처리, 변위에 영향을 주게끔 함
    location_ += velocity_ * speed_ * dTime;
}

// * 주의: RigidBody::mass_ 가 0.0인 경우 가속도 구할 때 Divide by Zero 예외 발생할 수 있음
void RigidBody::CalcObjectForces()
{
    Vector3 Fb, Mb;
    Vector3 vDragVector;
    Vector3 vAngularDragVector;
    Vector3 ContactForce;
    Vector3 pt;
    CollisionType collisionType = CollisionType_NoCollision;
    //Collision* collisionData;    // 여기서 접촉힘에 사용(Predicated, 대신 World::Collsions() 사용)
    Vector3 FrictionForce;
    Vector3 fDir;

    for(uint i = 0; i < World::Instance().Sprites().size(); ++i)
    {
        RigidBody& rigidBody = World::Instance().Sprites()[i]->GetRigidBody();

        // 힘과 모멘트를 재설정
        rigidBody.forces_.Reset();
        rigidBody.moments_.Reset();

        // 추력 벡터 정의, 무게중심에 작용 
        // * Predicated, 비행선용
        /*if(i == CAR)
        {
            Thrust.x = 1.0f;
            Thrust.y = 0.0f;
            Thrust.z = 0.0f;
            Thrust *= ThrustForce;
            Fb += Thrust;
        }*/

        // 항력 정의
        vDragVector = -rigidBody.velocityBody;
        vDragVector.Normalize();
        Fb += vDragVector * (rigidBody.speed_ * rigidBody.speed_ * Physics::AirDensity * Physics::LinearDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        vAngularDragVector = -rigidBody.angularVelocity_;
        vAngularDragVector.Normalize();
        Mb += vAngularDragVector * (rigidBody.angularVelocity_.Size() * rigidBody.angularVelocity_.Size() * Physics::AirDensity * Physics::AngularDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        // 힘을 모델 공간에서 전체 공간으로 변환
        rigidBody.forces_ = rigidBody.orientation_.VRotate(Fb);

        // 중력 작용
        rigidBody.forces_.Z += Physics::Gravity * rigidBody.mass_;

        // 모멘트 저장
        rigidBody.moments_ += Mb;

        // 지평면과 접촉하는 상황 처리
        rigidBody.acceleration_ = rigidBody.forces_ / rigidBody.mass_;
        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_));
        
        vector<Collision>& collisions = World::Instance().Collisions();
        collisions.clear();
 //       collisionType = CheckGroundPlaneContacts(rigidBody);
        if(collisionType == CollisionType_Contact)
        {
            // 접촉 상태임
            for(uint j = 0; j < collisions.size(); ++j)
            {
                //ContactForce = rigidBody.mass_/collisions.size() 
            }
        }
    }

}

}
