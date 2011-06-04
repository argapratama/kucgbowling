// LightPosition.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "LightPosition.h"


// LightPosition 대화 상자입니다.

IMPLEMENT_DYNAMIC(LightPosition, CDialog)

LightPosition::LightPosition(CWnd* pParent /*=NULL*/)
	: CDialog(LightPosition::IDD, pParent)
{
	f_lightX = -1.0f;
	f_lightY = 0.0f;
	f_lightZ = -3.0f;
	f_isPoint = 1.0f;
}

LightPosition::~LightPosition()
{
}

void LightPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_lightX);
	DDX_Text(pDX, IDC_EDIT_Y, f_lightY);
	DDX_Text(pDX, IDC_EDIT_Z, f_lightZ);
	DDX_Text(pDX, IDC_EDIT_P, f_isPoint);
}


BEGIN_MESSAGE_MAP(LightPosition, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &LightPosition::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &LightPosition::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// LightPosition 메시지 처리기입니다.

void LightPosition::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void LightPosition::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
