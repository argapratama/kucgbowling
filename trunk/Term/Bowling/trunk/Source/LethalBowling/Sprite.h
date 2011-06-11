#pragma once

#include "Vector.h"
#include "TString.h"
#include "PrimitiveType.h"
#include <vector>

namespace Virgin
{

struct QuadVertice
{
public:
    int Index[4];
};

struct TriangleVertice
{
public:
    int Index[4];
};

enum MeshMode
{
    MeshMode_Point,
    MeshMode_Wireframe,
    MeshMode_QuadMesh
};

class Sprite
{
public:
    Sprite(void);
    ~Sprite(void);

    bool Load(const String& fileName, const String& textureName);

    void RotateXMore(float angle);
    void RotateYMore(float angle);
    void RotateZMore(float angle);
    void RotateAxis(float angle, const Vector3& axisBegin, const Vector3& axisEnd);
    void TranslateMore(float x, float y, float z);
    void Scale(float x, float y, float z);
    void ScaleRate(float x, float y, float z);
    void ScaleFrom(const Vector3& from, float x, float y, float z);
    void Reset();

    void Draw();
    void SetMeshMode(MeshMode mode);
    void SetDrawNormal(bool drawNormal);
    void SetDrawTexture(bool drawTexture);

    void CopyTo(Sprite& rhs) const;

private:
    std::vector<Vector3> vertice_;
    std::vector<Vector3> texels_;
	std::vector<Vector3> normals_;
    std::vector<QuadVertice> faces_;
    std::vector<QuadVertice> textureFaces_;
	//std::vector<QuadVertice> normalFaces_;
	std::vector<QuadVertice> normalVertices_;
	std::vector<TriangleVertice> triFaces_;
    std::vector<TriangleVertice> triTextureFaces_;
    //std::vector<TriangleVertice> triFaceNormals_;
	std::vector<TriangleVertice> triNormalVertices_;

    std::vector<Vector3> faceNormals_;
    std::vector<Vector3> vertexNormals_;

    Vector3 location_;
    Vector3 anglesForEachAxis_;

    float rotateAngle_;
    Vector3 rotateAxisBegin_;
    Vector3 rotateAxisEnd_;

    Vector3 scales_;

    Vector3 pivotPointForScaling_;
    Vector3 pivotPointScales_;

    MeshMode meshMode_;
    bool doDrawNormal_;
    bool doDrawTexture_;

    uint texture_[3];

    //
    // 물리 모델링
    //

    // 질량 특성
    float mass_;        // 질량
    float massCenter_;  // 질량 중심    // * Todo: 좌표가 필요함
    float moment_;      // 관성 모멘트(회전 저항력)(Inertia)   // * Todo: 축별로 다름   
    
    // 물체에 작용하는 힘
    std::vector<float> forces_; // * Todo: 방향도 필요함
    std::vector<float> momentForces_;

    // 선가속도, 각가속도
    float linearAcceleration_;  // * Todo: 방향도 필요함
    float angleAcceleration_;

    // 선속도, 각속도
    float linearVelocity_;  // * Todo: 방향도 필요함
    float angleVelocity_;

    // 선 변위, 각 변위
    float linearDisplacement_;  // * Todo: 방향도 필요함
    float angleDisplacement_;

    // + 현재 위치, 방향
};

}
