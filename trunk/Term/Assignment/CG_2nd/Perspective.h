#pragma once


// Perspective 대화 상자입니다.

class Perspective : public CDialog
{
	DECLARE_DYNAMIC(Perspective)

public:
	Perspective(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Perspective();

	float f_fov, f_aspect, f_near, f_far;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_PERSPECTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
