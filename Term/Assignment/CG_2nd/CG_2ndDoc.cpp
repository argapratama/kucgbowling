
// CG_2ndDoc.cpp : CCG_2ndDoc 클래스의 구현
//

#include "stdafx.h"
#include "CG_2nd.h"

#include "CG_2ndDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG_2ndDoc

IMPLEMENT_DYNCREATE(CCG_2ndDoc, CDocument)

BEGIN_MESSAGE_MAP(CCG_2ndDoc, CDocument)
END_MESSAGE_MAP()


// CCG_2ndDoc 생성/소멸

CCG_2ndDoc::CCG_2ndDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	vertexCount = faceCount = tVertexCount = 0;
}

CCG_2ndDoc::~CCG_2ndDoc()
{
}

BOOL CCG_2ndDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CCG_2ndDoc serialization

void CCG_2ndDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

void CCG_2ndDoc::Initialize(CString filePath)
{
	this->filePath = filePath;
	SetTotalCount();
	vertices = new Vertex[vertexCount];
	tVertices = new Vertex[tVertexCount];
	faces = new Face[faceCount];
	tFaces = new Face[faceCount];
	fNVectors = new Vertex[faceCount];
	vNVectors = new Vertex[vertexCount];
	memset(TextureImage, 0, sizeof(void *)*1);
	SetModelFromFile();
	SetNormalVector();
}

void CCG_2ndDoc::Destroy()
{
	if(vertexCount != 0)
	{
		delete(vertices);
		delete(vNVectors);
	}
	if(tVertexCount != 0)
	{
		delete(tVertices);
	}
	if(faceCount != 0)
	{
		delete(faces);
		delete(tFaces);
		delete(fNVectors);
	}
	vertexCount = tVertexCount = faceCount = 0;
}

int CCG_2ndDoc::GetLineIndex(string value)
{
	if(value.compare("v") == 0 || value.compare("V") == 0)
	{
		return Line(VERTEX);
	}
	else if(value.compare("vt") == 0 || value.compare("VT") == 0)
	{
		return Line(VERTEX_TEXTURE);
	}
	else if(value.compare("f") == 0 || value.compare("F") == 0)
	{
		return Line(FACE);
	}
	return Line(NONE);
}

void CCG_2ndDoc::SetTotalCount()
{
	ifstream infile;
	infile.open(filePath);
	string in;
	if(infile.eof())
	{
		infile.close();
		return;
	}
	getline(infile, in);
	do
	{
		stringstream s(in);
		if(s.eof()) break;
		string header;
		s >> header;
		switch(GetLineIndex(header))
		{
		case Line(VERTEX):
			vertexCount++;
			break;
		case Line(VERTEX_TEXTURE):
			tVertexCount++;
			break;
		case Line(FACE):
			faceCount++;
			break;
		}
		getline(infile, in);
	} while(!infile.eof());
}

void CCG_2ndDoc::SetModelFromFile()
{
	ifstream infile;
	infile.open(filePath);
	string in;
	if(infile.eof())
	{
		infile.close();
		return;
	}
	int vertexIdx = 0, faceIdx = 0, tVertexIdx = 0, tFaceIdx = 0;
	getline(infile, in);
	do
	{
		stringstream s(in);
		if(s.eof()) break;
		string header;
		s >> header;
		
		string sFirst, sSecond, sThird, sFourth;
		Vertex vertex;
		switch(GetLineIndex(header))
		{
		case Line(VERTEX):
			s >> sFirst >> sSecond >> sThird;
			vertex.x = StringCast<float>(sFirst);
			vertex.y = StringCast<float>(sSecond);
			vertex.z = StringCast<float>(sThird);
			vertices[vertexIdx++] = vertex;
			break;
		case Line(VERTEX_TEXTURE):
			s >> sFirst >> sSecond >> sThird;
			vertex.x = StringCast<float>(sFirst);
			vertex.y = StringCast<float>(sSecond);
			vertex.z = StringCast<float>(sThird);
			tVertices[tVertexIdx++] = vertex;
			break;
		case Line(FACE):
			s >> sFirst >> sSecond >> sThird >> sFourth;
			Face face, tFace;
			vector<int> tokens;
			Tokenize(sFirst, tokens, "/");
			face.vertex0 = tokens.front();
			tFace.vertex0 = tokens.back();
			tokens.clear();
			Tokenize(sSecond, tokens, "/");
			face.vertex1 = tokens.front();
			tFace.vertex1 = tokens.back();
			tokens.clear();
			Tokenize(sThird, tokens, "/");
			face.vertex2 = tokens.front();
			tFace.vertex2 = tokens.back();
			tokens.clear();
			Tokenize(sFourth, tokens, "/");
			face.vertex3 = tokens.front();
			tFace.vertex3 = tokens.back();
			tokens.clear();
			faces[faceIdx++] = face;
			tFaces[tFaceIdx++] = tFace;
			break;
		}
		getline(infile, in);
	} while(!infile.eof());
}

