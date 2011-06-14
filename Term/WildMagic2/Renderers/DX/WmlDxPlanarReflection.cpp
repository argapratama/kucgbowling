// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include "WmlDxRenderer.h"
#include "WmlPlanarReflection.h"
using namespace Wml;

//----------------------------------------------------------------------------
void DxRenderer::Draw (const PlanarReflection& rkPReflection)
{
    TriMeshPtr spkPlane = rkPReflection.GetPlane();
    NodePtr spkCaster = rkPReflection.GetCaster();

    if ( !m_bCapPlanarReflection )
    {
        // The effect is not supported.  Draw normally without the mirror.
        // The OnDraw calls are necessary to handle culling and camera plane
        // state.
        spkPlane->OnDraw(*this);
        spkCaster->OnDraw(*this);
        return;
    }

    if ( m_bDrawingReflected )
    {
        // Some other object is currently doing a planar reflection.  Do not
        // allow the recursion and just draw normally.
        Renderer::Draw(spkCaster);
        SetState(spkPlane->GetRenderStateArray());
        Draw(*spkPlane);
        return;
    }

    // TO DO:  Support for multiple mirrors could be added here by iterating
    // over the section delimited by START PER-MIRROR and END PER-MIRROR.
    // None of the DirectX code needs to change, just the mirror-plane data.

    // START PER-MIRROR

    // Step 1 setup and render.
    // Render the mirror plane into the stencil buffer.  All visible
    // mirror pixels will have the stencil value of the mirror.
    // Make sure that no pixels are written to the depth buffer or color
    // buffer, but use depth buffer testing so that the stencil
    // will not be written where the plane is behind something already
    // in the depth buffer.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPReflection.GetStencilValue());
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILZFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILPASS,
        D3DSTENCILOP_REPLACE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILWRITEMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0);
    WML_DX_ERROR_CHECK(SetRenderState);
    Draw(*spkPlane);


    // Step 2 setup and render.
    // Render the mirror plane again by only processing pixels where
    // the stencil buffer contains the reference value.  This time
    // there is no changes to the stencil buffer and the depth buffer value
    // is reset to the far view clipping plane (this is done by setting the
    // range of depth values in the viewport volume to be [1,1].  Since the
    // mirror plane cannot also be semi-transparent, then there we do not
    // care what is behind the mirror plane in the depth buffer.  We need
    // to move the depth buffer values back where the mirror plane will
    // be rendered so that when the reflected caster is rendered
    // it can be depth buffered correctly (note that the rendering
    // of the reflected caster will cause depth value to be written
    // which will appear to be behind the mirror plane).  Enable writes
    // to the color buffer.  Later when we want to render the reflecting
    // plane and have it blend with the background (which should contain
    // the reflected caster), we want to use the same blending function
    // so that the pixels where the reflected caster was not rendered
    // will contain the reflecting plane and in that case, the blending
    // result will have the reflecting plane appear to be opaque when
    // in reality it was blended with blending coefficients adding to one.
    SetState(spkPlane->GetRenderStateArray());
    D3DVIEWPORT9 kViewport;
    ms_hResult = m_pqDevice->GetViewport(&kViewport);
    WML_DX_ERROR_CHECK(GetViewport);
    kViewport.MinZ = 1.0;
    kViewport.MaxZ = 1.0;
    ms_hResult = m_pqDevice->SetViewport(&kViewport);
    WML_DX_ERROR_CHECK(SetViewport);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,
        D3DCMP_EQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPReflection.GetStencilValue());
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILZFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILPASS,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILWRITEMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
        D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|
        D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
    WML_DX_ERROR_CHECK(SetRenderState);
    Draw(*spkPlane);


    // Step 2 cleanup.
    // Restore the viewport and restore the depth testing function.
    kViewport.MinZ = 0.0;
    kViewport.MaxZ = 1.0;
    ms_hResult = m_pqDevice->SetViewport(&kViewport);
    WML_DX_ERROR_CHECK(SetViewport);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);


    // Step 3 setup.
    // We are about to render the reflected caster.  For that, we
    // will need to compute the reflection viewing matrix.
    Vector3f kCurrNormal = spkPlane->WorldRotate()*
        rkPReflection.GetPlaneNormal();
    Vector3f kCurrPoint = spkPlane->WorldTranslate()+spkPlane->WorldScale()*
      (spkPlane->WorldRotate()*rkPReflection.GetPointOnPlane());
    D3DXVECTOR3 kPlanePoint(kCurrPoint.X(),kCurrPoint.Y(),kCurrPoint.Z());
    D3DXVECTOR3 kPlaneNormal(kCurrNormal.X(),kCurrNormal.Y(),kCurrNormal.Z());
    D3DXPLANE kPlane;
    D3DXPlaneFromPointNormal(&kPlane,&kPlanePoint,&kPlaneNormal);

    // Save the modelview transform before replacing it with
    // the viewing transform which will handle the reflection.
    D3DXMATRIX kOldModelViewMat;
    ms_hResult = m_pqDevice->GetTransform(D3DTS_VIEW,&kOldModelViewMat); 
    WML_DX_ERROR_CHECK(GetTransform);
    D3DXMATRIX kReflectMat;
    D3DXMatrixReflect(&kReflectMat,&kPlane);
    D3DXMATRIX kNewModelViewMat;
    D3DXMatrixMultiply(&kNewModelViewMat,&kReflectMat,&kOldModelViewMat);
    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kNewModelViewMat); 
    WML_DX_ERROR_CHECK(SetTransform);

    // Setup a clip plane so that only objects above the mirror plane
    // get reflected.
    DWORD dwClipPlanesEnabled;
    ms_hResult = m_pqDevice->GetRenderState(D3DRS_CLIPPLANEENABLE,
        &dwClipPlanesEnabled);
    WML_DX_ERROR_CHECK(GetRenderState);
    DWORD dwClipPlaneIndex = 0;
    ms_hResult = m_pqDevice->SetClipPlane(dwClipPlaneIndex,kPlane);
    WML_DX_ERROR_CHECK(SetClipPlane);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_CLIPPLANEENABLE,
        (1 << dwClipPlaneIndex) | dwClipPlanesEnabled);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Reverse the cull direction.  Allow for models that are not necessarily
    // set up with front or back face culling.
    m_bReverseCullState = true;

    // We do not support mirrors reflecting mirrors.  They just appear as the
    // base color in a reflection.
    m_bDrawingReflected = true;

    // Step 3 render.
    // Render the reflected caster.  Only render where the stencil buffer
    // contains the reference value.  Enable depth testing.  This time
    // allow writes to the color buffer.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,
        D3DCMP_EQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPReflection.GetStencilValue());
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILZFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILPASS,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILWRITEMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
        D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|
        D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
    WML_DX_ERROR_CHECK(SetRenderState);
    Renderer::Draw(spkCaster);

    // Step 3 cleanup.
    // Restore state.
    m_bDrawingReflected = false;
    m_bReverseCullState = false;

    // Disable the clip plane, and restore the modelview matrix.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_CLIPPLANEENABLE,
        dwClipPlanesEnabled);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kOldModelViewMat); 
    WML_DX_ERROR_CHECK(SetTransform);


    // Step 4 setup.
    // We are about to render the reflecting plane again.  Reset to
    // the render state for the reflecting plane.  We want to blend
    // the reflecting plane with what is already in the color buffer
    // where the reflecting plane will be rendered, particularly
    // either the image of the reflected caster or the reflecting
    // plane.  All we want to change about the rendering of the
    // reflecting plane at this stage is to force the alpha channel
    // to always be the reflectance value for the reflecting plane.
    // We use the first and only texture stage for that.  Set D3DTSS_ALPHAOP
    // for stage 0 to D3DTOP_SELECTARG2 since the default is to set
    // it to D3DTOP_SELECTARG1.
    SetState(spkPlane->GetRenderStateArray());
    D3DCOLOR kShadowBlendColor = D3DCOLOR_COLORVALUE(0.0,0.0,0.0,
        rkPReflection.GetReflectance());
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_TEXTUREFACTOR,
        kShadowBlendColor);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_COLOROP,
        D3DTOP_SELECTARG1);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,
        D3DTOP_SELECTARG2);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_COLORARG1,
        D3DTA_TEXTURE);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,
        D3DTA_TFACTOR);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(1,D3DTSS_COLOROP,
        D3DTOP_DISABLE);
    WML_DX_ERROR_CHECK(SetTextureStageState);


    
    // Step 4 render after more setup.
    // Render the reflecting plane wherever the stencil buffer is set
    // to the reference value.  This time clear the stencil buffer
    // reference value where it is set.  Perform the normal depth
    // buffer testing and writes.  Allow the color buffer to be
    // written to, but this time blend the relecting plane with
    // the values in the color buffer based on the reflectance value.
    // Note that where the stencil buffer is set, the color buffer
    // has either color values from the reflecting plane or the
    // reflected caster.  Blending will use src=1-alpha (reflecting plane)
    // and dest=alpha background (reflecting plane or reflected caster).
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,
        D3DCMP_EQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPReflection.GetStencilValue());
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILZFAIL,
        D3DSTENCILOP_KEEP);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILPASS,
        D3DSTENCILOP_INVERT);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILWRITEMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
        D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|
        D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_SRCBLEND,
        D3DBLEND_INVSRCALPHA);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_DESTBLEND,
        D3DBLEND_SRCALPHA);
    WML_DX_ERROR_CHECK(SetRenderState);
    Draw(*spkPlane);


    // Step 4 cleanup.
    // Disable the stencil buffer and blending.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
    WML_DX_ERROR_CHECK(SetRenderState);


    // Step 5.
    // Render the caster as normal.
    Renderer::Draw(spkCaster);
}
//----------------------------------------------------------------------------
