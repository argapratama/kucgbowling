
// BasicFunctionsDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "BasicFunctions.h"
#include "BasicFunctionsDlg.h"
#include "afxdialogex.h"
#include "Lighting.h"
#include "DateTime.h"
#include "Physics.h"
#include "Quaternion.h"
#include "TMath.h"
#include <gl/GL.h>
#include <glut.h>

#include <Mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace Virgin;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBasicFunctionsDlg 대화 상자




CBasicFunctionsDlg::CBasicFunctionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicFunctionsDlg::IDD, pParent)
    , rotateLeftButtonDown_(false)
    , rotateRightButtonDown_(false)
    , rotateUpButtonDown_(false)
    , rotateDownButtonDown_(false)
    , rollLeftButtonDown_(false)
    , rollRightButtonDown_(false)
    , moveUpButtonDown_(false)
    , moveDownButtonDown_(false)
    , moveLeftButtonDown_(false)
    , moveRightButtonDown_(false)
    , moveFarButtonDown_(false)
    , moveNearButtonDown_(false)
    , biggerButtonDown_(false)
    , smallerButtonDown_(false)
    , firstTime_(DateTime::SinceSystemStarted())
    , lastTime_(DateTime::SinceSystemStarted())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBasicFunctionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISPLAY_PANEL, displayPanel_);
	DDX_Control(pDX, IDC_FPS_STATIC, fpsStatic_);
	DDX_Control(pDX, IDC_SPEED_SLIDER, speedSlider_);
	DDX_Control(pDX, IDC_CAMERA_AUTO_ROTATION_CHECK, cameraAutoRotateCheck_);
	DDX_Control(pDX, IDC_SHOW_COLLISION_INFO_CHECK, showCollisionInfoCheck_);
	DDX_Control(pDX, IDC_PAUSE_CHECK, pauseCheck_);
}

BEGIN_MESSAGE_MAP(CBasicFunctionsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_ROTATE_LEFT_BUTTON, &CBasicFunctionsDlg::OnBnClickedRotateLeftButton)
    ON_BN_CLICKED(IDC_RESET_SPRITE_BUTTON, &CBasicFunctionsDlg::OnBnClickedResetSpriteButton)

    ON_BN_CLICKED(IDC_TEST_BUTTON, &CBasicFunctionsDlg::OnBnClickedTestButton)
    ON_BN_CLICKED(IDC_DRAW_NORMAL_CHECK, &CBasicFunctionsDlg::OnBnClickedDrawNormalCheck)
    ON_BN_CLICKED(IDC_MESH_POINT_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshPointButton)
    ON_BN_CLICKED(IDC_MESH_WIREFRAME_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshWireframeButton)
    ON_BN_CLICKED(IDC_MESH_QUAD_BUTTON, &CBasicFunctionsDlg::OnBnClickedMeshQuadButton)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SPEED_SLIDER, &CBasicFunctionsDlg::OnNMReleasedcaptureSpeedSlider)
    ON_WM_MOUSEWHEEL()
    ON_BN_CLICKED(IDC_CAMERA_AUTO_ROTATION_CHECK, &CBasicFunctionsDlg::OnBnClickedCameraAutoRotationCheck)
    ON_BN_CLICKED(IDC_LIGHT_CHECK, &CBasicFunctionsDlg::OnBnClickedLightCheck)
    ON_BN_CLICKED(IDC_FLAT_SHADING_BUTTON, &CBasicFunctionsDlg::OnBnClickedFlatShadingButton)
    ON_BN_CLICKED(IDC_GOURAUD_SHADING_BUTTON, &CBasicFunctionsDlg::OnBnClickedGouraudShadingButton)
    ON_BN_CLICKED(IDC_USER_VIEW_SELECTED_CHECK, &CBasicFunctionsDlg::OnBnClickedUserViewSelectedCheck)
    ON_BN_CLICKED(IDC_RESET_CAMERA_ROTATION_BUTTON, &CBasicFunctionsDlg::OnBnClickedResetCameraRotationButton)
    ON_BN_CLICKED(IDC_DRAW_TEXTURE_CHECK, &CBasicFunctionsDlg::OnBnClickedDrawTextureCheck)
    ON_BN_CLICKED(IDC_SHOW_COLLISION_INFO_CHECK, &CBasicFunctionsDlg::OnBnClickedShowCollisionInfoCheck)
    ON_BN_CLICKED(IDC_TEST2_BUTTON, &CBasicFunctionsDlg::OnBnClickedTest2Button)
    ON_BN_CLICKED(IDC_TEST3_BUTTON, &CBasicFunctionsDlg::OnBnClickedTest3Button)
    ON_BN_CLICKED(IDC_TEST4_BUTTON, &CBasicFunctionsDlg::OnBnClickedTest4Button)
    ON_BN_CLICKED(IDC_TEST5_BUTTON, &CBasicFunctionsDlg::OnBnClickedTest5Button)
    ON_BN_CLICKED(IDC_TEST4_BUTTON4, &CBasicFunctionsDlg::OnBnClickedTest4Button4)
    ON_BN_CLICKED(IDC_TEST4_BUTTON3, &CBasicFunctionsDlg::OnBnClickedTest4Button3)
