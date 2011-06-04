#pragma once


// RandomRotation 대화 상자입니다.

class RandomRotation : public CDialog
{
	DECLARE_DYNAMIC(RandomRotation)

public:
	RandomRotation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~RandomRotation();

	float f_sLineX, f_sLineY, f_sLineZ;
	float f_eLineX, f_eLineY, f_eLineZ;
	float f_rAngle;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RANDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
