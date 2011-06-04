#pragma once


// LightColor 대화 상자입니다.

class LightColor : public CDialog
{
	DECLARE_DYNAMIC(LightColor)

public:
	LightColor(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LightColor();

	float f_ambientR, f_ambientG, f_ambientB, f_ambientA;
	float f_diffuseR, f_diffuseG, f_diffuseB, f_diffuseA;
	float f_specularR, f_specularG, f_specularB, f_specularA;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LIGHT_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
