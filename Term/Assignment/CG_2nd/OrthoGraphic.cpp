// OrthoGraphic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "OrthoGraphic.h"


// OrthoGraphic 대화 상자입니다.

IMPLEMENT_DYNAMIC(OrthoGraphic, CDialog)

OrthoGraphic::OrthoGraphic(CWnd* pParent /*=NULL*/)
	: CDialog(OrthoGraphic::IDD, pParent)
{
	f_left = f_right = f_bottom = f_top = f_near = f_far = 0;
}

OrthoGraphic::~OrthoGraphic()
{
}

void OrthoGraphic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFT, f_left);
	DDX_Text(pDX, IDC_EDIT_RIGHT, f_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, f_bottom);
	DDX_Text(pDX, IDC_EDIT_TOP, f_top);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(OrthoGraphic, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &OrthoGraphic::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &OrthoGraphic::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// OrthoGraphic 메시지 처리기입니다.

void OrthoGraphic::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void OrthoGraphic::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
