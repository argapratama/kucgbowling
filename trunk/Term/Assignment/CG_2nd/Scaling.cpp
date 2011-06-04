// Scaling.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Scaling.h"


// Scaling 대화 상자입니다.

IMPLEMENT_DYNAMIC(Scaling, CDialog)

Scaling::Scaling(CWnd* pParent /*=NULL*/)
	: CDialog(Scaling::IDD, pParent)
{
	f_scaleX = f_scaleY = f_scaleZ = 1;
}

Scaling::~Scaling()
{
}

void Scaling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_scaleX);
	DDX_Text(pDX, IDC_EDIT_Y, f_scaleY);
	DDX_Text(pDX, IDC_EDIT_Z, f_scaleZ);
}


BEGIN_MESSAGE_MAP(Scaling, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Scaling::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Scaling::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Scaling 메시지 처리기입니다.

void Scaling::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void Scaling::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
