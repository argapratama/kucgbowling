#pragma once


// OrthoGraphic 대화 상자입니다.

class OrthoGraphic : public CDialog
{
	DECLARE_DYNAMIC(OrthoGraphic)

public:
	OrthoGraphic(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~OrthoGraphic();

	float f_left, f_right, f_bottom, f_top, f_near, f_far;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ORTHO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
