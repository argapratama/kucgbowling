// CameraPosition.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Camera.h"


// Camera 대화 상자입니다.

IMPLEMENT_DYNAMIC(Camera, CDialog)

Camera::Camera(CWnd* pParent /*=NULL*/)
	: CDialog(Camera::IDD, pParent)
{
	f_eyeX = -2; f_eyeY = 0; f_eyeZ = -1;
	f_atX = -1.5; f_atY = 0; f_atZ = -1.5;
	f_upX = 0; f_upY = 1; f_upZ = 0;
}

Camera::~Camera()
{
}

void Camera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POS_X, f_eyeX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, f_eyeY);
	DDX_Text(pDX, IDC_EDIT_POS_Z, f_eyeZ);
	DDX_Text(pDX, IDC_EDIT_FOC_X, f_atX);
	DDX_Text(pDX, IDC_EDIT_FOC_Y, f_atY);
	DDX_Text(pDX, IDC_EDIT_FOC_Z, f_atZ);
	DDX_Text(pDX, IDC_EDIT_UP_X, f_upX);
	DDX_Text(pDX, IDC_EDIT_UP_Y, f_upY);
	DDX_Text(pDX, IDC_EDIT_UP_Z, f_upZ);
}


BEGIN_MESSAGE_MAP(Camera, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Camera::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Camera::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Camera 메시지 처리기입니다.

void Camera::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void Camera::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
