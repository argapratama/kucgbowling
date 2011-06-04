
// CG_2ndView.cpp : CCG_2ndView 클래스의 구현
//

#include "stdafx.h"
#include "CG_2nd.h"

#include "CG_2ndDoc.h"
#include "CG_2ndView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG_2ndView

IMPLEMENT_DYNCREATE(CCG_2ndView, CView)

BEGIN_MESSAGE_MAP(CCG_2ndView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCG_2ndView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_LOAD_POINT, &CCG_2ndView::OnLoadPoint)
	ON_COMMAND(ID_LOAD_WIRE, &CCG_2ndView::OnLoadWire)
	ON_COMMAND(ID_LOAD_QUAD, &CCG_2ndView::OnLoadQuad)
	ON_COMMAND(ID_LOAD_VECTOR, &CCG_2ndView::OnLoadVector)
	ON_COMMAND(ID_TRANSFORM_TRANS, &CCG_2ndView::OnTransformTrans)
	ON_COMMAND(ID_TRANSFORM_SCALE, &CCG_2ndView::OnTransformScale)
	ON_COMMAND(ID_TRANSFORM_PIVOT, &CCG_2ndView::OnTransformPivot)
	ON_COMMAND(ID_TRANSFORM_Axis, &CCG_2ndView::OnTransformAxis)
	ON_COMMAND(ID_TRANSFORM_RANDOM, &CCG_2ndView::OnTransformRandom)
	ON_COMMAND(ID_FILE_OPEN, &CCG_2ndView::OnFileOpen)
	ON_COMMAND(ID_3DVIEWING_ORTHOGRAPHIC, &CCG_2ndView::OnOrthographic)
	ON_COMMAND(ID_3DVIEWING_PERSPECTIVE, &CCG_2ndView::OnPerspective)
	ON_COMMAND(ID_3DVIEWING_FRUSTUM, &CCG_2ndView::OnFrustum)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
ON_UPDATE_COMMAND_UI(ID_3DVIEWING_FRUSTUM, &CCG_2ndView::OnUpdate3dviewingFrustum)
ON_UPDATE_COMMAND_UI(ID_3DVIEWING_ORTHOGRAPHIC, &CCG_2ndView::OnUpdate3dviewingOrthographic)
ON_UPDATE_COMMAND_UI(ID_3DVIEWING_PERSPECTIVE, &CCG_2ndView::OnUpdate3dviewingPerspective)
ON_UPDATE_COMMAND_UI(ID_LOAD_POINT, &CCG_2ndView::OnUpdateLoadPoint)
ON_UPDATE_COMMAND_UI(ID_LOAD_WIRE, &CCG_2ndView::OnUpdateLoadWire)
ON_UPDATE_COMMAND_UI(ID_LOAD_QUAD, &CCG_2ndView::OnUpdateLoadQuad)
ON_UPDATE_COMMAND_UI(ID_LOAD_VECTOR, &CCG_2ndView::OnUpdateLoadVector)
ON_COMMAND(ID_CAMERA_POSITION, &CCG_2ndView::OnCameraPosition)
ON_COMMAND(ID_TEXTURE_OPEN, &CCG_2ndView::OnTextureOpen)
ON_COMMAND(ID_TEXTURE_ENABLE, &CCG_2ndView::OnTextureEnable)
ON_UPDATE_COMMAND_UI(ID_TEXTURE_OPEN, &CCG_2ndView::OnUpdateTextureOpen)
ON_UPDATE_COMMAND_UI(ID_TEXTURE_ENABLE, &CCG_2ndView::OnUpdateTextureEnable)
ON_UPDATE_COMMAND_UI(ID_SHADING_FLAT, &CCG_2ndView::OnUpdateShadingFlat)
ON_COMMAND(ID_SHADING_GOURAUD, &CCG_2ndView::OnShadingGouraud)
ON_COMMAND(ID_SHADING_FLAT, &CCG_2ndView::OnShadingFlat)
ON_UPDATE_COMMAND_UI(ID_SHADING_GOURAUD, &CCG_2ndView::OnUpdateShadingGouraud)
ON_COMMAND(ID_LIGHT_POSITION, &CCG_2ndView::OnLightPosition)
ON_COMMAND(ID_LIGHT_COLOR, &CCG_2ndView::OnLightColor)
ON_COMMAND(ID_MULTIVIEW_ENABLE, &CCG_2ndView::OnMultiviewEnable)
ON_COMMAND(ID_CAMERA_ROTATION, &CCG_2ndView::OnCameraRotation)
ON_WM_TIMER()
ON_UPDATE_COMMAND_UI(ID_MULTIVIEW_ENABLE, &CCG_2ndView::OnUpdateMultiviewEnable)
ON_COMMAND(ID_SHADING_NONE, &CCG_2ndView::OnShadingNone)
END_MESSAGE_MAP()

