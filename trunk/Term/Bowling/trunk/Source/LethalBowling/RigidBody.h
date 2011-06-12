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
    RigidBody();

    static void CalcObjectForces(); // 임의의 특정 순간에 개체에 작용하는 힘과 모멘트를 전부 계산한다
    static CollisionType CheckGroundPlaneContacts(const RigidBody& rigidBody);    // 접촉

    static float CalcDistanceFromPointToPlane(Vector3 pt, Vector3 u, Vector3 v, Vector3 ptOnPlane);
    void StepSimulation(float dtime);   // 오일러 방법 이용(적분)

    // 충돌 반응 처리
    void ResolveCollisions();

    // 

    void Update(TimeSpan timeSpan);

public:
    float mass_;                    // 전체 질량(일정)
    Matrix3 inertia_;               // 질량 관성모멘트, 물체 좌표
    Matrix3 inertiaInverse_;        // 질량 관성모멘트 행렬의 역

    Vector3 location_;              // 물체 위치, 전체 좌표
    Vector3 velocity_;              // 속도, 전체 좌표
    Vector3 velocityBody;           // 속도, 물체 좌표
    Vector3 acceleration_;          // 무게중심 가속도, 전체 공간
    Vector3 angularAcceleration_;   // 각가속도, 물체 좌표
    Vector3 angularVelocity_;       // 각속도, 물체 좌표
    Vector3 eulerAngles_;           // 오일러 각, 물체 좌표
    float speed_;                   // 속력
    Quaternion orientation_;        // 방향, 전체 좌표

    Vector3 forces_;                // 물체에 작용하는 전체 힘
    Vector3 moments_;               // 물체에 작용하는 전체 모멘트(토크)
    Matrix3 ieInverse_;             // 관성 모멘트의 역, 전체 좌표
    float radius_;
    Vector3 vertexList_[8];
};

}
