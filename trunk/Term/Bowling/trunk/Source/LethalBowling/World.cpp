#include "World.h"

#include "Exception.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>

namespace Virgin
{

World::World()
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
}

Sprite& World::GetBall()
{
    return ball_;
}

Sprite& World::GetPin(int number)
{
    if(number < 0 || number >= pins_.size())
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

}