// CCG_2ndView 생성/소멸

CCG_2ndView::CCG_2ndView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	InitPosition();
	isPointDisplay = isWireDisplay = isVectorDisplay = FALSE;
	isQuadDisplay = TRUE;
	isRRotation = false;
	isLMousePressed = isRMouseDbPressed = isRMousePressed = false;
	enableTexture = hasTexture = false;
	isCameraRotate = false;
	enableMultiView = false;
	isUserDisplay = true;
	light0.SetPosition(-1.0f, 0.0f, -3.0f, 1.0f);
	light0.SetAmbient(0.2, 0.2, 0.2, 1.0);
	light0.SetDiffuse(0.6, 0.6, 0.6, 1.0);
	light0.SetSpecular(1, 1, 0.5, 1.0);
	currentShading = Shading(NONE);
}

CCG_2ndView::~CCG_2ndView()
{
}

void CCG_2ndView::InitPosition()
{
	user.InitPosition();
	extra.InitPosition();
	f_pScaleX = f_pScaleY = f_pScaleZ = 1;
	f_pPointX = f_pPointY = f_pPointZ = 0;
	f_sLineX = f_sLineY = f_sLineZ = 0;
	f_eLineX = f_eLineY = f_eLineZ = 0;
	f_rAngle = 0;
	f_left = f_right = f_bottom = f_top = f_near = f_far = 0;
	f_fov = f_aspect = 0;
	f_eyeX = -2; f_eyeY = 0; f_eyeZ = -1;
	f_atX = -1.5; f_atY = 0; f_atZ = -1.5;
	f_upX = 0; f_upY = 1; f_upZ = 0;
	currentView = Viewing(NONE);
	f_rotY = 0;
	f_posX = f_posZ = 0;
}

BOOL CCG_2ndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCG_2ndView 그리기

void CCG_2ndView::OnDraw(CDC* /*pDC*/)
{
	CCG_2ndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	wglMakeCurrent(m_hDC, m_hRC);
	SetView();
	SwapBuffers(m_hDC);

	wglMakeCurrent(m_hDC, NULL);
}


// CCG_2ndView 인쇄


void CCG_2ndView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CCG_2ndView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCG_2ndView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCG_2ndView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCG_2ndView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCG_2ndView 진단

#ifdef _DEBUG
void CCG_2ndView::AssertValid() const
{
	CView::AssertValid();
}

void CCG_2ndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG_2ndDoc* CCG_2ndView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG_2ndDoc)));
	return (CCG_2ndDoc*)m_pDocument;
}
#endif //_DEBUG


// CCG_2ndView 메시지 처리기

int CCG_2ndView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	 int nPixelFormat;
	  m_hDC = ::GetDC(m_hWnd);

	  static PIXELFORMATDESCRIPTOR pfd = 
	  {
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_DRAW_TO_WINDOW |
	   PFD_SUPPORT_OPENGL |
	   PFD_DOUBLEBUFFER,
	   PFD_TYPE_RGBA,
	   24,
	   0,0,0,0,0,0,
	   0,0,
	   0,0,0,0,0,
	   32,
	   0,
	   0,
	   PFD_MAIN_PLANE,
	   0,
	   0,0,0
	  };

	  nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	  VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));
	  m_hRC = wglCreateContext(m_hDC);

	return 0;
}

void CCG_2ndView::OnDestroy()
{
	wglDeleteContext(m_hRC);
  ::ReleaseDC(m_hWnd, m_hDC);

	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CCG_2ndView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	f_width = (float)cx; f_height = (float)cy;
	SetView();
}

