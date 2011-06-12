#pragma once

#include "Vector.h"

namespace Virgin
{

enum CollisionType
{
    CollisionType_NoCollision,
    CollisionType_Contact,
    //CollisionType_Overlapped // 뚫고 들어간 경우
};

class Collision
{
public:

    int body1;  // 1번 물체 번호(지평면이면 -1 이용) // * Todo: RigidBody* 로 변경할 수 있을 듯
    int body2;  // 2번 물체 번호(지평면이면 -1 이용)
    Vector3 collisionNormal;    // 2번 물체 면에서 밖으로 나오는 법선 벡터
    Vector3 collisionPoint;     // 접촉점, 전체 좌표
    Vector3 relativeVelocity;   // 상대 속도
    Vector3 relativeAcceleration;   // 상대 가속도
    Vector3 collisionTangent;   // 접선 벡터이고, 접한 평명의 접선 방향 상대 속도와 반대 방향
};

// * Todo: Collision은 vector로 보관할 것

}


