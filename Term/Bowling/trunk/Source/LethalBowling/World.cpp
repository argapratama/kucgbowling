#include "World.h"

#include "Exception.h"
#include "TMath.h"
#include "Physics.h"
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

    floor_.SetMass(0.0f);
    floor_.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    camera_.Apply();
    
    glLoadIdentity();

	float shadow_plane[] = {0.0f, 0.0f, 100.0f, 1.0f};
	Vector3 vec = light_.GetLocation();
	float position[] = {vec.X(), vec.Y(), vec.Z(), 1.0f};
	BuildShadowMatrix(shadow_matrix, position, shadow_plane);
	
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

    glTranslatef(0.0f, 0.0f, 1.5f);
    ball_.Draw();
	for(uint i = 0; i < pins_.size(); ++i)
    {
        pins_[i].Draw();
    }
    
    if(doShowCollisionInfo_)
    {
        glPushMatrix();
        glTranslatef(ball_.Position().X(), ball_.Position().Y(), ball_.Position().Z());
        glutWireSphere(/*2.29934*//*1.9909358*/ 1.1496694, 10, 10);
        glPopMatrix();
    }
	
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

Ball& World::GetBall()
{
    return ball_;
}

Pin& World::GetPin(int number)
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

Ball& World::GetBall2()
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

void World::Update(TimeSpan time, TimeSpan timeDelta)
{
    DoPhysical();
    ball_.Update(time, timeDelta);
    
    // 
    // 
    //

    //if(timeDelta.TotalSeconds() == 0.0)
    //{
    //    timeDelta += TimeSpan(1);
    //}

    //ball_.Update(timeDelta);
    //RigidBody::StepSimulation(timeDelta);
}

vector<Sprite*>& World::Sprites()
{
    return sprites_;
}

vector<Collision>& World::Collisions()
{
    return collisions_;
}


void World::DoPhysical()
{
    DoCollisionDetection();
    DoCollisionResponse();
    
    totalKE_ = 0.0f;
    //for (uint i = 0; i < NUM_TETRA; i++)
    {
        //const RigidTetra& rkTetra = *m_apkTetra[i];
        RigidBody& rkTetra = ball_.GetRigidBody();
        float fInvMass = rkTetra.GetInverseMass();
        const Matrix3& rkInertia = rkTetra.GetWorldInertia();
        const Vector3& rkPos = rkTetra.GetPosition();
        const Vector3& rkLinMom = rkTetra.GetLinearMomentum();
        const Matrix3& rkROrient = rkTetra.GetROrientation();
        const Vector3& rkAngVel = rkTetra.GetAngularVelocity();

        /*m_aspkTetra[i]->Translate() = rkPos;
        m_aspkTetra[i]->Rotate() = rkROrient;*/

        totalKE_ += fInvMass*rkLinMom.Dot(rkLinMom) +
            rkAngVel.Dot(rkInertia*rkAngVel);
    }
    totalKE_ *= 0.5f;

    //// update the scene graph
    //m_spkScene->UpdateGS(0.0f);

    //// next simulation time: see DoMotion for calculation of m_fSimDelta
    //m_fSimTime += m_fSimDelta;
}