void CCG_2ndView::SetView()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(enableMultiView)
	{
		// 우측 하단
		glViewport(f_width/2 + 1, 0, f_width/2, f_height/2);
		GLRenderScene(MultiView(NORMAL));
		// 좌측 상단
		glViewport(0, f_height/2 + 1, f_width/2, f_height/2);
		GLRenderScene(MultiView(TOP));
		// 우측 상단
		glViewport(f_width/2 + 1, f_height/2 + 1, f_width/2, f_height/2);
		GLRenderScene(MultiView(FRONT));
		// 좌측 하단
		glViewport(0, 0, f_width/2, f_height/2);
		GLRenderScene(MultiView(SIDE));
	}
	else
	{
		glViewport(0, 0, f_width, f_height);
		GLRenderScene();
	}
}

void CCG_2ndView::DoShading()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glEnable(GL_LIGHTING);
	/*glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);*/
	/*if(enableTexture)
		glDisable(GL_COLOR_MATERIAL);
	else 
		glEnable(GL_COLOR_MATERIAL);*/
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0.position);
	switch(currentShading)
	{
	case Shading(FLAT):
		glShadeModel(GL_FLAT);
		break;
	case Shading(GOURAUD):
		glShadeModel(GL_SMOOTH);
		break;
	default: glDisable(GL_LIGHTING);
	}
}

void CCG_2ndView::DoDisplay()
{
	if(isPointDisplay)
		GetDocument()->PointDisplay();
	if(isWireDisplay)
		GetDocument()->WireframeDisplay();
	if(isQuadDisplay)
		GetDocument()->QuadMeshDisplay(currentShading);
	if(isVectorDisplay)
		GetDocument()->DrawNormalVector();
	if(enableTexture)
		GetDocument()->TextureDisplay(currentShading);
	else
		GetDocument()->DisableTexture();
}

void CCG_2ndView::GLRenderScene(int multiView) // 실제 그림을 그리는 부분
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DoModelBasicTransform();
	if(multiView == MultiView(NORMAL) || multiView == 0)
	{
		user.DoModelTransform();
	}
	else
	{
		extra.DoModelTransform();
	}
	DoCameraTransform(multiView);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	DoViewing();
	DoShading();
	DoDisplay();
}

void CCG_2ndView::DoModelBasicTransform()
{
	// 임의의 축 회전
	if(isRRotation)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(f_sLineX, f_sLineY, f_sLineZ);
		glVertex3f(f_eLineX, f_eLineY, f_eLineZ);
		glEnd();
		isRRotation = false;
	}
	glTranslated(-f_sLineX, -f_sLineY, -f_sLineZ);
	glRotatef(f_rAngle, f_eLineX-f_sLineX, f_eLineY-f_sLineY, f_eLineZ-f_sLineZ);
	glTranslated(f_sLineX, f_sLineY, f_sLineZ);
	// Pivot 기준 스케일링
	glTranslated(-f_pPointX, -f_pPointY, -f_pPointZ);
	glScalef(f_pScaleX, f_pScaleY, f_pScaleZ);
	glTranslated(f_pPointX, f_pPointY, f_pPointZ);
}

void CCG_2ndView::DoViewing()
{
	/*if(currentView == -1)
		return;*/
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	switch(currentView)
	{
	case Viewing(ORTHOGRAPHIC):
		glOrtho(f_left, f_right, f_bottom, f_top, f_near, f_far);
		break;
	case Viewing(PERSPECTIVE):
		gluPerspective(f_fov, f_aspect, f_near, f_far);
		break;
	case Viewing(FRUSTUM):
		glFrustum(f_left, f_right, f_bottom, f_top, f_near, f_far);
		break;
	default:	// For testing
		glOrtho(-2, 2, -2, 2, -1, 10);
	}
}

