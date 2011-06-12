#include "Physics.h"

namespace Virgin
{


//#define GRAVITY -32.174f
//#define LINEARDRAGCOEFFICIENT 5.0f
//#define ANGULARDRAGCOEFFICIENT 1200.0f
//#define COLLISIONTOLERANCE 0.9f
//#define COEFFICIENTOFRESTITUTION 0.5f
//#define COEFFICIENTOFRESTITUTIONGROUND 0.025f
//#define VELOCITYTOLERANCE 0.05f
//#define FRICTIONCOEFFICIENT 0.9f

float Physics::Gravity = -32.174f;  // * Todo: -9.8로 수정해볼 것 (ft/s^2 -> m/s^2)
float Physics::LinearDragCoefficient = 5.0f;
float Physics::AngularDragCoefficient = 1200.0f;
float Physics::CollisionTolerance = 0.9f;
float Physics::CoefficientOfRestitution = 0.5f;
float Physics::CoefficientOfRestitutionGround = 0.025f;
float Physics::VelocityTolerance = 0.05f;
float Physics::FrictionCoefficient = 0.3f;
float Physics::AirDensity = 0.0023769f;     // 해수면의 공기 밀도 0.0023769 slug/ft^3 = 1.225 kg/m^3 

bool Physics::DoFriction = true;
}
