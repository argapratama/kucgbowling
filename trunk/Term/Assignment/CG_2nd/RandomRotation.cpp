// RandomRotation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CG_2nd.h"
#include "RandomRotation.h"


// RandomRotation 대화 상자입니다.

IMPLEMENT_DYNAMIC(RandomRotation, CDialog)

RandomRotation::RandomRotation(CWnd* pParent /*=NULL*/)
	: CDialog(RandomRotation::IDD, pParent)
{
	f_sLineX = f_sLineY = f_sLineZ = 0;
	f_eLineX = f_eLineY = f_eLineZ = 0;
	f_rAngle = 0;
}

RandomRotation::~RandomRotation()
{
}

void RandomRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, f_sLineX);
	DDX_Text(pDX, IDC_EDIT_Y1, f_sLineY);
	DDX_Text(pDX, IDC_EDIT_Z1, f_sLineZ);
	DDX_Text(pDX, IDC_EDIT_X2, f_eLineX);
	DDX_Text(pDX, IDC_EDIT_Y2, f_eLineY);
	DDX_Text(pDX, IDC_EDIT_Z2, f_eLineZ);
	DDX_Text(pDX, IDC_EDIT_ANGLE, f_rAngle);
}


BEGIN_MESSAGE_MAP(RandomRotation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &RandomRotation::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &RandomRotation::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// RandomRotation 메시지 처리기입니다.

void RandomRotation::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	OnOK();
}

void RandomRotation::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
