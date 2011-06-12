#include "RigidBody.h"

#include "Collision.h"
#include "World.h"
#include "Physics.h"
#include "TMath.h"
#include "Geometric.h"

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
//
//// * 주의: RigidBody::mass_ 가 0.0인 경우 가속도 구할 때 Divide by Zero 예외 발생할 수 있음
//void RigidBody::CalcObjectForces()
//{
//    Vector3 Fb, Mb;
//    Vector3 vDragVector;
//    Vector3 vAngularDragVector;
//    Vector3 ContactForce;
//    Vector3 pt;
//    CollisionType collisionType = CollisionType_NoCollision;
//    //Collision* collisionData;    // 여기서 접촉힘에 사용(Predicated, 대신 World::Collsions() 사용)
//    Vector3 FrictionForce;
//    Vector3 fDir;
//
//    for(uint i = 0; i < World::Instance().Sprites().size(); ++i)
//    {
//        RigidBody& rigidBody = World::Instance().Sprites()[i]->GetRigidBody();
//
//        // 힘과 모멘트를 재설정
//        rigidBody.forces_.Reset();
//        rigidBody.moments_.Reset();
//
//        // 추력 벡터 정의, 무게중심에 작용 
//        // * Predicated, 비행선용
//        /*if(i == CAR)
//        {
//            Thrust.x = 1.0f;
//            Thrust.y = 0.0f;
//            Thrust.z = 0.0f;
//            Thrust *= ThrustForce;
//            Fb += Thrust;
//        }*/
//
//        // 항력 정의
//        vDragVector = -rigidBody.velocityBody;
//        vDragVector.Normalize();
//        Fb += vDragVector * (rigidBody.speed_ * rigidBody.speed_ * Physics::AirDensity * Physics::LinearDragCoefficient * rigidBody.radius_ * rigidBody.radius_);
//
//        vAngularDragVector = -rigidBody.angularVelocity_;
//        vAngularDragVector.Normalize();
//        Mb += vAngularDragVector * (rigidBody.angularVelocity_.Size() * rigidBody.angularVelocity_.Size() * Physics::AirDensity * Physics::AngularDragCoefficient * rigidBody.radius_ * rigidBody.radius_);
//
//        // 힘을 모델 공간에서 전체 공간으로 변환
//        rigidBody.forces_ = rigidBody.orientation_.VRotate(Fb);
//
//        // 중력 작용
//        rigidBody.forces_.Z += Physics::Gravity * rigidBody.mass_;
//
//        // 모멘트 저장
//        rigidBody.moments_ += Mb;
//
//        // 지평면과 접촉하는 상황 처리
//        rigidBody.acceleration_ = rigidBody.forces_ / rigidBody.mass_;
//        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_));
//        
//        vector<Collision>& collisions = World::Instance().Collisions();
//        collisions.clear();
//        collisionType = CheckGroundPlaneContacts(rigidBody);
//        if(collisionType == CollisionType_Contact)
//        {
//            // 접촉 상태임
//            for(uint j = 0; j < collisions.size(); ++j)
//            {
//                ContactForce = (rigidBody.mass_/collisions.size() * (-collisions[j].relativeAcceleration.Dot(collisions[j].collisionNormal))) * collisions[j].collisionNormal;
//                FrictionForce = (ContactForce.Size() * Physics::FrictionCoefficient) * collisions[j].collisionTangent;
//                rigidBody.forces_ += ContactForce;
//                rigidBody.forces_ += FrictionForce;
//                
//                ContactForce = (~rigidBody.orientation_).VRotate(ContactForce);
//                FrictionForce = (~rigidBody.orientation_).VRotate(FrictionForce);
//                pt = collisions[j].collisionPoint - rigidBody.location_;
//                rigidBody.moments_ += pt.Cross(ContactForce);
//                rigidBody.moments_ += pt.Cross(FrictionForce);
//            }
//        }
//    }
//}
//
//CollisionType CheckGroundPlaneCollisions(RigidBody& rigidBody)
//{
//	Vector3 v1[BoxVertexCount];
//	Vector3 tmp;
//	Vector3 u, v;
//	float d;	
//	Vector3 f[4];
//	Vector3 vel1;
//	Vector3 pt1;
//	Vector3 Vr;
//	float Vrn;
//	Vector3 n;
//	CollisionType collisionType = CollisionType_NoCollision;
//
//	//rotate bounding vertices and covert to global coordinates
//	for(int i = 0; i < BoxVertexCount; ++i)
//	{
//		tmp = rigidBody.vertexList_[i];
//        v1[i] = rigidBody.orientation_.VRotate(tmp);
//		v1[i] += rigidBody.location_;
//	}
//
//	//check each vertex of body i against each face of body j
//	for(int i = 0; i < BoxVertexCount; ++i)
//	{
//		// Check the ground plane
//		
//        if(v1[i].Z < Collision::CollisionTolerance)
//		{
//			// calc relative velocity, if <0 collision
//			pt1 = v1[i] - rigidBody.locatoin_;
//
//				
//            vel1 = rigidBody.velocity_ + (rigidBody.vAngularVelocityGlobal^pt1);
//			
//			
//			n.x = 0;
//			n.y = 0;
//			n.z = 1;
//				
//			Vr = vel1;
//			Vrn = Vr * n;
//				
//			if(Vrn < 0.0f)
//			{
//
//				// have a collision, fill the data structure and return
//				assert(NumCollisions < (NUMBODIES*16));
//				if(NumCollisions < (NUMBODIES*16))
//				{
//					CollisionData->body1 = body1;
//					CollisionData->body2 = -1;
//					CollisionData->vCollisionNormal = n;					
//					CollisionData->vCollisionPoint = v1[i];
//					CollisionData->vRelativeVelocity = Vr;
//										
//					CollisionData->vCollisionTangent = (n^Vr)^n;
//					CollisionData->vCollisionTangent.Reverse();					
//					
//					CollisionData->vCollisionTangent.Normalize();
//					CollisionData++;
//					NumCollisions++;
//					status = COLLISION;
//				}				
//			}
//		}
//
//
//	}
//
//	return status;
//}
//
//CollisionType RigidBody::CheckGroundPlaneContacts(const RigidBody& rigidBody)
//{
//    Vector3 v1[BoxVertexCount];
//    Vector3 tmp;
//    Vector3 u, v;
//    float d;
//    Vector3 f[4];
//    Vector3 vel1;
//    Vector3 pt1;
//    Vector3 Vr; // 상대속도(Velocity Relative)
//    float Vrn;
//    Vector3 n;
//    CollisionType collisionType = CollisionType_NoCollision;
//    Vector3 Ar; // 상대가속도(Acceleration Relative)
//    float Arn;
//
//    // 경계 꼭지점을 회전시켜서 전체 좌표로 변환
//    for(int i = 0; i < BoxVertexCount; ++i)
//    {
//        tmp = rigidBody.vertexList_[i];
//        v1[i] = rigidBody.orientation_.VRotate(tmp);
//        v1[i] += rigidBody.location_;
//    }
//
//    // 문제의 각 꼭지점이 지평면에 닿는지 확인
//    for(int i = 0; i < BoxVertexCount; ++i)
//    {
//        // * Todo: 우리는 X, Y가 바닥이 아니고 X, Z 평면이 바닥이므로 수정을 해야 할 듯
//        // u: X축 단위 벡터
//        u.X = 1.0f;
//        u.Y = 0.0f;
//        u.Z = 0.0f;
//        // v: Y축 단위 벡터
//        v.X = 0.0f;
//        v.Y = 1.0f;
//        v.Z = 0.0f;
//        tmp.Reset();
//
//        d = Geometric::DistanceFromPointToPlane(v1[i], u, v, tmp);
//        if(d < Physics::CollisionTolerance)
//        {
//            // 상대 속도 계산
//            pt1 = v1[i] - rigidBody.location_;
//
//            /*vel1 = rigidBody.velocityBody + (rigidBody.angularVelocity_.Cross(pt1));
//            vel1 = rigidBody.orientation_.VRotate(vel1);*/
//            vel1 = rigidBody.velocity_ + (rigidBody.angularVelocityGlobal_.Cross(pt1));
//
//            n = u.Cross(v);
//            n.Normalize();
//
//            Vr = vel1;
//            Vrn = Vr.Dot(n);
//
//            if(Math::Abs(Vrn) <=  Physics::VelocityTolerance /*sqrt(2*32.174*CONTACTTOLERANCE)*/ )    // 정지 // * Todo: 비교값 교체
//            {
//                // 이제 상대 가속도 확인
//                Ar = rigidBody.acceleration_ + (rigidBody.angularVelocity_.Cross(rigidBody.angularVelocity_.Cross(pt1))) + (rigidBody.angularAcceleration_.Cross(pt1));
//
//                Arn = Ar.Dot(n);
//
//                if(Arn <= 0.0f)
//                {
//                    vector<Collision>& collisions = World::Instance().Collisions();
//                    vector<Sprite*>& sprites = World::Instance().Sprites();
//                    
//                    // 접촉한 상태이고, 데이터 구조체를 채우고, 돌아간다
//                    assert(collisions.size() < sprites.size() * BoxVertexCount);
//
//                    if(collisions.size() < sprites.size() * BoxVertexCount)
//                    {
//                        Collision collision;
//                        collision.body1 = const_cast<RigidBody*>(&rigidBody);
//                        collision.body2 = nullptr;
//                        collision.collisionNormal = n;
//                        collision.collisionPoint = v1[i];
//                        collision.relativeVelocity = Vr;
//                        collision.relativeAcceleration = Ar;
//                        collision.collisionTangent = -(Vr - ((Vr.Dot(n)) * n));
//                        // 접선 벡터의 방향이 음이라는 것은 접선 속도의 반대 방향을 나타냄
//                        // 나중에 마찰을 처리하기 위함
//
//                        collision.collisionTangent.Normalize();
//                        
//                        collisions.push_back(collision);
//                        collisionType = CollisionType_Contact;
//                    }
//                }
//            }
//        }
//    }
//
//    return collisionType;
//}
//
//// 오일러 방법 이용(적분)
//void RigidBody::StepSimulation(TimeSpan timeDelta)
//{
//    Vector3 Ae; // 가속도
//    float dt = static_cast<float>(timeDelta.TotalSeconds());
//
//    // 모든 개체에 작용하는 힘과 모멘트를 전부 계산
//    CalcObjectForces();
//
//tryagain:
//
//    // 적분
//    vector<Sprite*>& sprites = World::Instance().Sprites();
//    for(uint i = 0; i < sprites.size(); ++i)
//    {
//        RigidBody& rigidBody = sprites[i]->GetRigidBody();
//
//        // 전체 좌표에서 가속도 계산
//        Ae = rigidBody.forces_ / rigidBody.mass_;
//        rigidBody.acceleration_ = Ae;
//
//        // 전체 좌표에서 속도 계산
//        rigidBody.velocity_ += Ae * dt;
//
//        // 전체 좌표에서 위치 계산
//        rigidBody.location_ += rigidBody.velocity_ * dt;
//
//        // 회전운동 처리
//        float mag;
//        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - (rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_)));
//        rigidBody.angularVelocity_ = rigidBody.angularAcceleration_ * dt;
//
//        // 회전 사원수 새로 계산
//        rigidBody.orientation_ += (rigidBody.orientation_ * rigidBody.angularVelocity_) * (0.5f * dt);
//
//        // 방향 사원수 규격화
//        mag = rigidBody.orientation_.Size();
//        if(mag != 0.0)
//        {
//            rigidBody.orientation_ /= mag;
//        }
//
//        // 물체 공간에서 속도 계산 (we'll need this to calculate lift and drag forces)
//        rigidBody.velocityBody = (~rigidBody.orientation_).VRotate(rigidBody.velocity_);
//
//		// get the angular velocity in global coords:
//        rigidBody.angularVelocityGlobal_ = rigidBody.orientation_.VRotate(rigidBody.angularVelocity_);
//
//		// get the angular acceleration in global coords:
//        rigidBody.angularAccelerationGlobal_ = rigidBody.orientation_.VRotate(rigidBody.angularAcceleration_);
//		
//		// Get the inverse intertia tensor in global coordinates
//		Matrix3 R, RT;		
//		R = rigidBody.orientation_.ToMatrix();
//		RT = R.Transpose();
//        rigidBody.ieInverse_ = R * rigidBody.inertiaInverse_ * RT;
//
//        // 속력 계산
//        rigidBody.speed_ = rigidBody.velocity_.Size();
//
//        // 오일러 각 구하기
//        Vector3 u;
//
//        u = rigidBody.orientation_.ToEulerAngles();
//        rigidBody.eulerAngles_.X = u.X; // roll
//        rigidBody.eulerAngles_.Y = u.Y; // pitch
//        rigidBody.eulerAngles_.Z = u.Z; // yaw
//    }
//
//    // 충돌 처리
//    CollisionType collisionType = CheckForCollisions(Geometric::DoPenetrationCheck);
//    if(collisionType == CollisionType_Collision)
//    {
//    }
//    else if(collisionType == CollisionType_Penetrating)
//    {
//    }
//    
//    // * Todo: 관통 시 timeDelta 1/2로 재연산
//}
//
//CollisionType RigidBody::CheckForCollisions(bool doCheckPenetration)
//{
//    CollisionType collisionType = CollisionType_NoCollision;
//	Vector3 d;  // 강체 1, 2 사이의 벡터 차(뺄셈;거리)
//	pCollision	pCollisionData;
//	
//    CollisionType check = CollisionType_NoCollision;
//
//    vector<Collision>& collisions = World::Instance().Collisions();
//    collisions.clear();
//	
//	// check object collisions with each other	
//    vector<Sprite*>& sprites = World::Instance().Sprites();
//	for(uint i = 0; i < sprites.size(); ++i)
//	{
//        RigidBody& rigidBody1 = sprites[i]->GetRigidBody();
//
//		for(uint j = 0; j < sprites.size(); ++j)
//        {
//            if(i == j) // don't check object against itself
//            {
//                continue;
//            }
//			
//            RigidBody& rigidBody2 = sprites[i]->GetRigidBody();
//
//            // do a bounding sphere check first	
//            d = rigidBody1.location_ - rigidBody2.location_;
//			if(d.Size() < (rigidBody1.radius_ + rigidBody2.radius_))				
//			{
//                // possible collision
//				if(doCheckPenetration)
//                {
//					check = IsPenetrating(rigidBody1, rigidBody2);
//                }
//
//				if(check == CollisionType_Penetrating)
//				{
//					collisionType = CollisionType_Penetrating;
//					break;
//				} 
//                else 
//                {
//					check = CheckBoxCollision(pCollisionData, i, j);
//					if(check == COLLISION)
//					{
//						status = COLLISION;
//						pCollisionData++;
//					}
//				}
//			}
//			
//        }
//
//		if(status == PENETRATING) 
//			break;
//	}
//
//	if(status != PENETRATING)
//	{
//		// check object collisions with the ground	
//		for(i=0; i<NUMBODIES; i++)
//		{
//			if(doCheckPenetration)
//				check = IsPenetratingGround(i);
//			if(check == PENETRATING)
//			{
//				status = PENETRATING;
//				break;
//			} else {
//				check = CheckGroundPlaneCollisions(pCollisionData, i);
//				if(check == COLLISION)
//				{
//					status = COLLISION;
//					pCollisionData++;
//				}
//			}
//		}
//	}
//	
//	return status;
//}
//
//CollisionType IsPenetrating(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
//{
//	Vector3 v1[BoxVertexCount];
//	Vector3 v2[BoxVertexCount];
//	Vector3 tmp;
//	Vector3 u, v;
//	float d;	
//	Vector3 f[4];
//	Vector3 vel1, vel2;
//	Vector3 pt1, pt2;
//	Vector3 Vr;	
//	Vector3 n;
//	CollisionType collisionType = CollisionType_NoCollision;
//	bool outside = false;
//
//	//rotate bounding vertices and covert to global coordinates
//    vector<Sprite*>& sprites = World::Instance().Sprites();
//	for(int i = 0; i < BoxVertexCount; ++i)
//	{
//		tmp = rigidBody1.vertexList_[i];
//        v1[i] = rigidBody1.orientation_.VRotate(tmp);
//        v1[i] += rigidBody1.location_;
//
//		tmp = rigidBody2.vertexList_[i];
//        v2[i] = rigidBody2.orientation_.VRotate(tmp);
//        v2[i] = rigidBody2.location_;
//	}
//	
//	//check each vertex of body 1 against each face of body 2
//	for(int i = 0; i < BoxVertexCount; ++i)
//	{
//		outside = false;
//
//		// Front face of body 2:
//		u = v2[1] - v2[0];
//		v = v2[3] - v2[0];
//		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//		if(d > -Collision::PenetrationTolerance) 
//        {
//			outside = true;
//        }
//	
//		// Aft face of body 2:   
//		v = v2[6] - v2[7];
//		u = v2[4] - v2[7];
//        d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//        if(d > -Collision::PenetrationTolerance) 
//        {
//			outside = true;
//        }
//
//		// Top face of body 2:  
//		v = v2[2] - v2[6];
//		u = v2[5] - v2[6];
//		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//		if(d > -Collision::PenetrationTolerance) 
//        {
//            outside = true;
//        }
//
//		// Bottom face of body 2:
//		u = v2[0] - v2[4];
//		v = v2[7] - v2[4];
//		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//		if(d > -Collision::PenetrationTolerance) 
//        {
//			outside = true;
//        }
//
//		// Left face of body 2:   
//		v = v2[5] - v2[4];
//		u = v2[0] - v2[4];
//		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//		if(d > -Collision::PenetrationTolerance) 
//        {
//			outside = true;
//        }
//
//		// Right face of body 2:
//		u = v2[6] - v2[2];
//		v = v2[3] - v2[2];
//		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
//		if(d > -Collision::PenetrationTolerance) 
//        {
//			outside = true;
//        }
//
//		if(!outside)
//        {
//			return CollisionType_Penetrating;
//        }
//			
//	}
//
//    return collisionType;
//}
//
//CollisionType RigidBody::CheckBoxCollision(pCollision CollisionData, int body1, int body2)
//{
//	CollisionType status1 = CollisionType_NoCollision;
//	CollisionType status2 = CollisionType_NoCollision;
//	CollisionType status3 = CollisionType_NoCollision;
//	
//	status1 = CheckVertexFaceCollisions(CollisionData, body1, body2);
//	status2 = CheckVertexEdgeCollisions(CollisionData, body1, body2);
//	status3 = CheckEdgeEdgeCollisions(CollisionData, body1, body2);
//
//	if((status1 == PENETRATING) || (status2 == PENETRATING) || (status3 == PENETRATING))
//    {
//		return CollisionType_Penetrating;
//    }
//	else if((status1 == COLLISION) || (status2 == COLLISION) || (status3 == COLLISION))
//    {
//        return CollisionType_Collision;
//    }
//	else
//    {
//        return CollisionType_NoCollision;
//    }
//
//}
//
//
//CollisionType CheckVertexFaceCollisions(pCollision CollisionData, int body1, int body2)
//{
//	int		i;
//	Vector	v1[8];
//	Vector	v2[8];
//	Vector	tmp;
//	Vector	u, v;
//	float	d;	
//	Vector	f[4];
//	Vector	vel1, vel2;
//	Vector	pt1, pt2;
//	Vector	Vr;
//	float	Vrn;
//	Vector	n;
//	int	status = NOCOLLISION;
//	bool	inside = true;
//
//	//rotate bounding vertices and covert to global coordinates
//	for(i=0; i<8; i++)
//	{
//		tmp = Bodies[body1].vVertexList[i];
//		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
//		v1[i] += Bodies[body1].vPosition;
//
//		tmp = Bodies[body2].vVertexList[i];
//		v2[i] = QVRotate(Bodies[body2].qOrientation, tmp);
//		v2[i] += Bodies[body2].vPosition;
//	}
//
//	//check each vertex of body i against each face of body j
//	for(i=0; i<8; i++)
//	{
//		inside = true;
//		// Front face of body 2:
//		u = v2[1]-v2[0];
//		v = v2[3]-v2[0];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[0]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[0]; 
//			f[1] = v2[1]; 
//			f[2] = v2[2]; 
//			f[3] = v2[3]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//				
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//				
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//
//				if(Vrn < 0.0f)
//				{
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;				
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//
//
//		// Aft face of body 2:
//		v = v2[6]-v2[7];
//		u = v2[4]-v2[7];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[7]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[7]; 
//			f[1] = v2[6]; 
//			f[2] = v2[5]; 
//			f[3] = v2[4]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//				
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//				
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//
//		// Top face of body 2:
//		v = v2[2]-v2[6];
//		u = v2[5]-v2[6];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[6]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[6]; 
//			f[1] = v2[2]; 
//			f[2] = v2[1]; 
//			f[3] = v2[5]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//			
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//				
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;
//
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//
//		// Bottom face of body 2:
//		u = v2[0]-v2[4];
//		v = v2[7]-v2[4];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[4]; 
//			f[1] = v2[0]; 
//			f[2] = v2[3]; 
//			f[3] = v2[7]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//			
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//				
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//						
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//
//		// Left face of body 2:???
//		v = v2[5]-v2[4];
//		u = v2[0]-v2[4];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[4]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[4]; 
//			f[1] = v2[5]; 
//			f[2] = v2[1]; 
//			f[3] = v2[0]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//			
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//			
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//						
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//
//		// Right face of body 2:
//		u = v2[6]-v2[2];
//		v = v2[3]-v2[2];
//		d = CalcDistanceFromPointToPlane(v1[i], u, v, v2[2]);		
//		if(d < COLLISIONTOLERANCE)
//		{
//			f[0] = v2[2]; 
//			f[1] = v2[6]; 
//			f[2] = v2[7]; 
//			f[3] = v2[3]; 
//			if(IsPointOnFace(v1[i], f))
//			{	
//				// calc relative velocity, if <0 collision
//				pt1 = v1[i] - Bodies[body1].vPosition;
//				pt2 = v1[i] - Bodies[body2].vPosition;
//
//				
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//				
//				n = u^v;
//				n.Normalize();
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = v1[i];
//						CollisionData->vRelativeVelocity = Vr;
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//						
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}		
//		
//	}
//
//	return status;
//
//}
//
//CollisionType CheckEdgeEdgeCollisions(pCollision CollisionData, int body1, int body2)
//{
//	int		i;
//	Vector	v1[8];
//	Vector	v2[8];
//	Vector	tmp;
//	Vector	u, v;
//	
//	Vector	f[4];
//	Vector	vel1, vel2;
//	Vector	pt1, pt2;
//	Vector	Vr;
//	float	Vrn;
//	Vector	n;
//	int	status = NOCOLLISION;
//	bool	inside = true;
//	Edge	e[12];
//	int		j;
//	float	t, tx, ty, tz;
//	float	num, denom;
//	int		a1, b1;
//	int		a2, b2;
//	Vector  vE1, vE2;
//	
//
//	//rotate bounding vertices and covert to global coordinates
//	for(i=0; i<8; i++)
//	{
//		tmp = Bodies[body1].vVertexList[i];
//		v1[i] = QVRotate(Bodies[body1].qOrientation, tmp);
//		v1[i] += Bodies[body1].vPosition;
//
//		tmp = Bodies[body2].vVertexList[i];
//		v2[i] = QVRotate(Bodies[body2].qOrientation, tmp);
//		v2[i] += Bodies[body2].vPosition;
//	}
//
//	e[0].a = 0;		e[0].b = 1;
//	e[1].a = 1;		e[1].b = 2;
//	e[2].a = 2;		e[2].b = 3;
//	e[6].a = 3;		e[6].b = 0;	
//	e[3].a = 4;		e[3].b = 5;
//	e[4].a = 5;		e[4].b = 6;
//	e[5].a = 6;		e[5].b = 7;	
//	e[7].a = 7;		e[7].b = 4;
//	e[8].a = 1;		e[8].b = 5;
//	e[9].a = 2;		e[9].b = 6;
//	e[10].a = 3;	e[10].b = 7;
//	e[11].a = 0;	e[11].b = 4;
//
//	//check each edge of body 1 against each edge of body 2
//	for(i=0; i<12; i++)
//	{
//		a1 = e[i].a;
//		b1 = e[i].b;
//		for(j=0; j<12; j++)
//		{
//			// calc tx
//			a2 = e[j].a;
//			b2 = e[j].b;
//			num = v1[a1].x - v2[a2].x;
//			denom = v2[b2].x - v2[a2].x - v1[b1].x + v1[a1].x;
//			
//			if(fabs(denom) < tol)
//				tx = -1; // parallel in x direction			
//			else
//				tx = num / denom;
//
//			// calc ty
//			a2 = e[j].a;
//			b2 = e[j].b;
//			num = v1[a1].y - v2[a2].y;
//			denom = v2[b2].y - v2[a2].y - v1[b1].y + v1[a1].y;
//			
//			if(fabs(denom) < tol)
//				ty = -1; // parallel in x direction			
//			else
//				ty = num / denom;
//
//			// calc tz
//			a2 = e[j].a;
//			b2 = e[j].b;
//			num = v1[a1].z - v2[a2].z;
//			denom = v2[b2].z - v2[a2].z - v1[b1].z + v1[a1].z;
//			
//			if(fabs(denom) < tol)
//				tz = -1; // parallel in x direction			
//			else
//				tz = num / denom;
//
//			// test for intersection
//			t = tx;
//			if( ((fabs(t-ty)<PENETRATIONTOLERANCE/2) && (fabs(t-tz)<PENETRATIONTOLERANCE/2)) && (t>=0) && (t <=1))
//			{ // have intersection
//
//				tmp.x = v1[a1].x + (v1[b1].x - v1[a1].x) * t;
//				tmp.y = v1[a1].y + (v1[b1].y - v1[a1].y) * t;
//				tmp.z = v1[a1].z + (v1[b1].z - v1[a1].z) * t;				
//				
//				// calc relative velocity, if <0 collision
//				pt1 = tmp - Bodies[body1].vPosition;
//				pt2 = tmp - Bodies[body2].vPosition;
//
//			
//				vel1 = Bodies[body1].vVelocity + (Bodies[body1].vAngularVelocityGlobal^pt1);
//				vel2 = Bodies[body2].vVelocity + (Bodies[body2].vAngularVelocityGlobal^pt2);
//
//			
//				vE1 = v1[b1] - v1[a1];
//				vE2 = v2[b2] - v2[a2];
//				
//				n = vE1^vE2;
//				
//				n.Normalize();
//				
//				
//				Vr = (vel1 - vel2);
//				Vrn = Vr * n;
//				
//				if(Vrn < 0.0f)
//				{
//
//					// have a collision, fill the data structure and return
//					assert(NumCollisions < (NUMBODIES*16));
//					if(NumCollisions < (NUMBODIES*16))
//					{
//						CollisionData->body1 = body1;
//						CollisionData->body2 = body2;
//						CollisionData->vCollisionNormal = n;					
//						CollisionData->vCollisionPoint = tmp;
//						CollisionData->vRelativeVelocity = Vr;
//						
//						
//						CollisionData->vCollisionTangent = (n^Vr)^n;
//						
//
//						CollisionData->vCollisionTangent.Normalize();
//						CollisionData++;
//						NumCollisions++;
//						status = COLLISION;
//					}									
//				}
//			}
//		}
//	}
//
//	
//	return status;
//}
//
//CollisionType CheckVertexEdgeCollisions(pCollision CollisionData, int body1, int body2)
//{
//	int	status = NOCOLLISION;
//	
//	return status;
//}
//
//
//void RigidBody::ResolveCollisions()
//{
//	int		i;
//	double	j;
//	Vector	pt1, pt2, vB1V, vB2V, vB1AV, vB2AV;
//	float	fCr = COEFFICIENTOFRESTITUTION;	
//	int		b1, b2;
//	float	Vrt;
//	float	mu = FRICTIONCOEFFICIENT;
//	bool	dofriction = DOFRICTION;
//
//	for(i=0; i<NumCollisions; i++)
//	{
//		b1 = Collisions[i].body1;
//		b2 = Collisions[i].body2;
//
//		if( (b1 != -1) && (b1 != b2) )
//		{
//			if(b2 != -1) // not ground plane
//			{
//				pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
//				pt2 = Collisions[i].vCollisionPoint - Bodies[b2].vPosition;
//				
//				// calculate impulse
//				j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
//					( (1/Bodies[b1].fMass + 1/Bodies[b2].fMass) +
//					(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mIeInverse )^pt1) ) +
//					(Collisions[i].vCollisionNormal * ( ( (pt2 ^ Collisions[i].vCollisionNormal)*Bodies[b2].mIeInverse )^pt2) )
//					);
//			
//				Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
//	
//				if(fabs(Vrt) > 0.0 && dofriction) {
//					Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
//					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mIeInverse;
//					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
//
//					Bodies[b2].vVelocity += ((-j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)) / Bodies[b2].fMass;										
//					Bodies[b2].vAngularVelocityGlobal += (pt2 ^ ((-j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b2].mIeInverse;
//					Bodies[b2].vAngularVelocity = QVRotate(~Bodies[b2].qOrientation, Bodies[b2].vAngularVelocityGlobal);
//
//				} else {					
//					// apply impulse
//					Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;										
//					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mIeInverse;
//					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
//					
//					Bodies[b2].vVelocity -= (j * Collisions[i].vCollisionNormal) / Bodies[b2].fMass;										
//					Bodies[b2].vAngularVelocityGlobal -= (pt2 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b2].mIeInverse;
//					Bodies[b2].vAngularVelocity = QVRotate(~Bodies[b2].qOrientation, Bodies[b2].vAngularVelocityGlobal);
//				}
//
//			} else { // ground plane
//				fCr = COEFFICIENTOFRESTITUTIONGROUND;
//				pt1 = Collisions[i].vCollisionPoint - Bodies[b1].vPosition;
//				
//				// calculate impulse
//				j = (-(1+fCr) * (Collisions[i].vRelativeVelocity*Collisions[i].vCollisionNormal)) /						
//					( (1/Bodies[b1].fMass) +
//					(Collisions[i].vCollisionNormal * ( ( (pt1 ^ Collisions[i].vCollisionNormal)*Bodies[b1].mIeInverse )^pt1)));
//			
//				Vrt = Collisions[i].vRelativeVelocity * Collisions[i].vCollisionTangent;
//	
//				if(fabs(Vrt) > 0.0 && dofriction) {
//					Bodies[b1].vVelocity += ( (j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent) ) / Bodies[b1].fMass;										
//					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ ((j * Collisions[i].vCollisionNormal) + ((mu * j) * Collisions[i].vCollisionTangent)))*Bodies[b1].mIeInverse;
//					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
//				} else {					
//					// apply impulse
//					Bodies[b1].vVelocity += (j * Collisions[i].vCollisionNormal) / Bodies[b1].fMass;			
//					Bodies[b1].vAngularVelocityGlobal += (pt1 ^ (j * Collisions[i].vCollisionNormal))*Bodies[b1].mIeInverse;
//					Bodies[b1].vAngularVelocity = QVRotate(~Bodies[b1].qOrientation, Bodies[b1].vAngularVelocityGlobal);
//				}
//		
//			}
//		}
//	}
//}
//

}