void CCG_2ndDoc::SetNormalVector()
{
	for(int i = 0; i < vertexCount; i++)
	{
		vNVectors[i].x = 0;	vNVectors[i].y = 0; vNVectors[i].z = 0;
	}
	for(int i = 0; i < faceCount; i++)
	{
		Face face = faces[i];

		Vertex vertex;
		vertex.x = (vertices[face.vertex0-1].x + vertices[face.vertex1-1].x + vertices[face.vertex2-1].x + vertices[face.vertex3-1].x) / 4;
		vertex.y = (vertices[face.vertex0-1].y + vertices[face.vertex1-1].y + vertices[face.vertex2-1].y + vertices[face.vertex3-1].y) / 4;
		vertex.z = (vertices[face.vertex0-1].z + vertices[face.vertex1-1].z + vertices[face.vertex2-1].z + vertices[face.vertex3-1].z) / 4;
		
		Vertex vector1, vector2;
		vector1.x = vertices[face.vertex1-1].x - vertices[face.vertex2-1].x;
		vector2.x = vertices[face.vertex0-1].x - vertices[face.vertex1-1].x;
		vector1.y = vertices[face.vertex1-1].y - vertices[face.vertex2-1].y;
		vector2.y = vertices[face.vertex0-1].y - vertices[face.vertex1-1].y;
		vector1.z = vertices[face.vertex1-1].z - vertices[face.vertex2-1].z;
		vector2.z = vertices[face.vertex0-1].z - vertices[face.vertex1-1].z;
		fNVectors[i] = GetOuterVector(vector1, vector2);
		vNVectors[face.vertex0-1].x += fNVectors[i].x; vNVectors[face.vertex0-1].y += fNVectors[i].y; vNVectors[face.vertex0-1].z += fNVectors[i].z;
		vNVectors[face.vertex1-1].x += fNVectors[i].x; vNVectors[face.vertex1-1].y += fNVectors[i].y; vNVectors[face.vertex1-1].z += fNVectors[i].z;
		vNVectors[face.vertex2-1].x += fNVectors[i].x; vNVectors[face.vertex2-1].y += fNVectors[i].y; vNVectors[face.vertex2-1].z += fNVectors[i].z;
		vNVectors[face.vertex3-1].x += fNVectors[i].x; vNVectors[face.vertex3-1].y += fNVectors[i].y; vNVectors[face.vertex3-1].z += fNVectors[i].z;
	}
}

void CCG_2ndDoc::Tokenize(const string& str, vector<int>& tokens, const string& delimiters)
{
    // 맨 첫 글자가 구분자인 경우 무시
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // 구분자가 아닌 첫 글자를 찾는다
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while(string::npos != pos || string::npos != lastPos)
    {
		// token을 찾았으니 vector에 추가한다
		tokens.push_back(StringCast<int>(str.substr(lastPos, pos - lastPos)));
		// 구분자를 뛰어넘는다.  "not_of"에 주의하라
		lastPos = str.find_first_not_of(delimiters, pos);
		// 다음 구분자가 아닌 글자를 찾는다
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void CCG_2ndDoc::PointDisplay()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < vertexCount; i++)
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
}

void CCG_2ndDoc::QuadMeshDisplay(int shadingMode)
{
	glColor3f(0.85f, 0.85f, 0.85f);
	glBegin(GL_QUADS);
	for(int i = 0; i < faceCount; i++)
	{
		DrawVertex(i, shadingMode, false);
	}
	glEnd();
}

void CCG_2ndDoc::SetNormalElement(Vertex vertex)
{
	float size = Magnitude(vertex);
	vertex.x /= size;
	vertex.y /= size;
	vertex.z /= size;
	glNormal3f(vertex.x, vertex.y, vertex.z);
}

void CCG_2ndDoc::WireframeDisplay()
{
	glColor3f(5.0f, 0.0f, 5.0f);
	for(int i = 0; i < faceCount; i++)
	{
		Face face = faces[i];
		if(face.vertex0 > vertexCount || face.vertex1 > vertexCount || face.vertex2 > vertexCount || face.vertex3 > vertexCount)
			continue;
		glBegin(GL_LINE_LOOP);
		glVertex3f(vertices[face.vertex0 - 1].x, vertices[face.vertex0 - 1].y, vertices[face.vertex0 - 1].z);
		glVertex3f(vertices[face.vertex3 - 1].x, vertices[face.vertex3 - 1].y, vertices[face.vertex3 - 1].z);
		glVertex3f(vertices[face.vertex2 - 1].x, vertices[face.vertex2 - 1].y, vertices[face.vertex2 - 1].z);
		glVertex3f(vertices[face.vertex1 - 1].x, vertices[face.vertex1 - 1].y, vertices[face.vertex1 - 1].z);
		glEnd();
	}
}

