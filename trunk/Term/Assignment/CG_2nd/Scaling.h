#pragma once


// Scaling 대화 상자입니다.

class Scaling : public CDialog
{
	DECLARE_DYNAMIC(Scaling)

public:
	Scaling(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Scaling();
	float f_scaleX, f_scaleY, f_scaleZ;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