END_MESSAGE_MAP()


// CBasicFunctionsDlg 메시지 처리기

BOOL CBasicFunctionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
    
    RECT rect;
    displayPanel_.GetWindowRect(&rect);
    ScreenToClient(&rect);
    openGlPanel_.Create(rect, this);
    
    InitializeWorld();
    InitializeSpriteMassProperties();
    InitializeControls();
    
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBasicFunctionsDlg::InitializeWorld()
{
    World().ResizePinCount(10);

	if(!World().GetBall().Load(L"bowling_ball.obj", L"green_ball_skin.bmp"))
    {
        MessageBox(L"bowling_ball.obj doesn't exist. Please restart this application ^^;;");
    }
	World().GetBall().TranslateMore(6.0, -0.2, 1.0);
    //World().GetBall().TranslateMore(1.0, 6.0, -0.2);
	
	if(!World().GetPin(0).Load(L"bowling_pin.obj", L""))
    {
        MessageBox(L"bowling_pin.obj doesn't exist. Please restart this application ^^;;");
    }

	World().GetPin(0).CopyTo(World().GetPin(1));
	World().GetPin(0).CopyTo(World().GetPin(2));
	World().GetPin(0).CopyTo(World().GetPin(3));
	World().GetPin(0).CopyTo(World().GetPin(4));
	World().GetPin(0).CopyTo(World().GetPin(5));
	World().GetPin(0).CopyTo(World().GetPin(6));
	World().GetPin(0).CopyTo(World().GetPin(7));
	World().GetPin(0).CopyTo(World().GetPin(8));
	World().GetPin(0).CopyTo(World().GetPin(9));

    // The Main Light
    World().GetLight().MoveTo(0, 20, 30);
    World().GetLight().Enable();

    for(int i = 0; i < 10; ++i)
    {
        World().Sprites().push_back(&World().GetPin(i));
    }
}

void CBasicFunctionsDlg::InitializeSpriteMassProperties()
{
    World().ResetSprites();
}

void CBasicFunctionsDlg::InitializeBall(Virgin::Ball& ball)
{
}

void CBasicFunctionsDlg::InitializePin(Pin& pin)
{
}

void CBasicFunctionsDlg::InitializeControls()
{
    // Speed Slider
    speedSlider_.SetRange(1, 2000);
    speedSlider_.SetRangeMin(1);
    speedSlider_.SetRangeMax(2000);
    speedSlider_.SetPos(100);

    openGlPanel_.SetManipulatingSprite(true);

    Lighting().EnableLighting();

}

void CBasicFunctionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBasicFunctionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBasicFunctionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CBasicFunctionsDlg::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    return CDialogEx::OnEraseBkgnd(pDC);
}


void CBasicFunctionsDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
}

