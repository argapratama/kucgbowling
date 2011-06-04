
// CG_2ndView.h : CCG_2ndView 클래스의 인터페이스
//


#pragma once

#include <string>
#include <locale.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include "Translation.h"
#include "Scaling.h"
#include "AxisRotation.h"
#include "PivotScaling.h"
#include "RandomRotation.h"
#include "OrthoGraphic.h"
#include "Frustum.h"
#include "Perspective.h"
#include "Camera.h"
#include "LightPosition.h"
#include "LightColor.h"
#include "CG_2ndViewUser.h"

using namespace std;

struct Light
{
	float position[4];
	float ambient[4], diffuse[4], specular[4];

	void SetPosition(float x, float y, float z, float isPoint)
	{
		position[0]=x; position[1]=y;
		position[2]=z; position[3]=isPoint;
	}
	void SetAmbient(float r, float g, float b, float t)
	{
		ambient[0]=r; ambient[1]=g; 
		ambient[2]=b; ambient[3]=t;
	}
	void SetDiffuse(float r, float g, float b, float t)
	{
		diffuse[0]=r; diffuse[1]=g; 
		diffuse[2]=b; diffuse[3]=t;
	}
	void SetSpecular(float r, float g, float b, float t)
	{
		specular[0]=r; specular[1]=g; 
		specular[2]=b; specular[3]=t;
	}
};

class CCG_2ndView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCG_2ndView();
	DECLARE_DYNCREATE(CCG_2ndView)

// 특성입니다.
public:
	CCG_2ndDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCG_2ndView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCG_2ndViewUser user, extra;

	// Display Mode
	bool isPointDisplay;
	bool isWireDisplay;
	bool isQuadDisplay;
	bool isVectorDisplay;
	
	// Pivot Scaling
	float f_pScaleX, f_pScaleY, f_pScaleZ;
	float f_pPointX, f_pPointY, f_pPointZ;

	// Random Rotation
	float f_sLineX, f_sLineY, f_sLineZ;
	float f_eLineX, f_eLineY, f_eLineZ;
	// Random Rotation
	float f_rAngle;
	bool isRRotation;
	// Camera Rotation
	float f_rotY;
	float f_posX, f_posZ;
	bool isCameraRotate;

	// View Volumn
	float f_left, f_right, f_bottom, f_top, f_near, f_far;
	float f_aspect, f_fov;

	// Camera
	float f_eyeX, f_eyeY, f_eyeZ;
	float f_atX, f_atY, f_atZ;
	float f_upX, f_upY, f_upZ;

	// View Mode
	enum Viewing {NONE = -1, ORTHOGRAPHIC = 1, PERSPECTIVE = 2, FRUSTUM = 3};
	int currentView;

	// Texture Mapping
	bool hasTexture, enableTexture;

	// Shading
	int currentShading;
	// Lighting
	Light light0;

	// Event Handler
	bool isLMousePressed, isRMousePressed, isRMouseDbPressed;
	CPoint tStartPoint, rStartPoint, cStartPoint;
	HDC m_hDC; // 기본 멤버 변수 추가
	HGLRC m_hRC; // 기본 멤버 변수 추가

	// Multiview
	bool enableMultiView;
	float f_width, f_height;
	bool isUserDisplay;

	void InitPosition();
	void GLRenderScene(int = 0);
	void ChangeDisplayMode(UINT, bool *);
	void SetView();
	void DoViewing();
	void DoDisplay();
	void DoShading();
	void DoModelBasicTransform();
	void DoCameraTransform(int MultiView);

	enum MultiView {TOP = 1, FRONT = 2, SIDE = 3, NORMAL = 4};
public:
	enum Shading {NOTHING = -1, FLAT = 1, GOURAUD = 2};

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLoadPoint();
	afx_msg void OnLoadWire();
	afx_msg void OnLoadQuad();
	afx_msg void OnLoadVector();
public:
	afx_msg void OnTransformTrans();
	afx_msg void OnTransformScale();
	afx_msg void OnTransformPivot();
	afx_msg void OnTransformAxis();
	afx_msg void OnTransformRandom();
	afx_msg void OnFileOpen();
	afx_msg void OnOrthographic();
	afx_msg void OnPerspective();
	afx_msg void OnFrustum();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdate3dviewingFrustum(CCmdUI *pCmdUI);
	afx_msg void OnUpdate3dviewingOrthographic(CCmdUI *pCmdUI);
	afx_msg void OnUpdate3dviewingPerspective(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLoadPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLoadWire(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLoadQuad(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLoadVector(CCmdUI *pCmdUI);
	afx_msg void OnCameraPosition();
	afx_msg void OnTextureOpen();
	afx_msg void OnTextureEnable();
	afx_msg void OnUpdateTextureOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTextureEnable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShadingFlat(CCmdUI *pCmdUI);
	afx_msg void OnShadingGouraud();
	afx_msg void OnShadingFlat();
	afx_msg void OnUpdateShadingGouraud(CCmdUI *pCmdUI);
	afx_msg void OnLightPosition();
	afx_msg void OnLightColor();
	afx_msg void OnMultiviewEnable();
	afx_msg void OnCameraRotation();
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateMultiviewEnable(CCmdUI *pCmdUI);
	afx_msg void OnShadingNone();
};

#ifndef _DEBUG  // CG_2ndView.cpp의 디버그 버전
inline CCG_2ndDoc* CCG_2ndView::GetDocument() const
   { return reinterpret_cast<CCG_2ndDoc*>(m_pDocument); }
#endif