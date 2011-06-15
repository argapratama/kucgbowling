#pragma once

//namespace Virgin
//{
//    static void CalcObjectForces(); // 임의의 특정 순간에 개체에 작용하는 힘과 모멘트를 전부 계산한다
//    static void StepSimulation(TimeSpan timeDelta);   // 오일러 방법 이용(적분)
//    
//    static CollisionType CheckGroundPlaneContacts(const RigidBody& rigidBody);    // 접촉
//    static CollisionType CheckForCollisions(bool doCheckPenetration);
//    static CollisionType CheckGroundPlaneCollisions(RigidBody& rigidBody);
//    static CollisionType CheckBoxCollision(const RigidBody& rigidBody1, const RigidBody& rigidBody2);
//    static CollisionType CheckVertexFaceCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2);
//    static CollisionType CheckEdgeEdgeCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2);
//    static CollisionType CheckVertexEdgeCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2);
//
//    static CollisionType IsPenetrating(const RigidBody& rigidBody1, const RigidBody& rigidBody2);
//    static CollisionType IsPenetratingGround(const RigidBody& rigidBody);
//
//    // 충돌 반응 처리
//    static void ResolveCollisions();
//}