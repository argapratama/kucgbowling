#include "World.h"

#include "Exception.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>

namespace Virgin
{

World::World()
    : doShowCollisionInfo_(false)
{
}

World& World::Instance()
{
    static World instance;
    return instance;
}

void World::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
    glClearStencil(0);
    glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_BLEND);
	glColor4f(0.49, 0.49, 0.49, 1);
	glStencilFunc(GL_EQUAL, 1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glScalef(1,-1,1);
	glTranslatef(0, 2, 0);
	ball_.Draw();
	glPopMatrix();
	glPushMatrix();
	glScalef(1,-1,1);
	glTranslatef(0, 3, 0);
	
    for(uint i = 0; i < pins_.size(); ++i)
    {
        pins_[i].Draw();
    }

	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	
    ball_.Draw();
	for(uint i = 0; i < pins_.size(); ++i)
    {
        pins_[i].Draw();
    }

    if(doShowCollisionInfo_)
    {
        ball_.DrawCoveringSphere();
    }

    //
    // 원점 그리기
    //
    static float CenterPointMaterial[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, CenterPointMaterial);
    glutSolidSphere(0.5f, 10, 10);
}

Sprite& World::GetBall()
{
    return ball_;
}

Sprite& World::GetPin(int number)
{
    if(number < 0 || number >= static_cast<int>(pins_.size()))
    {
        throw Exception(L"없는 핀 번호입니다.");
    }

    return pins_[number];
}

Camera& World::GetCamera()
{
    return camera_;
}

Sprite& World::GetBall2()
{
    return ball2_;
}

Light& World::GetLight()
{
    return light_;
}

void World::ResizePinCount(int count)
{
    pins_.resize(count);
}

void World::ShowCollisionInfo()
{
    doShowCollisionInfo_ = true;
}

void World::HideCollisionInfo()
{
    doShowCollisionInfo_ = false;
}

void World::Update(TimeSpan timeDelta)
{
    if(timeDelta.TotalSeconds() == 0.0)
    {
        timeDelta += TimeSpan(1);
    }

    ball_.Update(timeDelta);
}

vector<Sprite*>& World::Sprites()
{
    return sprites_;
}

vector<Collision>& World::Collisions()
{
    return collisions_;
}

}