void World::DoCollisionDetection()
{
    Contact kContact;
    contacts_.clear();

    // 공 - 바닥 충돌 검사
    // 공 Z 좌표 - Radius와 바닥과의 거리 계산
    ball_.GetRigidBody().Moved() = false;

    float distanceFromFloor = (ball_.GetRigidBody().GetPosition().Z() - ball_.CoveringSphere().Radius()) - floor_.GetPosition().Z();
    if(distanceFromFloor < Math::EPSILON)
    {
        Contact contact;
        contact.A = &floor_;
        contact.B = &ball_.GetRigidBody();
        contact.isVFContact = true;
        contact.N = Vector3::UNIT_Z;
        contact.PA = Vector3::ZERO;
        contact.PB = Vector3(ball_.CoveringSphere().Center() - Vector3(0.0f, 0.0f, -ball_.CoveringSphere().Radius()));

        ball_.GetRigidBody().SetPosition(ball_.GetRigidBody().GetPosition() - distanceFromFloor*contact.N);
        ball_.GetRigidBody().Moved() = true;

        contacts_.push_back(contact);
    }
    

    // 핀 바닥 충돌 검사
    // 핀을 Box로 보고... Box의 각 점(8개)들이 바닥과 위인지 검사
    for(uint i = 0; i < pins_.size(); ++i)
    {
        /*for(uint j = 0; j < 
        Vector3 position = pins_[i].GetRigidBody().GetPosition().Z();*/
    }
    

    //for(uint i = 0; i < pins_.size(); i++)
    //{
    //    
    //    m_apkTetra[i]->Moved() = false;
    //    if ( FarFromBoundary(i) )
    //        continue;

    //    // These checks are done in pairs under the assumption that the tetra 
    //    // have smaller diameters than the separation of opposite boundaries, 
    //    // hence only one of each opposite pair of boundaries may be touched 
    //    // at any one time.
    //    Vector3f akVertex[4];
    //    float afDistance[4];
    //    m_apkTetra[i]->GetVertices(akVertex);
    //    float fRadius = m_apkTetra[i]->GetRadius();
    //    Vector3f kPos = m_apkTetra[i]->GetPosition();

    //    // rear [0] and front[5] boundaries
    //    if ( kPos.X() - fRadius < m_akBLocation[0].X() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = akVertex[j].X() - m_akBLocation[0].X();
    //        TetraBoundaryIntersection(i,0,afDistance,kContact);
    //    }
    //    else if ( kPos.X() + fRadius > m_akBLocation[5].X() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = m_akBLocation[5].X() - akVertex[j].X();
    //        TetraBoundaryIntersection(i,5,afDistance,kContact);
    //    }

    //    // left [1] and right [3] boundaries
    //    if ( kPos.Y() - fRadius < m_akBLocation[1].Y() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = akVertex[j].Y() - m_akBLocation[1].Y();
    //        TetraBoundaryIntersection(i,1,afDistance,kContact);
    //    }
    //    else if ( kPos.Y() + fRadius > m_akBLocation[3].Y() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = m_akBLocation[3].Y() - akVertex[j].Y();
    //        TetraBoundaryIntersection(i,3,afDistance,kContact);
    //    }

    //    // bottom [2] and top [4] boundaries
    //    if ( kPos.Z() - fRadius < m_akBLocation[2].Z() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = akVertex[j].Z() - m_akBLocation[2].Z();
    //        TetraBoundaryIntersection(i,2,afDistance,kContact);
    //    }
    //    else if ( kPos.Z()+fRadius > m_akBLocation[4].Z() )
    //    {
    //        for (j = 0; j < 4; j++)
    //            afDistance[j] = m_akBLocation[4].Z() - akVertex[j].Z();
    //        TetraBoundaryIntersection(i,4,afDistance,kContact);
    //    }
    //}    

    // 공과 핀 충돌 검사


    // 핀과 핀 충돌 검사



    //// test for tetrahedron-tetrahedron collisions
    //m_iLCPCount = 0;
    //for (i = 0; i < NUM_TETRA-1; i++)
    //{
    //    Vector3f akVertex0[4];
    //    m_apkTetra[i]->GetVertices(akVertex0);

    //    for (j = i+1; j < NUM_TETRA; j++)
    //    {
    //        Vector3f akVertex1[4];
    //        m_apkTetra[j]->GetVertices(akVertex1);

    //        if ( !FarApart(i,j) )
    //        {
    //            float fDist = 1.0f;
    //            int iStatusCode = 0;
    //            Vector3f akRes[2];
    //            LCPPolyDist3(4,akVertex0,4,m_akFaces,4,akVertex1,4,m_akFaces,
    //                iStatusCode,fDist,akRes);
    //            m_iLCPCount++;
    //            if ( fDist <= m_fTolerance )
    //            {
    //                // collision with good LCPPolyDist results
    //                Reposition(i,j,kContact);
    //                m_kContact.push_back(kContact);
    //            }
    //        }
    //    }
    //}
}

void World::DoCollisionResponse()
{
    if(!contacts_.empty()) //  m_iNumContacts > 0 )
    {
        vector<float> preRelVel;
        preRelVel.resize(contacts_.size());
        vector<float> impulseMag;
        impulseMag.resize(contacts_.size());

        ComputePreimpulseVelocity(preRelVel);
        ComputeImpulseMagnitude(preRelVel, impulseMag);
        DoImpulse(impulseMag);
    }
}

void World::ComputePreimpulseVelocity(std::vector<float>& preRelVel)
{
    for (uint i = 0; i < contacts_.size(); i++)
    {
        const Contact& rkContact = contacts_[i];
        const RigidBody& rkBodyA = *rkContact.A;
        const RigidBody& rkBodyB = *rkContact.B;

        Vector3 kXA = rkBodyA.GetPosition();
        Vector3 kXB = rkBodyB.GetPosition();
        Vector3 kVA = rkBodyA.GetLinearVelocity();
        Vector3 kVB = rkBodyB.GetLinearVelocity();
        Vector3 kWA = rkBodyA.GetAngularVelocity();
        Vector3 kWB = rkBodyB.GetAngularVelocity();

        Vector3 kRelA = rkContact.PA - kXA;
        Vector3 kRelB = rkContact.PB - kXB;
        Vector3 kVelA = kVA + kWA.Cross(kRelA);
        Vector3 kVelB = kVB + kWB.Cross(kRelB);
        preRelVel[i] = rkContact.N.Dot(kVelB - kVelA);
    }
}

