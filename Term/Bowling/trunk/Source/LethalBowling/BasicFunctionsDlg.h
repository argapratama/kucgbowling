#pragma once
#include "afxwin.h"
#include "OpenGlPanel.h"
#include "afxcmn.h"
#include "World.h"
#include "Sprite.h"
#include "DateTime.h"


class CBasicFunctionsDlg : public CDialogEx
{
public:
	enum { IDD = IDD_BASICFUNCTIONS_DIALOG };

public:
    CBasicFunctionsDlg(CWnd* pParent = NULL);	
    void UpdateAndDraw();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
    static float ToFloat(const CWnd& wnd);
    Virgin::Sprite& GetSelectedSprite();
    void InitializeWorld();
    void InitializeSpriteMassProperties();
    void InitializeBall(Virgin::Ball& ball);
    void InitializePin(Virgin::Pin& pin);
    void InitializeControls();

    static Virgin::World& World();

protected:
	HICON m_hIcon;

private:
    OpenGlPanel openGlPanel_;

    CStatic displayPanel_;
    CButton rotateLeftButton_;
    CButton rotateRightButton_;

    bool rotateLeftButtonDown_;
    bool rotateRightButtonDown_;
    bool rotateUpButtonDown_;
    bool rotateDownButtonDown_;
    bool rollLeftButtonDown_;
    bool rollRightButtonDown_;

    bool moveUpButtonDown_;
    bool moveDownButtonDown_;
    bool moveLeftButtonDown_;
    bool moveRightButtonDown_;
    bool moveFarButtonDown_;
    bool moveNearButtonDown_;

    bool biggerButtonDown_;
    bool smallerButtonDown_;

    Virgin::DateTime firstTime_;
    Virgin::DateTime lastTime_;

public:
    virtual BOOL DestroyWindow();
    afx_msg void OnDestroy();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnBnClickedRotateLeftButton();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CButton rotateUpButton_;
    CButton rollLeftButton_;
    CButton rollRightButton_;
    CButton rotateDownButton_;
    CButton moveFarButton_;
    CButton moveNearButton_;
    CButton moveLeftButton_;
    CButton moveRightButton_;
    CButton moveUpButton_;
    CButton moveDownButton_;
    CButton biggerButton_;
    CButton smallerButton_;
    afx_msg void OnBnClickedResetSpriteButton();
    CEdit scaleXEdit_;
    CEdit scaleYEdit_;
    CEdit scaleZEdit_;
    afx_msg void OnEditChange();
    afx_msg void OnBnClickedTestButton();
    afx_msg void OnBnClickedDrawNormalCheck();
    CButton drawNormalCheck_;
    afx_msg void OnBnClickedMeshPointButton();
    afx_msg void OnBnClickedMeshWireframeButton();
    afx_msg void OnBnClickedMeshQuadButton();
    CStatic fpsStatic_;
    CSliderCtrl speedSlider_;
    afx_msg void OnNMReleasedcaptureSpeedSlider(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    CEdit cameraLocationXEdit_;
    CEdit cameraLocationYEdit_;
    CEdit cameraLocationZEdit_;
    CEdit cameraLookAtXEdit_;
    CEdit cameraLookAtYEdit_;
    CEdit cameraLookAtZEdit_;
    CEdit cameraUpXEdit_;
    CEdit cameraUpYEdit_;
    CEdit cameraUpZEdit_;
    CButton cameraAutoRotateCheck_;
    afx_msg void OnBnClickedCameraAutoRotationCheck();
    CEdit ambientREdit_;
    CEdit ambientGEdit_;
    CEdit ambientBEdit_;
    CEdit diffuseREdit_;
    CEdit diffuseGEdit_;
    CEdit diffuseBEdit_;
    CEdit specularREdit_;
    CEdit specularGEdit_;
    CEdit specularBEdit_;
    afx_msg void OnBnClickedLightCheck();
    CButton lightCheck_;
    afx_msg void OnBnClickedFlatShadingButton();
    afx_msg void OnBnClickedGouraudShadingButton();
    CButton userViewSelectedCheck_;
    afx_msg void OnBnClickedUserViewSelectedCheck();
    afx_msg void OnBnClickedResetCameraRotationButton();
    CButton drawTextureCheck_;
    afx_msg void OnBnClickedDrawTextureCheck();
    afx_msg void OnBnClickedShowCollisionInfoCheck();
    CButton showCollisionInfoCheck_;
    afx_msg void OnBnClickedTest2Button();
    afx_msg void OnBnClickedTest3Button();
    afx_msg void OnBnClickedTest4Button();
    CButton pauseCheck_;
	CButton cameraRotateRight_;
	afx_msg void OnBnClickedButtonCameraLeft();
	CButton cameraRotateLeft_;
	afx_msg void OnBnClickedButtonCameraRight();
    afx_msg void OnBnClickedTest5Button();
};
