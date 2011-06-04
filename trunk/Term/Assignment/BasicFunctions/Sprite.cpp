#include "Sprite.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLAUX.H>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

namespace Virgin
{

Sprite::Sprite(void)
    : rotateAngle_(0.0)
    , scales_(1.0, 1.0, 1.0)
    , pivotPointScales_(1.0, 1.0, 1.0)
    , meshMode_(MeshMode_QuadMesh)
    , doDrawNormal_(false)
    , doDrawTexture_(true)
{
}


Sprite::~Sprite(void)
{
}

AUX_RGBImageRec* LoadBitmap(String filePath)					// Loads A Bitmap Image
{
    if(filePath.empty())								// Make Sure A Filename Was Given
	{
		return nullptr;							// If Not Return NULL
	}

    return auxDIBImageLoad(filePath.c_str());				// Load The Bitmap And Return A Pointer
}

bool Sprite::Load(const String& fileName)
{
    // HappyBuddha.obj

    wifstream file(fileName);
    if(file.fail())
    {
        return false;
    }

    vertice_.clear();
    texels_.clear();
    faces_.clear();
    
    while(!file.eof())
    {
        String line;
        getline(file, line);
        
        // v 1.0 1.0 1.0
        if(line.size() > 2 && line[0] == L'v' && line[1] == L' ')
        {
            float x;
            float y;
            float z;
            swscanf(line.c_str(), L"v %f %f %f", &x, &y, &z);

            vertice_.push_back(Vector3(x, y, z));
        }

        // vt 1.0 1.0 1.0
        else if(line.size() > 2 && line[0] == L'v' && line[1] == L't')
        {
            float x;
            float y;
            float z;
            swscanf(line.c_str(), L"vt %f %f %f", &x, &y, &z);

            texels_.push_back(Vector3(x, y, z));
        }

        // f 0/0 1/2 3/3 2/1
        else if(line.size() > 2 && line[0] == L'f' && line[1] == L' ')
        {
            QuadVertice vertice;
            QuadVertice textureVertice;
            vertice.Index[0];
            swscanf(line.c_str(), L"f %d/%d %d/%d %d/%d %d/%d", 
                &vertice.Index[0], &textureVertice.Index[0], 
                &vertice.Index[1], &textureVertice.Index[1], 
                &vertice.Index[2], &textureVertice.Index[2], 
                &vertice.Index[3], &textureVertice.Index[3]);

            // index가 1-base 이므로 0-base로 바꿔준다.
            vertice.Index[0]--;
            vertice.Index[1]--;
            vertice.Index[2]--;
            vertice.Index[3]--;
            textureVertice.Index[0]--;
            textureVertice.Index[1]--;
            textureVertice.Index[2]--;
            textureVertice.Index[3]--;

            faces_.push_back(vertice);
            textureFaces_.push_back(textureVertice);
        }
    }

    //
    // Face Normal 계산
    //
    vertexNormals_.resize(vertice_.size());
    for(int i = 0; i < faces_.size(); ++i)
    {
        const Vector3& vertex1 = vertice_[faces_[i].Index[0]];
        const Vector3& vertex2 = vertice_[faces_[i].Index[1]];
        const Vector3& vertex3 = vertice_[faces_[i].Index[2]];
        // 법선을 구하는 데는 벡터 두개만 있으면 되므로 4번째 점(vertex4)은 보지 않기로 함.

        Vector3 first = vertex2 - vertex1;
        Vector3 second = vertex3 - vertex2;
        Vector3 normal = first.Cross(second);
        normal.Normalize();
        faceNormals_.push_back(normal);

        // 이제 이 Face에 속한 각 Vertex들의 Normal 벡터값을 증가시켜줌
        vertexNormals_[faces_[i].Index[0]] += normal;
        vertexNormals_[faces_[i].Index[1]] += normal;
        vertexNormals_[faces_[i].Index[2]] += normal;
        vertexNormals_[faces_[i].Index[3]] += normal;
    }

    // Texture, FileName: "check.bmp"
    AUX_RGBImageRec* TextureImage[1];
    memset(TextureImage,0,sizeof(void *)*1);

    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBitmap(L"check.bmp"))
	{
        glGenTextures(3, &texture_[0]);	
        // Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture_[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // ( NEW )
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // ( NEW )
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

        // Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture_[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

        // Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texture_[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // ( NEW )

        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); // ( NEW )
	}

    if (TextureImage[0])							// If Texture Exists
	{
		if (TextureImage[0]->data)					// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);						// Free The Image Structure
	}

    return true;
}

