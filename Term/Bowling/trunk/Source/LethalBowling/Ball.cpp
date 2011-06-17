#include "Ball.h"

namespace Virgin
{

Sphere& Ball::CoveringSphere()
{
    sphere_.Center() = GetRigidBody().GetPosition();
    return sphere_;
}

}
