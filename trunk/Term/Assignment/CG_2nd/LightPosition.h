#pragma once


// LightPosition 대화 상자입니다.

class LightPosition : public CDialog
{
	DECLARE_DYNAMIC(LightPosition)

public:
	LightPosition(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LightPosition();

	float f_lightX, f_lightY, f_lightZ, f_isPoint;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LIGHT_POS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