void CCG_2ndView::DoCameraTransform(int MultiView)
{
	switch(MultiView)
	{
	case TOP:
		if(isCameraRotate)
			gluLookAt(0.5 + f_eyeX + f_posX, 2 + f_eyeY, -0.5 + f_eyeZ + f_posZ, f_atX, f_atY, f_atZ, f_upX, -1 + f_upY, -1 + f_upZ);
		else
			gluLookAt(0.5 + f_eyeX, 2 + f_eyeY, -0.5 + f_eyeZ, f_atX, f_atY, f_atZ, f_upX, -1 + f_upY, -1 + f_upZ);
		break;
	case FRONT:
		if(isCameraRotate)
			gluLookAt(0.5 + f_eyeX + f_posX, 2 + f_eyeY, -0.5 + f_eyeZ + f_posZ, f_atX, f_atY, f_atZ, f_upX, -1 + f_upY, -1 + f_upZ);
		else
			gluLookAt(0.5 + f_eyeX, f_eyeY, f_eyeZ, f_atX, f_atY, f_atZ, f_upX, f_upY, f_upZ);
		break;
	case SIDE:
		if(isCameraRotate)
			gluLookAt(0.5 + f_eyeX + f_posX, 2 + f_eyeY, -0.5 + f_eyeZ + f_posZ, f_atX, f_atY, f_atZ, f_upX, -1 + f_upY, -1 + f_upZ);
		else
			gluLookAt(-4 + f_eyeX, f_eyeY, f_eyeZ, f_atX, f_atY, f_atZ, f_upX, f_upY, f_upZ);
		break;
	case NORMAL:
		if(isCameraRotate)
			gluLookAt(0.5 + f_eyeX + f_posX, 2 + f_eyeY, -0.5 + f_eyeZ + f_posZ, f_atX, f_atY, f_atZ, f_upX, -1 + f_upY, -1 + f_upZ);
		else
			gluLookAt(-1 + f_eyeX, 1 + f_eyeY, f_eyeZ, f_atX, f_atY, f_atZ, f_upX, f_upY, f_upZ);
		break;
	default:
		if(isCameraRotate)
			gluLookAt(f_eyeX + f_posX, f_eyeY, f_eyeZ + f_posZ, f_atX, f_atY, f_atZ, f_upX, f_upY, f_upZ);
		else
			gluLookAt(f_eyeX, f_eyeY, f_eyeZ, f_atX, f_atY, f_atZ, f_upX, f_upY, f_upZ);
	}
}

void CCG_2ndView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog fileDlg(TRUE, _T("*.*"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("All Files(*.*)|*.*|"), NULL);
	if(fileDlg.DoModal() == IDOK)
	{
		InitPosition();
		GetDocument()->Destroy();
		Invalidate(FALSE);
		CString filePath = _T("");
		setlocale(LC_ALL, "Korean");
		filePath.Format(_T("%s/%s"), fileDlg.GetFolderPath(), fileDlg.GetFileName());
		GetDocument()->Initialize(filePath);
		CString msgStr;
		msgStr.Format(_T("%s가 선택되었습니다."), fileDlg.GetFileName());
		AfxMessageBox(msgStr);
	}
}

void CCG_2ndView::OnLoadPoint()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChangeDisplayMode(ID_LOAD_POINT, &isPointDisplay);
}

void CCG_2ndView::OnLoadWire()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChangeDisplayMode(ID_LOAD_WIRE, &isWireDisplay);
}

void CCG_2ndView::OnLoadQuad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChangeDisplayMode(ID_LOAD_QUAD, &isQuadDisplay);
}

void CCG_2ndView::OnLoadVector()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChangeDisplayMode(ID_LOAD_VECTOR, &isVectorDisplay);
}

void CCG_2ndView::ChangeDisplayMode(UINT id, bool *displayMode)
{
	*displayMode = !(*displayMode);

	CMenu *pMenu = AfxGetMainWnd()->GetMenu();
	Invalidate(false);
}

void CCG_2ndView::OnTransformTrans()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Translation tranDlg;
	if(tranDlg.DoModal() == IDOK)
	{
		user.f_transX = tranDlg.f_transX;
		user.f_transY = tranDlg.f_transY;
		user.f_transZ = tranDlg.f_transZ;
	}
	Invalidate(false);
}

void CCG_2ndView::OnTransformScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Scaling scaleDlg;
	if(scaleDlg.DoModal() == IDOK)
	{
		user.f_scaleX = scaleDlg.f_scaleX;
		user.f_scaleY = scaleDlg.f_scaleY;
		user.f_scaleZ = scaleDlg.f_scaleZ;
	}
	Invalidate(false);
}

