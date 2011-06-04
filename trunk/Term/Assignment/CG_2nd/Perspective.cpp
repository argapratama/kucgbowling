// Perspective.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Perspective.h"


// Perspective 대화 상자입니다.

IMPLEMENT_DYNAMIC(Perspective, CDialog)

Perspective::Perspective(CWnd* pParent /*=NULL*/)
	: CDialog(Perspective::IDD, pParent)
{
	f_fov = f_aspect = f_near = f_far = 0;
}

Perspective::~Perspective()
{
}

void Perspective::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FOV, f_fov);
	DDX_Text(pDX, IDC_EDIT_ASPECT, f_aspect);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(Perspective, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Perspective::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Perspective::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Perspective 메시지 처리기입니다.

void Perspective::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void Perspective::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
