#pragma once

#include "RenderingContext.h"
#include "Sprite.h"
#include "Camera.h"
#include "Light.h"

class OpenGlPanel : public CWnd
{
	DECLARE_DYNAMIC(OpenGlPanel)

public:
	OpenGlPanel();
	virtual ~OpenGlPanel();

    void Create(CRect rect, CWnd* parent);

    Virgin::Sprite& Sprite();
	Virgin::Sprite& SpritePin();
	Virgin::Sprite& SpritePin2();
	Virgin::Sprite& SpritePin3();
	Virgin::Sprite& SpritePin4();
	Virgin::Sprite& SpritePin5();
	Virgin::Sprite& SpritePin6();
	Virgin::Sprite& SpritePin7();
	Virgin::Sprite& SpritePin8();
	Virgin::Sprite& SpritePin9();
	Virgin::Sprite& SpritePin10();
    Virgin::Camera& Camera();
    Virgin::Light& Light();

    Virgin::Sprite& AnotherSprite() { return anotherSprite_; }
    Virgin::Camera& TopCamera() { return topCamera_; }
    Virgin::Camera& FrontCamera() { return frontCamera_; }
    Virgin::Camera& SideCamera() { return sideCamera_; }

    void SetManipulatingSprite(bool isSprite) { isManipulatingSprite_ = isSprite; }
    Virgin::Sprite& GetManipulatingSprite() { return isManipulatingSprite_ ? sprite_ : anotherSprite_; }

protected:
	DECLARE_MESSAGE_MAP()

private:
    void InitializeOpenGl();
    void DrawScene();

    void SetupPixelFormat(HDC hDC);

    afx_msg void OnSize(UINT nType, int cx, int cy);

private:
    CClientDC* clientDc_;   // * Todo: OnPaint의 CPaintDC로 대체해볼 것
    float rotation_;
    Virgin::Sprite sprite_;
	Virgin::Sprite spritePin_;
	Virgin::Sprite spritePin2_;
	Virgin::Sprite spritePin3_;
	Virgin::Sprite spritePin4_;
	Virgin::Sprite spritePin5_;
	Virgin::Sprite spritePin6_;
	Virgin::Sprite spritePin7_;
	Virgin::Sprite spritePin8_;
	Virgin::Sprite spritePin9_;
	Virgin::Sprite spritePin10_;
    Virgin::Camera camera_;
    Virgin::Light light_;

    Virgin::Sprite anotherSprite_;
    Virgin::Camera topCamera_;
    Virgin::Camera sideCamera_;
    Virgin::Camera frontCamera_;

    OpenGl::RenderingContext* renderingContext_;
    
    bool isLButtonDown_;
    bool isRButtonDown_;
    bool isMButtonDown_;

    int width_;
    int height_;

    bool isManipulatingSprite_;

public:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnMouseLeave();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
};


