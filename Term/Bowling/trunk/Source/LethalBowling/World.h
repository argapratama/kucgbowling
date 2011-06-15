#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"
#include "TimeSpan.h"
#include "Ball.h"
#include "Pin.h"
#include "Contact.h"

#include <glut.h>

using namespace std;

namespace Virgin
{

// 이 프로그램의 모든 3D 요소 - 스프라이트, 조명, 옵션 등등 - 가 들어가 있는 Singleton 클래스
class World
{
private:
    World();    // Singleton

public:
    static World& Instance();

    void DrawScene();

    Ball& GetBall();
    Ball& GetBall2();
    Pin& GetPin(int number);
    void ResizePinCount(int count);

    Camera& GetCamera();
    Light& GetLight();

    void ShowCollisionInfo();
    void HideCollisionInfo();
	void Init();
	void DrawObject();
	void DrawFloor();

	void Update(TimeSpan time, TimeSpan timeDelta);

    vector<Sprite*>& Sprites();  
    vector<Collision>& Collisions();

    void DrawString3(void *font, const char *str, float x_position, float y_position, float z_position);
    // 물리 시뮬레이션
    void DoPhysical();

    // 충돌 감지
    void DoCollisionDetection();
    bool FarFromBoundary(int i);
    bool FarApart(int iT0, int iT1);
    bool TetraBoundaryIntersection(int iTetra, int iBoundary, float* afDistance, Contact& rkContact);
    void BuildContactMoveTetra(int iTetra, int iBoundary, int iHitIndex, float fDepthMax, Contact& rkContact);
    void Reposition(int iT0, int iT1, Contact& rkContact);
    bool IsVertex(const Vector3* akVertex, const Vector3& rkRes);
    void CalculateNormal(const Vector3* akVertex, const Vector3& rkRes, Contact& rkContact);
    Vector3 ClosestEdge(const Vector3* akVertex, const Vector3& rkRes,Vector3& rkOtherVertex);

    // 충돌 반응
    void DoCollisionResponse();
    void ComputePreimpulseVelocity(std::vector<float>& preRelVel);
    void ComputeImpulseMagnitude(std::vector<float>& preRelVel, std::vector<float>& impulseMag);
    void DoImpulse(std::vector<float>& impulseMag);
    void DoMotion();
    static float CalcKE(const RigidBody& rigidBody);

    // 시각화
    void DoVisual();

    static Vector3 Force (float fTime, float fMass, const Vector3& rkPos,
        const Quaternion& rkQOrient, const Vector3& rkLinMom,
        const Vector3& rkAngMom, const Matrix3& rkOrient,
        const Vector3& rkLinVel, const Vector3& rkAngVel);

    static Vector3 Torque (float fTime, float fMass, const Vector3& rkPos,
        const Quaternion& rkQOrient, const Vector3& rkLinMom,
        const Vector3& rkAngMom, const Matrix3& rkOrient,
        const Vector3& rkLinVel, const Vector3& rkAngVel);

private:
	vector<Sprite*> sprites_;   // 여기에 모든 스프라이트들을 등록해두어야 함 (충돌 검사 등에 사용)
    vector<Collision> collisions_;
    vector<Contact> contacts_;
    Ball ball_;
    Ball ball2_;
    vector<Pin> pins_;
	float shadow_matrix[16];
    Light light_;

    RigidBody floor_;
    float totalKE_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;
	GLuint texture[4];
    bool doShowCollisionInfo_;
	void LoadGLTextures();
};

}