void World::ComputeImpulseMagnitude(std::vector<float>& preRelVel, std::vector<float>& impulseMag)
{
    // coefficient of restitution
    float fRestitution = 0.8f;
    float fTemp = 20.0f * (pins_.size() + 1/*ball count*/);
    if(totalKE_ < fTemp)
    {
        fRestitution *= 0.5f * totalKE_ / fTemp;
    }
    float fCoeff = -(1.0f + fRestitution);

    for (uint i = 0; i < contacts_.size(); i++)
    {
        if(preRelVel[i] < 0.0f)
        {
            const Contact& rkContact = contacts_[i];
            const RigidBody& rkBodyA = *rkContact.A;
            const RigidBody& rkBodyB = *rkContact.B;

            Vector3 kVDiff = rkBodyA.GetLinearVelocity() - rkBodyB.GetLinearVelocity();
            Vector3 kRelA = rkContact.PA - rkBodyA.GetPosition();
            Vector3 kRelB = rkContact.PB - rkBodyB.GetPosition();
            Vector3 kAxN = kRelA.Cross(rkContact.N);
            Vector3 kBxN = kRelB.Cross(rkContact.N);
            Vector3 kJInvAxN = rkBodyA.GetWorldInverseInertia()*kAxN;
            Vector3 kJInvBxN = rkBodyB.GetWorldInverseInertia()*kBxN;
            float fNumer = fCoeff*(rkContact.N.Dot(kVDiff) 
                + rkBodyA.GetAngularVelocity().Dot(kAxN)
                - rkBodyB.GetAngularVelocity().Dot(kBxN));
            float fDenom = rkBodyA.GetInverseMass() + rkBodyB.GetInverseMass()
                + kAxN.Dot(kJInvAxN) + kBxN.Dot(kJInvBxN);
            impulseMag[i] = fNumer/fDenom;
        }
        else
        {
            impulseMag[i] = 0.0f;
        }
    }
}

void World::DoImpulse(std::vector<float>& impulseMag)
{
    for(uint i = 0; i < contacts_.size(); i++)
    {
        Contact& rkContact = contacts_[i];
        RigidBody& rkBodyA = *rkContact.A;
        RigidBody& rkBodyB = *rkContact.B;

        Vector3 kPA = rkBodyA.GetLinearMomentum();
        Vector3 kPB = rkBodyB.GetLinearMomentum();
        Vector3 kLA = rkBodyA.GetAngularMomentum();
        Vector3 kLB = rkBodyB.GetAngularMomentum();

        // update linear/angular momentum/velocity
        Vector3 kImpulse = impulseMag[i]*rkContact.N;
        kPA += kImpulse;
        kPB -= kImpulse;
        Vector3 kRelA = rkContact.PA - rkBodyA.GetPosition();
        kLA += kRelA.Cross(kImpulse);
        Vector3 kRelB = rkContact.PB - rkBodyB.GetPosition();
        kLB -= kRelB.Cross(kImpulse);

        rkBodyA.SetLinearMomentum(kPA);
        rkBodyB.SetLinearMomentum(kPB);
        rkBodyA.SetAngularMomentum(kLA);
        rkBodyB.SetAngularMomentum(kLB);
    }
}


void World::DoVisual()
{
}


Vector3 World::Force (float fTime, float fMass, const Vector3& rkPos,
    const Quaternion& rkQOrient, const Vector3& rkLinMom,
    const Vector3& rkAngMom, const Matrix3& rkOrient,
    const Vector3& rkLinVel, const Vector3& rkAngVel)
{
    const float fGravityConstant = Physics::Gravity;
    const Vector3 kGravityDirection = -Vector3::UNIT_Z;
    return (fGravityConstant*fMass)*kGravityDirection;
}

Vector3 World::Torque (float fTime, float fMass, const Vector3& rkPos,
    const Quaternion& rkQOrient, const Vector3& rkLinMom,
    const Vector3& rkAngMom, const Matrix3& rkOrient,
    const Vector3& rkLinVel, const Vector3& rkAngVel)
{
    return Vector3::ZERO;
}

}