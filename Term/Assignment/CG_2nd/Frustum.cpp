// Frustum.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Frustum.h"


// Frustum 대화 상자입니다.

IMPLEMENT_DYNAMIC(Frustum, CDialog)

Frustum::Frustum(CWnd* pParent /*=NULL*/)
	: CDialog(Frustum::IDD, pParent)
{
	f_left = f_right = f_bottom = f_top = f_near = f_far = 0;
}

Frustum::~Frustum()
{
}

void Frustum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFT, f_left);
	DDX_Text(pDX, IDC_EDIT_RIGHT, f_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, f_bottom);
	DDX_Text(pDX, IDC_EDIT_TOP, f_top);
	DDX_Text(pDX, IDC_EDIT_NEAR, f_near);
	DDX_Text(pDX, IDC_EDIT_FAR, f_far);
}


BEGIN_MESSAGE_MAP(Frustum, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Frustum::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Frustum::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Frustum 메시지 처리기입니다.

void Frustum::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void Frustum::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