void CBasicFunctionsDlg::UpdateAndDraw()
{
    DateTime currTime = DateTime::SinceSystemStarted();
    TimeSpan timeDelta = currTime - lastTime_;
    lastTime_ = currTime;

    if(timeDelta.TotalSeconds() != 0.0)
    {
        CString fpsText;
        int fps = (double)1.0/timeDelta.TotalSeconds();
        fpsText.Format(L"%d", fps);
        fpsStatic_.SetWindowText(fpsText);
    }

    if(!pauseCheck_.GetCheck())
    {
        static TimeSpan fakeTime(0);
        static const TimeSpan fakeTimeDelta(30);

        //World().Update(lastTime_ - firstTime_, timeDelta);
        World().Update(fakeTime, fakeTimeDelta);
        fakeTime += fakeTimeDelta;
    }

    const float Speed = static_cast<float>(speedSlider_.GetPos() / 100.0);

    const float MoveUnit = 0.01 * Speed;
    const float RotateUnit = 0.5 * Speed;
    const float ScaleRate = 0.01 * Speed;

    float moveX = 0.0;
    float moveY = 0.0;
    float moveZ = 0.0;

    float rotateXAngle = 0.0;
    float rotateYAngle = 0.0;
    float rotateZAngle = 0.0;

    float magnitudeRate = 1.0;

    if(moveLeftButtonDown_)
    {   
        moveX = -MoveUnit;
    }
    else if(moveRightButtonDown_)
    {
        moveX = MoveUnit;
    }

    if(moveUpButtonDown_)
    {   
        moveY = MoveUnit;
    }
    else if(moveDownButtonDown_)
    {
        moveY = -MoveUnit;
    }

    if(moveFarButtonDown_)
    {   
        moveZ = -MoveUnit;
    }
    else if(moveNearButtonDown_)
    {
        moveZ = MoveUnit;
    }



    if(rotateUpButtonDown_)
    {   
        rotateXAngle = -RotateUnit;
    }
    else if(rotateDownButtonDown_)
    {
        rotateXAngle = RotateUnit;
    }

    if(rotateLeftButtonDown_)
    {   
        rotateYAngle = -RotateUnit;
    }
    else if(rotateRightButtonDown_)
    {
        rotateYAngle = RotateUnit;
    }

    if(rollLeftButtonDown_)
    {   
        rotateZAngle = RotateUnit;
    }
    else if(rollRightButtonDown_)
    {
        rotateZAngle = -RotateUnit;
    }

    if(biggerButtonDown_)
    {
        magnitudeRate += ScaleRate;
    }
    else if(smallerButtonDown_)
    {
        magnitudeRate -= ScaleRate;
    }

    World().GetBall().TranslateMore(moveZ, moveX, moveY);
    World().GetBall().RotateXMore(rotateXAngle);
    World().GetBall().RotateYMore(rotateYAngle);
    World().GetBall().RotateZMore(rotateZAngle);
    World().GetBall().ScaleRate(magnitudeRate, magnitudeRate, magnitudeRate);

	World().GetBall2().TranslateMore(moveX, moveY, moveZ);
    World().GetBall2().RotateXMore(rotateXAngle);
    World().GetBall2().RotateYMore(rotateYAngle);
    World().GetBall2().RotateZMore(rotateZAngle);
    World().GetBall2().ScaleRate(magnitudeRate, magnitudeRate, magnitudeRate);

    Vector3 values;
    Vector3 values2;

    //
    // Camera
    //
    if(cameraAutoRotateCheck_.GetCheck())
    {
        //World().GetCamera().RotateYMore(RotateUnit);
        World().GetCamera().RotateZMore(RotateUnit);
    }

    //values.X() = ToFloat(cameraLocationXEdit_);
    //values.Y() = ToFloat(cameraLocationYEdit_);
    //values.Z() = ToFloat(cameraLocationZEdit_);
    //World().GetCamera().MoveTo(values.X(), values.Y(), values.Z());

    //values.X() = ToFloat(cameraLookAtXEdit_);
    //values.Y() = ToFloat(cameraLookAtYEdit_);
    //values.Z() = ToFloat(cameraLookAtZEdit_);
    //World().GetCamera().LookAt(values.X(), values.Y(), values.Z());

    //values.X() = ToFloat(cameraUpXEdit_);
    //values.Y() = ToFloat(cameraUpYEdit_);
    //values.Z() = ToFloat(cameraUpZEdit_);
    //World().GetCamera().SetUpVector(values.X(), values.Y(), values.Z());
    //World().GetCamera().Apply();

    // 
    // Light
    //
    World().GetLight().SetAmbient(0.5, 0.5, 0.5);
    World().GetLight().SetDiffuse(1.0, 1.0, 1.0);
    World().GetLight().SetSpecular(0.5, 0.5, 0.5);


	
    openGlPanel_.Invalidate();
}



