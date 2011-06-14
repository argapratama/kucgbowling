// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifndef WMLDXCAMERA_H
#define WMLDXCAMERA_H

#include "WmlDxUtility.h"
#include "WmlRendererLibType.h"
#include "WmlCamera.h"

namespace Wml
{

class DxRenderer;

class WML_RENDERER_ITEM DxCamera : public Camera
{
    WmlDeclareRTTI;
    WmlDeclareStream;

public:
    DxCamera (DxRenderer* pkRenderer, float fWidth, float fHeight);
    
protected:
    DxCamera();

    virtual void OnResize (int iWidth, int iHeight);
    virtual void OnFrustumChange ();
    virtual void OnViewPortChange ();
    virtual void OnFrameChange ();

protected:
    float m_fWidth, m_fHeight;

    // Pointer to current renderer to update the current view and
    // projection matrices.
    DxRenderer* m_pkRenderer;

private:
    IDevicePtr m_pqDevice;
    static HRESULT ms_hResult;
};

WmlRegisterStream(DxCamera);

}

#endif
