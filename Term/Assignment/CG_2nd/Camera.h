#pragma once


// Camera 대화 상자입니다.

class Camera : public CDialog
{
	DECLARE_DYNAMIC(Camera)

public:
	Camera(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Camera();

	float f_eyeX, f_eyeY, f_eyeZ;
	float f_atX, f_atY, f_atZ;
	float f_upX, f_upY, f_upZ;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_Camera_POS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
