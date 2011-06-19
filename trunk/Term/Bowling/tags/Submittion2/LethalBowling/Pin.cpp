#include "Pin.h"

namespace Virgin
{

Sphere& Pin::CoveringSphere()
{
    return coverSphere_;
}

Vector3* Pin::GetBox()
{
    return box_;
}

//void Pin::Update(TimeSpan time, TimeSpan timeDelta)
//{
//    Sprite::Update(time, timeDelta);
//
//    // Box 좌표 재계산
//    // * Todo: 회전 계산
//    for(int i = 0; i < BoxVerticeCount; ++i)
//    {
//        const Vector3& position = GetRigidBody().GetPosition();
//
//        box_[i] += position;
//    }
//}

void Pin::GetBox(Vector3 box[8])
{
    // move the box vertices
    for (int i = 0; i < BoxVerticeCount; i++)
        box[i] = GetRigidBody().GetROrientation()*box_[i] + GetRigidBody().GetPosition();
}

void Pin::GetBox(Box& boxOut)
{
    boxOut.Center() = GetRigidBody().GetPosition();
    
    Vector3 boxAxisX = GetRigidBody().GetROrientation() * Vector3::UNIT_X;
    Vector3 boxAxisY = GetRigidBody().GetROrientation() * Vector3::UNIT_Y;
    Vector3 boxAxisZ = GetRigidBody().GetROrientation() * Vector3::UNIT_Z;
    boxOut.Axis(0) = boxAxisX;
    boxOut.Axis(1) = boxAxisY;
    boxOut.Axis(2) = boxAxisZ;
    
    boxOut.Extent(0) = 0.31128f;
    boxOut.Extent(1) = 0.31128f;
    boxOut.Extent(2) = 0.97743f;
}

}