void CCG_2ndView::OnTransformPivot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PivotScaling pScaleDlg;
	if(pScaleDlg.DoModal() == IDOK)
	{
		f_pScaleX = pScaleDlg.f_pScaleX;
		f_pScaleY = pScaleDlg.f_pScaleY;
		f_pScaleZ = pScaleDlg.f_pScaleZ;
		f_pPointX = pScaleDlg.f_pPointX;
		f_pPointY = pScaleDlg.f_pPointY;
		f_pPointZ = pScaleDlg.f_pPointZ;
	}
	Invalidate(false);
}

void CCG_2ndView::OnTransformAxis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AxisRotation aRotateDlg;
	if(aRotateDlg.DoModal() == IDOK)
	{
		user.f_aRotateX = aRotateDlg.f_aRotateX;
		user.f_aRotateY = aRotateDlg.f_aRotateY;
		user.f_aRotateZ = aRotateDlg.f_aRotateZ;
	}
	Invalidate(false);
}

void CCG_2ndView::OnTransformRandom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	RandomRotation rRotateDlg;
	if(rRotateDlg.DoModal() == IDOK)
	{
		f_sLineX = rRotateDlg.f_sLineX;
		f_sLineY = rRotateDlg.f_sLineY;
		f_sLineZ = rRotateDlg.f_sLineZ;
		f_eLineX = rRotateDlg.f_eLineX;
		f_eLineY = rRotateDlg.f_eLineY;
		f_eLineZ = rRotateDlg.f_eLineZ;
		f_rAngle = rRotateDlg.f_rAngle;
		isRRotation = true;
	}
	Invalidate(false);
}

void CCG_2ndView::OnOrthographic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OrthoGraphic orthoDlg;
	if(orthoDlg.DoModal() == IDOK)
	{
		f_left = orthoDlg.f_left;
		f_right = orthoDlg.f_right;
		f_bottom = orthoDlg.f_bottom;
		f_top = orthoDlg.f_top;
		f_near = orthoDlg.f_near;
		f_far = orthoDlg.f_far;
		currentView = Viewing(ORTHOGRAPHIC);
	}
	Invalidate(false);
}

void CCG_2ndView::OnPerspective()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Perspective persDlg;
	if(persDlg.DoModal() == IDOK)
	{
		f_fov = persDlg.f_fov;
		f_aspect = persDlg.f_aspect;
		f_near = persDlg.f_near;
		f_far = persDlg.f_far;
		currentView = Viewing(PERSPECTIVE);
	}
	Invalidate(false);
}

void CCG_2ndView::OnFrustum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Frustum frustumDlg;
	if(frustumDlg.DoModal() == IDOK)
	{
		f_left = frustumDlg.f_left;
		f_right = frustumDlg.f_right;
		f_bottom = frustumDlg.f_bottom;
		f_top = frustumDlg.f_top;
		f_near = frustumDlg.f_near;
		f_far = frustumDlg.f_far;
		currentView = Viewing(FRUSTUM);
	}
	Invalidate(false);
}

void CCG_2ndView::OnCameraPosition()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Camera cameraDlg;
	if(cameraDlg.DoModal() == IDOK)
	{
		f_eyeX = cameraDlg.f_eyeX;
		f_eyeY = cameraDlg.f_eyeY;
		f_eyeZ = cameraDlg.f_eyeZ;
		f_atX = cameraDlg.f_atX;
		f_atY = cameraDlg.f_atY;
		f_atZ = cameraDlg.f_atZ;
		f_upX = cameraDlg.f_upX;
		f_upY = cameraDlg.f_upY;
		f_upZ = cameraDlg.f_upZ;
	}
	Invalidate(false);
}

void CCG_2ndView::OnLightPosition()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LightPosition lightPosDlg;
	if(lightPosDlg.DoModal() == IDOK)
	{
		light0.SetPosition(lightPosDlg.f_lightX, lightPosDlg.f_lightY, lightPosDlg.f_lightZ, lightPosDlg.f_isPoint);
	}
	Invalidate(false);
}

