
// CG_2ndDoc.h : CCG_2ndDoc 클래스의 인터페이스
//


#pragma once

#include <string>
#include <locale.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Vertex
{
	float x;
	float y;
	float z;
};

struct Face
{
	int vertex0;
	int vertex1;
	int vertex2;
	int vertex3;
};

class CCG_2ndDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CCG_2ndDoc();
	DECLARE_DYNCREATE(CCG_2ndDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CCG_2ndDoc();
	void Initialize(CString);
	void PointDisplay();
	void WireframeDisplay();
	void QuadMeshDisplay(int);
	void DrawNormalVector();
	void TextureDisplay(int);
	void Tokenize(const string&, vector<int>&, const string&);
	void Destroy();
	void LoadTexture();
	void DisableTexture();
	void SetTextureFile(CString filePath);
private:
	void SetTotalCount();
	void SetModelFromFile();
	void SetNormalVector();
	Vertex GetOuterVector(Vertex, Vertex);
	float Magnitude(Vertex vector);
	int GetLineIndex(string value);
	void SetNormalElement(Vertex);
	void DrawVertex(int faceIndex, int shadingMode, bool isTexture);
// 변수
private:
	enum Line {NONE = -1, VERTEX = 1, VERTEX_TEXTURE = 2, FACE = 3};
	Vertex *vertices, *tVertices;	// 평면의 점, 텍스쳐 평면의 점
	Face *faces, *tFaces;		// 평면, 텍스쳐 평면
	Vertex *fNVectors, *vNVectors;	// 평면의 법선벡터, 점의 법선벡터
	CString filePath;
	int vertexCount, tVertexCount, faceCount;
	AUX_RGBImageRec *TextureImage[3];
	GLuint texture[1];
	CString texturePath;
public:
	enum Shading {NOTHING = -1, FLAT = 1, GOURAUD = 2};
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};


template< typename To, typename From > 
const To StringCast(const From& from) 
{ 
	std::stringstream strStream;
	strStream << from; 
	To result; 
	strStream >> result; 
	if( strStream.fail() && !strStream.eof() ) return 0;   
	return result; 
}