BOOL CBasicFunctionsDlg::DestroyWindow() 
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    return CDialogEx::DestroyWindow();
}


void CBasicFunctionsDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CBasicFunctionsDlg::OnOK()
{
    DestroyWindow();
}


void CBasicFunctionsDlg::OnCancel()
{
    DestroyWindow();
}


void CBasicFunctionsDlg::OnBnClickedRotateLeftButton()
{
    
}


BOOL CBasicFunctionsDlg::PreTranslateMessage(MSG* pMsg)
{
    struct ButtonDownStatus
    {
        CWnd* control;
        bool* isButtonDown;
    };

    bool isButtonDown;
    switch(pMsg->message)
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        isButtonDown = pMsg->message == WM_LBUTTONDOWN;
        break;
    case WM_KEYDOWN:
        switch(pMsg->wParam)
        {
            case VK_LEFT:
                //World().GetCamera().RotateZMore(10.0);
                World().GetCamera().MoveMore(1.0, 0.0, 0.0);
                return true;
            case VK_RIGHT:
                //World().GetCamera().RotateZMore(-10.0);
                World().GetCamera().MoveMore(-1.0, 0.0, 0.0);
                return true;
            case VK_UP:
                //World().GetCamera().RotateYMore(10.0);
                World().GetCamera().MoveMore(0.0, 0.0, 1.0);
                return true;
            case VK_DOWN:
                //World().GetCamera().RotateYMore(-10.0);
                World().GetCamera().MoveMore(0.0, 0.0, -1.0);
                return true;
        }
        break;
    }
    
    return CDialogEx::PreTranslateMessage(pMsg);
}


void CBasicFunctionsDlg::OnBnClickedResetSpriteButton()
{
    World().ResetSprites();
}

float CBasicFunctionsDlg::ToFloat(const CWnd& wnd)
{
    CString text;
    float value;
    wnd.GetWindowText(text);
    swscanf(text, L"%f", &value);
    return value;
}


void CBasicFunctionsDlg::OnEditChange()
{
    UpdateAndDraw();
}


void CBasicFunctionsDlg::OnBnClickedTestButton()
{
    //World().GetBall().Load(L"HappyBuddha.obj");
    //CFileDialog fileDialog(TRUE, L"obj", NULL, OFN_FILEMUSTEXIST | OFN_LONGNAMES, L"Object (*.obj) | *.obj", this);
    //INT_PTR result = fileDialog.DoModal();
    //if(result == IDOK)
    //{
    //    CString pathName = fileDialog.GetPathName();
    //    MessageBox(pathName);
    //}

    World().GetBall().Position().Z() = 10.0f;
}


void CBasicFunctionsDlg::OnBnClickedDrawNormalCheck()
{
    //World().GetBall().SetDrawNormal(drawNormalCheck_.GetCheck() != 0);
}


void CBasicFunctionsDlg::OnBnClickedMeshPointButton()
{
    World().GetBall().SetMeshMode(MeshMode_Point);
    World().GetBall2().SetMeshMode(MeshMode_Point);
}


void CBasicFunctionsDlg::OnBnClickedMeshWireframeButton()
{
    World().GetBall().SetMeshMode(MeshMode_Wireframe);
    World().GetBall2().SetMeshMode(MeshMode_Wireframe);
}


void CBasicFunctionsDlg::OnBnClickedMeshQuadButton()
{
    World().GetBall().SetMeshMode(MeshMode_QuadMesh);
    World().GetBall2().SetMeshMode(MeshMode_QuadMesh);
}


void CBasicFunctionsDlg::OnNMReleasedcaptureSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
}


BOOL CBasicFunctionsDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    //GetSelectedSprite().TranslateMore(0.0, 0.0, zDelta/240.0);
    //GetSelectedSprite().TranslateMore(zDelta/240.0, 0.0, 0.0);
    World().GetCamera().MoveMore(0, zDelta/60, 0);
    return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CBasicFunctionsDlg::OnBnClickedCameraAutoRotationCheck()
{
}


void CBasicFunctionsDlg::OnBnClickedLightCheck()
{
    //Lighting lighting;
    //if(lightCheck_.GetCheck())
    //{
    //    lighting.EnableLighting();
    //}
    //else
    //{
    //    lighting.DisableLighting();
    //}
}


