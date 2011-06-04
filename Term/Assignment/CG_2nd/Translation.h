#pragma once


// Translation 대화 상자입니다.

class Translation : public CDialog
{
	DECLARE_DYNAMIC(Translation)

public:
	Translation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Translation();
	float f_transX, f_transY, f_transZ;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TRAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