void CCG_2ndDoc::DrawNormalVector()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	for(int i = 0; i < faceCount; i++)
	{
		Face face = faces[i];

		Vertex vertex;
		vertex.x = (vertices[face.vertex0-1].x + vertices[face.vertex1-1].x + vertices[face.vertex2-1].x + vertices[face.vertex3-1].x) / 4;
		vertex.y = (vertices[face.vertex0-1].y + vertices[face.vertex1-1].y + vertices[face.vertex2-1].y + vertices[face.vertex3-1].y) / 4;
		vertex.z = (vertices[face.vertex0-1].z + vertices[face.vertex1-1].z + vertices[face.vertex2-1].z + vertices[face.vertex3-1].z) / 4;

		glVertex3f(vertex.x, vertex.y, vertex.z);
		glVertex3f(vertex.x - fNVectors[i].x/100, vertex.y - fNVectors[i].y/100, vertex.z - fNVectors[i].z/100);
	}
	glEnd();
}

void CCG_2ndDoc::TextureDisplay(int shadingMode)
{
	LoadTexture();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	glBegin(GL_QUADS);
	for(int i = 0; i < faceCount; i++)
	{
		DrawVertex(i, shadingMode, true);
	}
	glEnd();
}

void CCG_2ndDoc::DrawVertex(int faceIndex, int shadingMode, bool isTexture)
{
	Face face = faces[faceIndex];
	Face tFace = tFaces[faceIndex];
	if(face.vertex0 > vertexCount || face.vertex1 > vertexCount || face.vertex2 > vertexCount || face.vertex3 > vertexCount)
		return;
	if(shadingMode == Shading(FLAT))
		SetNormalElement(fNVectors[faceIndex]);
	if(shadingMode == Shading(GOURAUD))
		SetNormalElement(vNVectors[face.vertex0 - 1]);
	if(isTexture)
		glTexCoord2f(tVertices[tFace.vertex0 - 1].x, tVertices[tFace.vertex0 - 1].y);
	glVertex3f(vertices[face.vertex0 - 1].x, vertices[face.vertex0 - 1].y, vertices[face.vertex0 - 1].z);
	if(shadingMode == Shading(GOURAUD))
		SetNormalElement(vNVectors[face.vertex1 - 1]);
	if(isTexture)
		glTexCoord2f(tVertices[tFace.vertex1 - 1].x, tVertices[tFace.vertex1 - 1].y);
	glVertex3f(vertices[face.vertex1 - 1].x, vertices[face.vertex1 - 1].y, vertices[face.vertex1 - 1].z);
	if(shadingMode == Shading(GOURAUD))
		SetNormalElement(vNVectors[face.vertex2 - 1]);
	if(isTexture)
		glTexCoord2f(tVertices[tFace.vertex2 - 1].x, tVertices[tFace.vertex2 - 1].y);
	glVertex3f(vertices[face.vertex2 - 1].x, vertices[face.vertex2 - 1].y, vertices[face.vertex2 - 1].z);
	if(shadingMode == Shading(GOURAUD))
		SetNormalElement(vNVectors[face.vertex3 - 1]);
	if(isTexture)
		glTexCoord2f(tVertices[tFace.vertex3 - 1].x, tVertices[tFace.vertex3 - 1].y);
	glVertex3f(vertices[face.vertex3 - 1].x, vertices[face.vertex3 - 1].y, vertices[face.vertex3 - 1].z);
}

Vertex CCG_2ndDoc::GetOuterVector(Vertex vector1, Vertex vector2)
{
	Vertex outerVector;
	outerVector.x = vector1.y*vector2.z - vector1.z*vector2.y;
	outerVector.y = vector1.z*vector2.x - vector1.x*vector2.z;
	outerVector.z = vector1.x*vector2.y - vector1.y*vector2.x;
	float vectorSize = Magnitude(outerVector);
	outerVector.x /= vectorSize;
	outerVector.y /= vectorSize;
	outerVector.z /= vectorSize;
	return outerVector;
}

float CCG_2ndDoc::Magnitude(Vertex vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

void CCG_2ndDoc::SetTextureFile(CString filePath)
{
	this->texturePath = filePath;
}

void CCG_2ndDoc::LoadTexture()
{
	if(!texturePath.IsEmpty())
	{
		TextureImage[0] = auxDIBImageLoad(texturePath);
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY
			, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

void CCG_2ndDoc::DisableTexture()
{
	glDisable(GL_TEXTURE_2D);
}

// CCG_2ndDoc 진단

#ifdef _DEBUG
void CCG_2ndDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG_2ndDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG_2ndDoc 명령
