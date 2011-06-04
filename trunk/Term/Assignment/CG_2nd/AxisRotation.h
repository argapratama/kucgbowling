#pragma once


// AxisRotation 대화 상자입니다.

class AxisRotation : public CDialog
{
	DECLARE_DYNAMIC(AxisRotation)

public:
	AxisRotation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AxisRotation();

	float f_aRotateX, f_aRotateY, f_aRotateZ;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_AXIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