void CCG_2ndView::OnLightColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LightColor lightColorDlg;
	if(lightColorDlg.DoModal() == IDOK)
	{
		light0.SetAmbient(lightColorDlg.f_ambientR, lightColorDlg.f_ambientG, lightColorDlg.f_ambientB, lightColorDlg.f_ambientA);
		light0.SetDiffuse(lightColorDlg.f_diffuseR, lightColorDlg.f_diffuseG, lightColorDlg.f_diffuseB, lightColorDlg.f_diffuseA);
		light0.SetSpecular(lightColorDlg.f_specularR, lightColorDlg.f_specularG, lightColorDlg.f_specularB, lightColorDlg.f_specularA);
	}
	Invalidate(false);
}

void CCG_2ndView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(!isRMousePressed)
	{
		rStartPoint = point;
		if(isUserDisplay)
			user.f_aRotateX += 0.1;
		else
			extra.f_aRotateX += 0.1;
	}
	isRMousePressed = true;
	CView::OnRButtonDown(nFlags, point);
}


void CCG_2ndView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(isRMousePressed)
	{
		isRMousePressed = false;
	}
	CView::OnRButtonUp(nFlags, point);
}

void CCG_2ndView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isRMouseDbPressed = !isRMouseDbPressed;
	CView::OnRButtonDblClk(nFlags, point);
}

void CCG_2ndView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(!isLMousePressed)
		tStartPoint = point;
	isLMousePressed = true;
	CView::OnLButtonDown(nFlags, point);
}

void CCG_2ndView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(isLMousePressed)
	{
		isLMousePressed = false;
	}
	CView::OnLButtonUp(nFlags, point);
}

void CCG_2ndView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(isUserDisplay)
	{
		user.f_scaleX += 0.1;
		user.f_scaleY += 0.1;
		user.f_scaleZ += 0.1;
	}
	else
	{
		extra.f_scaleX += 0.1;
		extra.f_scaleY += 0.1;
		extra.f_scaleZ += 0.1;
	}
	Invalidate(FALSE);
	CView::OnMButtonDown(nFlags, point);
}

void CCG_2ndView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(isUserDisplay)
	{
		user.f_scaleX -= 0.2;
		user.f_scaleY -= 0.2;
		user.f_scaleZ -= 0.2;
	}
	else
	{
		extra.f_scaleX -= 0.2;
		extra.f_scaleY -= 0.2;
		extra.f_scaleZ -= 0.2;
	}
	Invalidate(FALSE);
	CView::OnMButtonDblClk(nFlags, point);
}

BOOL CCG_2ndView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(zDelta > 0)
	{
		if(isUserDisplay)
		{
			user.f_scaleX += 0.1;
			user.f_scaleY += 0.1;
			user.f_scaleZ += 0.1;
		}
		else
		{
			extra.f_scaleX += 0.1;
			extra.f_scaleY += 0.1;
			extra.f_scaleZ += 0.1;
		}
	}
	else
	{
		if(isUserDisplay)
		{
			user.f_scaleX -= 0.1;
			user.f_scaleY -= 0.1;
			user.f_scaleZ -= 0.1;
		}
		else
		{
			extra.f_scaleX -= 0.1;
			extra.f_scaleY -= 0.1;
			extra.f_scaleZ -= 0.1;
		}
		
	}
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCG_2ndView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(!enableMultiView || point.x >= f_width/2 && point.y >= f_height/2)
	{
		isUserDisplay = true;
	}
	else
	{
		isUserDisplay = false;
	}
	if(isLMousePressed)
	{
		if(isUserDisplay)
		{
			user.f_transX += (float)((point.x - tStartPoint.x) / 200.0);
			user.f_transY += (float)((tStartPoint.y - point.y) / 200.0);
		}
		else
		{
			extra.f_transX += (float)((point.x - tStartPoint.x) / 200.0);
			extra.f_transY += (float)((tStartPoint.y - point.y) / 200.0);
		}	
		tStartPoint = point;
	}
	else if(isRMousePressed)
	{
		if(isUserDisplay)
		{
			user.f_aRotateX += (float)(point.x - rStartPoint.x);
			user.f_aRotateY += (float)(rStartPoint.y - point.y);
		}
		else
		{
			extra.f_aRotateX += (float)(point.x - rStartPoint.x);
			extra.f_aRotateY += (float)(rStartPoint.y - point.y);
		}
		rStartPoint = point;
	}
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CCG_2ndView::OnUpdate3dviewingFrustum(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(currentView == Viewing(FRUSTUM));
}

