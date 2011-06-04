// Translation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "Translation.h"


// Translation 대화 상자입니다.

IMPLEMENT_DYNAMIC(Translation, CDialog)

Translation::Translation(CWnd* pParent /*=NULL*/)
	: CDialog(Translation::IDD, pParent)
{
	f_transX = f_transY = f_transZ = 0;
}

Translation::~Translation()
{
}

void Translation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_transX);
	DDX_Text(pDX, IDC_EDIT_Y, f_transY);
	DDX_Text(pDX, IDC_EDIT_Z, f_transZ);
}


BEGIN_MESSAGE_MAP(Translation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &Translation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Translation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// Translation 메시지 처리기입니다.

void Translation::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void Translation::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
