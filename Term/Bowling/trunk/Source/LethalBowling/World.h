#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"
#include "TimeSpan.h"
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

    Sprite& GetBall();
    Sprite& GetBall2();
    Sprite& GetPin(int number);
    void ResizePinCount(int count);

    Camera& GetCamera();
    Light& GetLight();

    void ShowCollisionInfo();
    void HideCollisionInfo();
	void Init();
	void DrawObject();
	void DrawFloor();

	void Update(TimeSpan timeDelta);

    vector<Sprite*>& Sprites();  
    vector<Collision>& Collisions();
private:
	vector<Sprite*> sprites_;   // 여기에 모든 스프라이트들을 등록해두어야 함 (충돌 검사 등에 사용)
    vector<Collision> collisions_;
    Sprite ball_;
    Sprite ball2_;
    vector<Sprite> pins_;
	float shadow_matrix[16];
    Light light_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;
	GLuint texture[4];
    bool doShowCollisionInfo_;
	void LoadGLTextures();
};

}