void CCG_2ndView::OnUpdate3dviewingOrthographic(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(currentView == Viewing(ORTHOGRAPHIC));
}

void CCG_2ndView::OnUpdate3dviewingPerspective(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(currentView == Viewing(PERSPECTIVE));
}

void CCG_2ndView::OnUpdateLoadPoint(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 0)
	{
		pCmdUI->SetCheck(isPointDisplay);
	}
}

void CCG_2ndView::OnUpdateLoadWire(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 1)
	{
		pCmdUI->SetCheck(isWireDisplay);
	}
}

void CCG_2ndView::OnUpdateLoadQuad(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 2)
	{
		pCmdUI->SetCheck(isQuadDisplay);
	}
}

void CCG_2ndView::OnUpdateLoadVector(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 3)
	{
		pCmdUI->SetCheck(isVectorDisplay);
	}
}

void CCG_2ndView::OnTextureOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog fileDlg(TRUE, _T("*.*"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("All Files(*.*)|*.*|"), NULL);
	if(fileDlg.DoModal() == IDOK)
	{
		CString msgStr;
		msgStr.Format(_T("%s가 선택되었습니다."), fileDlg.GetFileName());
		AfxMessageBox(msgStr);
		GetDocument()->SetTextureFile(fileDlg.GetFileName());
		hasTexture = true;
	}
	else
	{
		hasTexture = false;
		enableTexture = false;
	}
}

void CCG_2ndView::OnTextureEnable()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(hasTexture)
	{
		enableTexture = !enableTexture;
		Invalidate(FALSE);
	}
	else
	{
		CString msgStr;
		msgStr = ("파일을 먼저 선택해야 합니다.");
		AfxMessageBox(msgStr);
	}
}

void CCG_2ndView::OnUpdateTextureOpen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 0)
	{
		pCmdUI->SetCheck(hasTexture);
	}
}

void CCG_2ndView::OnUpdateTextureEnable(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(pCmdUI->m_nIndex == 1)
	{
		pCmdUI->SetCheck(enableTexture);
	}
}

void CCG_2ndView::OnUpdateShadingFlat(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(currentShading == Shading(FLAT)); 
}

void CCG_2ndView::OnShadingFlat()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentShading = Shading(FLAT);
	Invalidate(FALSE);
}

void CCG_2ndView::OnUpdateShadingGouraud(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(currentShading == Shading(GOURAUD));
}


void CCG_2ndView::OnShadingGouraud()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentShading = Shading(GOURAUD);
	Invalidate(FALSE);
}

void CCG_2ndView::OnShadingNone()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentShading = Shading(NONE);
	Invalidate(FALSE);
}


void CCG_2ndView::OnMultiviewEnable()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	enableMultiView = !enableMultiView;
	if(enableMultiView)
	{
		InitPosition();
	}
	Invalidate(FALSE);
}


void CCG_2ndView::OnCameraRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	isCameraRotate = !isCameraRotate;
	InitPosition();
	if(isCameraRotate)
		SetTimer(NULL, 200, NULL);
	else
		KillTimer(NULL);
}

void CCG_2ndView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDocument()->Initialize(_T("HappyBuddha_WithTexture.obj"));
}

void CCG_2ndView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	f_rotY += 0.001;
	if(f_rotY > 0.072) {
		f_rotY = 0;
		KillTimer(NULL);
		isCameraRotate = false;
	}
	float distance = sqrt( f_eyeX * f_eyeX + f_eyeZ * f_eyeZ);
	f_posX = float(distance * cos(f_rotY*360/3.1415f));
	f_posZ = float(distance * sin(f_rotY*360/3.1415f));
	Invalidate(FALSE);
	
	CView::OnTimer(nIDEvent);
}

void CCG_2ndView::OnUpdateMultiviewEnable(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(enableMultiView);
}