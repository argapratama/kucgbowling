#include "World.h"

#include "Exception.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

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

void BuildShadowMatrix(float matrix[16], float light_position[4], float plane[4])
{

   float dot = plane[0] * light_position[0] + 
               plane[1] * light_position[1] + 
               plane[2] * light_position[2] + 
               plane[3] * light_position[3];

   matrix[ 0] = dot  - light_position[0] * plane[0];
   matrix[ 4] = 0.0f - light_position[0] * plane[1];
   matrix[ 8] = 0.0f - light_position[0] * plane[2];
   matrix[12] = 0.0f - light_position[0] * plane[3];

   matrix[ 1] = 0.0f - light_position[1] * plane[0];
   matrix[ 5] = dot  - light_position[1] * plane[1];
   matrix[ 9] = 0.0f - light_position[1] * plane[2];
   matrix[13] = 0.0f - light_position[1] * plane[3];

   matrix[ 2] = 0.0f - light_position[2] * plane[0];
   matrix[ 6] = 0.0f - light_position[2] * plane[1];
   matrix[10] = dot  - light_position[2] * plane[2];
   matrix[14] = 0.0f - light_position[2] * plane[3];

   matrix[ 3] = 0.0f - light_position[3] * plane[0];
   matrix[ 7] = 0.0f - light_position[3] * plane[1];
   matrix[11] = 0.0f - light_position[3] * plane[2];
   matrix[15] = dot  - light_position[3] * plane[3];

   return;
}

void World::LoadGLTextures() {	
    Image *image1;
    
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
		return;
    }

    if (!ImageLoad("lane.bmp", image1)) {
		return;
    }

    glGenTextures(2, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

	free(image1->data);
	free(image1);
};

void World::Init()
{
	memset(shadow_matrix, 16, 0);
	LoadGLTextures();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClearStencil(0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

void World::DrawFloor()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	/*glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0, 0.0, 3.0);
			
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50.0, 0.0,-3.0);
			
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( 50.0, 0.0,-3.0);
			
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 50.0, 0.0, 3.0);*/
    glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.0, -50.0, 0.0);
			
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0, -50.0, 0.0);
			
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0, 50.0, 0.0);
			
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0, 50.0, 0.0);
	glEnd();
}

void World::DrawString3(void *font, const char *str, float x_position, float y_position, float z_position)
{
     glColor3f(1, 1, 1);
     /*if( z_position == 0.0f )
     {
          glDisable(GL_DEPTH_TEST);
          glPushAttrib( GL_LIGHTING_BIT );
          glDisable(GL_LIGHTING);
          glMatrixMode(GL_PROJECTION);
          glPushMatrix();
           glLoadIdentity();

           glMatrixMode(GL_MODELVIEW);

           glPushMatrix();
     }*/
     glRasterPos3f(x_position, y_position, z_position);
     for(unsigned int i = 0; i < strlen(str); i++)
      glutBitmapCharacter(font, str[i]);

     /*if( z_position == 0.0f )
     {
           glPopMatrix();
           glMatrixMode(GL_PROJECTION);
          glPopMatrix();
          glMatrixMode(GL_MODELVIEW);

          glPopAttrib();
          glEnable(GL_DEPTH_TEST);
     }*/
}


void World::DrawScene()
{
	float shadow_plane[] = {0.0f, 0.0f, 100.0f, 1.0f};
    //float shadow_plane[] = {0.0f, 100.0f, 0.0f, 1.0f};
	Vector3 vec = light_.GetLocation();
	float position[] = {vec.Z, vec.X, vec.Y, 1.0f};
	BuildShadowMatrix(shadow_matrix, position, shadow_plane);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0.0f, -3.6f, 1.0f);
    glTranslatef(1.0f, 0.0f, -3.6f);
	glColorMask(0,0,0,0);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	DrawFloor();
	glEnable(GL_DEPTH_TEST);
	glColorMask(1,1,1,1);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glPushMatrix();
    /*glTranslatef(0.0f, -1.5f, 0.0f);
	glScalef(1.0f, -1.0f, 1.0f);*/
    glTranslatef(0.0f, 0.0f, -1.5f);
	glScalef(1.0f, 1.0f, -1.0f);
	ball_.Draw();
	for(uint i = 0; i < pins_.size(); ++i)
	{
		pins_[i].Draw();
	}
	glPopMatrix();

   glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
   glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
   glPushMatrix();
   //glTranslatef(-0.8f, 0.5f, 0.0f);
   glTranslatef(0.0f,-0.8f, 0.5f);
   glMultMatrixf(shadow_matrix);
   ball_.Draw();
   for(uint i = 0; i < pins_.size(); ++i)
	{
		pins_[i].Draw();
	}
   glPopMatrix();
   glDisable(GL_BLEND);
   glEnable(GL_DEPTH_TEST);

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawFloor();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

	//glTranslatef(0.0f, 1.5f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.5f);
	for(uint i = 0; i < pins_.size(); ++i)
    {
        pins_[i].Draw();
    }

    if(doShowCollisionInfo_)
    {
        glPushMatrix();
        //glTranslatef(ball_.Location().X, ball_.Location().Y, ball_.Location().Z);
        glTranslatef(ball_.Location().Z, ball_.Location().X, ball_.Location().Y);
        glutWireSphere(/*2.29934*//*1.9909358*/ 1.1496694, 10, 10);
        glPopMatrix();
    }
	ball_.Draw();

    //
    // 원점 그리기
    //
   /* static float CenterPointMaterial[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CenterPointMaterial);
    glutSolidSphere(0.5f, 10, 10);*/


    glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glEnd();
        glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glEnd();
        glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
		glEnd();
	glPopMatrix();
    DrawString3(GLUT_BITMAP_8_BY_13, "X Axis", 1, 0, 0);
    DrawString3(GLUT_BITMAP_8_BY_13, "Y Axis", 0, 1, 0);
    DrawString3(GLUT_BITMAP_8_BY_13, "Z Axis", 0, 0, 1);
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
    //if(timeDelta.TotalSeconds() == 0.0)
    //{
    //    timeDelta += TimeSpan(1);
    //}

    //ball_.Update(timeDelta);
    RigidBody::StepSimulation(timeDelta);
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