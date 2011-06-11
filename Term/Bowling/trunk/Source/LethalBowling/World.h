#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"

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

private:
    Sprite ball_;
    Sprite ball2_;
    vector<Sprite> pins_;

    Light light_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;

    bool doShowCollisionInfo_;
};

}