void Sprite::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    float diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
    float specular[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    glScalef(scales_.X, scales_.Y, scales_.Z);
    glTranslatef(location_.X, location_.Y, location_.Z);
    
    glRotatef(anglesForEachAxis_.X, 1.0, 0.0, 0.0);
    glRotatef(anglesForEachAxis_.Y, 0.0, 1.0, 0.0);
    glRotatef(anglesForEachAxis_.Z, 0.0, 0.0, 1.0);

    // Pivot-Point Scaling
    glTranslatef(pivotPointForScaling_.X, pivotPointForScaling_.Y, pivotPointForScaling_.Z);
    glScalef(pivotPointScales_.X, pivotPointScales_.Y, pivotPointScales_.Z);
    glTranslatef(-pivotPointForScaling_.X, -pivotPointForScaling_.Y, -pivotPointForScaling_.Z);

    // Arbitrary Axis Rotation
    glTranslatef(-rotateAxisBegin_.X, -rotateAxisBegin_.Y, -rotateAxisBegin_.Z);
    glRotatef(rotateAngle_, rotateAxisEnd_.X - rotateAxisBegin_.X, rotateAxisEnd_.Y - rotateAxisBegin_.Y, rotateAxisEnd_.Z - rotateAxisBegin_.Z);
    glTranslatef(-rotateAxisBegin_.X, -rotateAxisBegin_.Y, -rotateAxisBegin_.Z);

    glColor3f(1.0, 1.0, 1.0);

    if(meshMode_ == MeshMode_Point)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        for(int i = 0; i < faces_.size(); ++i)
        {
            glBegin(GL_POINTS);

            const Vector3& vertex1 = vertice_[faces_[i].Index[0]];
            const Vector3& vertex2 = vertice_[faces_[i].Index[1]];
            const Vector3& vertex3 = vertice_[faces_[i].Index[2]];
            const Vector3& vertex4 = vertice_[faces_[i].Index[3]];

            glVertex3f(vertex1.X, vertex1.Y, vertex1.Z);
            glVertex3f(vertex2.X, vertex2.Y, vertex2.Z);
            glVertex3f(vertex3.X, vertex3.Y, vertex3.Z);
            glVertex3f(vertex4.X, vertex4.Y, vertex4.Z);

            glEnd();

            if(doDrawNormal_)
            {
                // 시작점은 4점의 평균
                Vector3 normalBegin((vertex1.X + vertex2.X + vertex3.X + vertex4.X)/4, 
                    (vertex1.Y + vertex2.Y + vertex3.Y + vertex4.Y)/4, 
                    (vertex1.Z + vertex2.Z + vertex3.Z + vertex4.Z)/4);

                Vector3 normal = faceNormals_[i];
                normal = normal * 0.05;
                Vector3 normalEnd = normalBegin + normal;
                
                glColor3f(0.0, 0.0, 1.0);
                glBegin(GL_LINES);
                    glVertex3f(normalBegin.X, normalBegin.Y, normalBegin.Z);
                    glVertex3f(normalEnd.X, normalEnd.Y, normalEnd.Z);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
            }
        }
    }
    else if(meshMode_ == MeshMode_Wireframe)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        for(int i = 0; i < faces_.size(); ++i)
        {
            const Vector3& vertex1 = vertice_[faces_[i].Index[0]];
            const Vector3& vertex2 = vertice_[faces_[i].Index[1]];
            const Vector3& vertex3 = vertice_[faces_[i].Index[2]];
            const Vector3& vertex4 = vertice_[faces_[i].Index[3]];

            if(doDrawNormal_)
            {
                // 시작점은 4점의 평균
                Vector3 normalBegin((vertex1.X + vertex2.X + vertex3.X + vertex4.X)/4, 
                    (vertex1.Y + vertex2.Y + vertex3.Y + vertex4.Y)/4, 
                    (vertex1.Z + vertex2.Z + vertex3.Z + vertex4.Z)/4);

                Vector3 normal = faceNormals_[i];
                normal = normal * 0.05;
                Vector3 normalEnd = normalBegin + normal;

                glColor3f(0.0, 0.0, 1.0);
                glBegin(GL_LINES);
                    glVertex3f(normalBegin.X, normalBegin.Y, normalBegin.Z);
                    glVertex3f(normalEnd.X, normalEnd.Y, normalEnd.Z);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
            }

            glBegin(GL_LINE_LOOP);
            glVertex3f(vertex1.X, vertex1.Y, vertex1.Z);
            glVertex3f(vertex2.X, vertex2.Y, vertex2.Z);
            glVertex3f(vertex3.X, vertex3.Y, vertex3.Z);
            glVertex3f(vertex4.X, vertex4.Y, vertex4.Z);
            glEnd();

            
        }
    }
    else if(meshMode_ == MeshMode_QuadMesh)
    {
        for(int i = 0; i < faces_.size(); ++i)
        {
            const Vector3& vertex1 = vertice_[faces_[i].Index[0]];
            const Vector3& vertex2 = vertice_[faces_[i].Index[1]];
            const Vector3& vertex3 = vertice_[faces_[i].Index[2]];
            const Vector3& vertex4 = vertice_[faces_[i].Index[3]];
            const Vector3& texel1 = texels_[textureFaces_[i].Index[0]];
            const Vector3& texel2 = texels_[textureFaces_[i].Index[1]];
            const Vector3& texel3 = texels_[textureFaces_[i].Index[2]];
            const Vector3& texel4 = texels_[textureFaces_[i].Index[3]];

            if(doDrawNormal_)
            {
                // 시작점은 4점의 평균
                Vector3 normalBegin((vertex1.X + vertex2.X + vertex3.X + vertex4.X)/4, 
                    (vertex1.Y + vertex2.Y + vertex3.Y + vertex4.Y)/4, 
                    (vertex1.Z + vertex2.Z + vertex3.Z + vertex4.Z)/4);
                Vector3 normal = faceNormals_[i];
                normal = normal * 0.05;
                Vector3 normalEnd = normalBegin + normal;
                
                glColor3f(0.0, 0.0, 1.0);
                glBegin(GL_LINES);
                    glVertex3f(normalBegin.X, normalBegin.Y, normalBegin.Z);
                    glVertex3f(normalEnd.X, normalEnd.Y, normalEnd.Z);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
            }
            
            const Vector3& vertexNormal1 = vertexNormals_[faces_[i].Index[0]];
            const Vector3& vertexNormal2 = vertexNormals_[faces_[i].Index[1]];
            const Vector3& vertexNormal3 = vertexNormals_[faces_[i].Index[2]];
            const Vector3& vertexNormal4 = vertexNormals_[faces_[i].Index[3]];

            if(doDrawTexture_)
                glBindTexture(GL_TEXTURE_2D, texture_[0]);
            else
                glBindTexture(GL_TEXTURE_2D, 0);

            glBegin(GL_QUADS);

            glNormal3f(vertexNormal1.X, vertexNormal1.Y, vertexNormal1.Z);
            if(doDrawTexture_)
                glTexCoord2f(texel1.X, texel1.Y); 
            glVertex3f(vertex1.X, vertex1.Y, vertex1.Z);
            
            glNormal3f(vertexNormal2.X, vertexNormal2.Y, vertexNormal2.Z);
            if(doDrawTexture_)
                glTexCoord2f(texel2.X, texel2.Y); 
            glVertex3f(vertex2.X, vertex2.Y, vertex2.Z);

            glNormal3f(vertexNormal3.X, vertexNormal3.Y, vertexNormal3.Z);
            if(doDrawTexture_) 
                glTexCoord2f(texel3.X, texel3.Y); 
            glVertex3f(vertex3.X, vertex3.Y, vertex3.Z);

            glNormal3f(vertexNormal4.X, vertexNormal4.Y, vertexNormal4.Z);
            if(doDrawTexture_) 
                glTexCoord2f(texel4.X, texel4.Y); 
            glVertex3f(vertex4.X, vertex4.Y, vertex4.Z);

            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

void Sprite::RotateXMore(float angle)
{
    anglesForEachAxis_.X += angle;
}

void Sprite::RotateYMore(float angle)
{
    anglesForEachAxis_.Y += angle;
}

void Sprite::RotateZMore(float angle)
{
    anglesForEachAxis_.Z += angle;
}

void Sprite::RotateAxis(float angle, const Vector3& axisBegin, const Vector3& axisEnd)
{
    rotateAngle_ = angle;
    rotateAxisBegin_ = axisBegin;
    rotateAxisEnd_ = axisEnd;
}

void Sprite::TranslateMore(float x, float y, float z)
{
    location_.X += x;
    location_.Y += y;
    location_.Z += z;
}

void Sprite::Scale(float x, float y, float z)
{
    scales_.X = x;
    scales_.Y = y;
    scales_.Z = z;
}

void Sprite::ScaleRate(float x, float y, float z)
{
    scales_.X *= x;
    scales_.Y *= y;
    scales_.Z *= z;
}

void Sprite::ScaleFrom(const Vector3& from, float x, float y, float z)
{
    pivotPointForScaling_ = from;
    pivotPointScales_.X = x;
    pivotPointScales_.Y = y;
    pivotPointScales_.Z = z;
}

void Sprite::Reset()
{
    location_.Reset();
    anglesForEachAxis_.Reset();

    rotateAngle_ = 0.0;
    rotateAxisBegin_.Reset();
    rotateAxisEnd_.Reset();

    scales_.X = 1.0;
    scales_.Y = 1.0;
    scales_.Z = 1.0;

    pivotPointForScaling_.Reset();
    pivotPointScales_.X = 1.0;
    pivotPointScales_.Y = 1.0;
    pivotPointScales_.Z = 1.0;
}

void Sprite::SetMeshMode(MeshMode mode)
{
    meshMode_ = mode;
}

void Sprite::SetDrawNormal(bool drawNormal)
{
    doDrawNormal_ = drawNormal;
}

void Sprite::CopyTo(Sprite& rhs) const
{
    rhs.vertice_ = vertice_;
    rhs.texels_ = texels_;
    rhs.faces_ = faces_;
    rhs.textureFaces_ = textureFaces_;
    rhs.faceNormals_ = faceNormals_;
    rhs.vertexNormals_ = vertexNormals_;

    for(int i = 0; i < 3; ++i)
        rhs.texture_[i] = texture_[i];
}

void Sprite::SetDrawTexture(bool drawTexture)
{
    doDrawTexture_ = drawTexture;
}

}