void CBasicFunctionsDlg::OnBnClickedFlatShadingButton()
{
    Lighting lighting;
    lighting.SetShadeModelFlat();
}


void CBasicFunctionsDlg::OnBnClickedGouraudShadingButton()
{
    Lighting lighting;
    lighting.SetShadeModelSmooth();
}

Virgin::Sprite& CBasicFunctionsDlg::GetSelectedSprite()
{
    //if(userViewSelectedCheck_.GetCheck())
    //{
    //    return World().GetBall();
    //}
    //else
    //{
    //    return World().GetBall2();
    //}
}


void CBasicFunctionsDlg::OnBnClickedUserViewSelectedCheck()
{
    //if(userViewSelectedCheck_.GetCheck())
    //{
    //    openGlPanel_.SetManipulatingSprite(true);
    //}
    //else
    //{
    //    openGlPanel_.SetManipulatingSprite(false);
    //}
}


void CBasicFunctionsDlg::OnBnClickedResetCameraRotationButton()
{
    World().GetCamera().ResetRotation();
}


void CBasicFunctionsDlg::OnBnClickedDrawTextureCheck()
{
    //if(drawTextureCheck_.GetCheck())
    //{
    //    World().GetBall().SetDrawTexture(true);
    //    World().GetBall2().SetDrawTexture(true);
    //}
    //else
    //{
    //    World().GetBall().SetDrawTexture(false);
    //    World().GetBall2().SetDrawTexture(false);
    //}
}

// World Instance 좀 더 짧은 코드로 구할 수 있도록
World& CBasicFunctionsDlg::World()
{
    return World::Instance();
}


void CBasicFunctionsDlg::OnBnClickedShowCollisionInfoCheck()
{
    if(showCollisionInfoCheck_.GetCheck())
    {
        World().ShowCollisionInfo();
    }
    else
    {
        World().HideCollisionInfo();
    }
}


void CBasicFunctionsDlg::OnBnClickedTest2Button()
{
    static bool first = true;
    float randomX;
    if(first)
    {
        randomX = Math::IntervalRandom(0.0f, 10000.0f, timeGetTime());
        first = false;
    }
    else
    {
        randomX = Math::IntervalRandom(0.0f, 10000.0f);
    }
    if(World().GetBall().GetRigidBody().GetPosition().X() > 0.0f)
    {
        // 공이 X 쪽에 있으니 -X 쪽으로 던지게 해야 함
        if(randomX > 0.0f)
        {
            randomX = -randomX;
        }
    }

    World().GetBall().GetRigidBody().AppendInternalForce(Vector3(randomX, -100000.0f, 0.0f));
    //World().GetBall().SetVelocity(Vector3(0.0f, 1.0f, 0.0f), 0.5f);
    //World().GetBall().GetRigidBody().ApplyForce(Vector3(-100.0, 0.0, 0.0));
}


void CBasicFunctionsDlg::OnBnClickedTest3Button()
{
    World().GetBall().SetVelocity(Vector3(0.0f, 0.0f, 0.0f), 0.0f);
}


void CBasicFunctionsDlg::OnBnClickedTest4Button()
{
    lastTime_ += 50;
    World().Update(lastTime_ - firstTime_, TimeSpan(50));
}


void CBasicFunctionsDlg::OnBnClickedButtonCameraLeft()
{
	World().GetCamera().RotateZMore(10.0);
	UpdateAndDraw();
}


void CBasicFunctionsDlg::OnBnClickedButtonCameraRight()
{
	World().GetCamera().RotateZMore(-10.0);
	UpdateAndDraw();
}


void CBasicFunctionsDlg::OnBnClickedTest5Button()
{
    World().GetPin(0).Position().Z() = 10.0f;
    Vector3 tmp(1.0, 0.0, 0.0);
    Quaternion ori;
    ori.FromAxisAngle(tmp, 1.0f);
    World().GetPin(0).GetRigidBody().SetQOrientation(ori);
}


void CBasicFunctionsDlg::OnBnClickedTest4Button4()
{
    lastTime_ += 10;
    World().Update(lastTime_ - firstTime_, TimeSpan(10));
}


void CBasicFunctionsDlg::OnBnClickedTest4Button3()
{
    lastTime_ += 100;
    World().Update(lastTime_ - firstTime_, TimeSpan(100));
}
