// PivotScaling.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "PivotScaling.h"


// PivotScaling 대화 상자입니다.

IMPLEMENT_DYNAMIC(PivotScaling, CDialog)

PivotScaling::PivotScaling(CWnd* pParent /*=NULL*/)
	: CDialog(PivotScaling::IDD, pParent)
{
	f_pScaleX = f_pScaleY = f_pScaleZ = 1;
	f_pPointX = f_pPointY = f_pPointZ = 0;
}

PivotScaling::~PivotScaling()
{
}

void PivotScaling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, f_pScaleX);
	DDX_Text(pDX, IDC_EDIT_Y, f_pScaleY);
	DDX_Text(pDX, IDC_EDIT_Z, f_pScaleZ);
	DDX_Text(pDX, IDC_EDIT_PIVOT_X, f_pPointX);
	DDX_Text(pDX, IDC_EDIT_PIVOT_Y, f_pPointY);
	DDX_Text(pDX, IDC_EDIT_PIVOT_Z, f_pPointZ);
}


BEGIN_MESSAGE_MAP(PivotScaling, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &PivotScaling::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &PivotScaling::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// PivotScaling 메시지 처리기입니다.

void PivotScaling::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void PivotScaling::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
