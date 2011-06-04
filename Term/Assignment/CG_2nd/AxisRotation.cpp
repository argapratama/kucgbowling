// AxisRotation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "AxisRotation.h"


// AxisRotation 대화 상자입니다.

IMPLEMENT_DYNAMIC(AxisRotation, CDialog)

AxisRotation::AxisRotation(CWnd* pParent /*=NULL*/)
	: CDialog(AxisRotation::IDD, pParent)
{
	f_aRotateX = f_aRotateY = f_aRotateZ = 0;
}

AxisRotation::~AxisRotation()
{
}

void AxisRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_aRotateX);
	DDX_Text(pDX, IDC_EDIT_Y, f_aRotateY);
	DDX_Text(pDX, IDC_EDIT_Z, f_aRotateZ);
}


BEGIN_MESSAGE_MAP(AxisRotation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &AxisRotation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &AxisRotation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AxisRotation 메시지 처리기입니다.

void AxisRotation::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void AxisRotation::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
