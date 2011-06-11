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

    void SetManipulatingSprite(bool isSprite) { isManipulatingSprite_ = isSprite; }
    Virgin::Sprite& GetManipulatingSprite();

protected:
	DECLARE_MESSAGE_MAP()

private:
    void InitializeOpenGl();
    void DrawScene();

    void SetupPixelFormat(HDC hDC);

    afx_msg void OnSize(UINT nType, int cx, int cy);

private:
    CClientDC* clientDc_;   // * Todo: OnPaint의 CPaintDC로 대체해볼 것

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


