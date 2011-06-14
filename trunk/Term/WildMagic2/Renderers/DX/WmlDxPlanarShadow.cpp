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
#include "WmlDirectionalLight.h"
#include "WmlPointLight.h"
#include "WmlPlanarShadow.h"
using namespace Wml;

//----------------------------------------------------------------------------
void DxRenderer::Draw (const PlanarShadow& rkPShadow)
{
    TriMeshPtr spkPlane = rkPShadow.GetPlane();
    NodePtr spkCaster = rkPShadow.GetCaster();

    if ( !m_bCapPlanarShadow )
    {
        // The effect is not supported.  Draw normally without the shadow.
        // The OnDraw calls are necessary to handle culling and camera plane
        // state.
        spkPlane->OnDraw(*this);
        spkCaster->OnDraw(*this);
        return;
    }

    // enable depth buffering
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);

    // draw the caster
    Renderer::Draw(spkCaster);

    // Enable the stencil buffer so that the shadow can be clipped by the
    // plane.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPShadow.GetStencilValue());
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

    // draw the plane
    SetState(spkPlane->GetRenderStateArray());
    Draw(*spkPlane);

    // Compute the current plane equation (rotate the normal and xform the
    // point).
    Vector3f kCurrNormal = spkPlane->WorldRotate()*rkPShadow.GetPlaneNormal();
    Vector3f kCurrPoint = spkPlane->WorldTranslate() + spkPlane->WorldScale()
        * (spkPlane->WorldRotate()*rkPShadow.GetPointOnPlane());
    D3DXVECTOR3 kPlanePoint(kCurrPoint.X(),kCurrPoint.Y(),kCurrPoint.Z());
    D3DXVECTOR3 kPlaneNormal(kCurrNormal.X(),kCurrNormal.Y(),kCurrNormal.Z());
    D3DXPLANE kPlane;
    D3DXPlaneFromPointNormal(&kPlane,&kPlanePoint,&kPlaneNormal);

    // Conservative test to see if a shadow should be cast -- this can cause
    // incorrect results if the caster is large and intersects the plane, but
    // ordinarily we are not trying to cast shadows in such situations.
    Vector3f& rkCenter = spkCaster->WorldBound().Center();
    if ( kCurrNormal.Dot(rkCenter) - kCurrNormal.Dot(kCurrPoint) < 0.0f )
    {
        // caster is on far side of plane
        return;
    }

    // Create the light vector based on the light type.
    Light* pkLight = rkPShadow.GetLight();
    D3DXVECTOR4 kLightPosition;
    Vector3f kLightVec;
    switch ( pkLight->GetType() )
    {
    default:
    case Light::LT_AMBIENT:
        kLightPosition.x = 0.0f;
        kLightPosition.y = 0.0f;
        kLightPosition.z = 0.0f;
        kLightPosition.w = 1.0f;
        break;
    case Light::LT_DIRECTIONAL:
        kLightVec = -WmlDynamicCast(DirectionalLight,pkLight)->Direction();
        kLightPosition.x = kLightVec.X();
        kLightPosition.y = kLightVec.Y();
        kLightPosition.z = kLightVec.Z();
        kLightPosition.w = 0.0f;
        break;
    case Light::LT_POINT:
    case Light::LT_SPOT:
        kLightVec = WmlDynamicCast(PointLight,pkLight)->Location();
        kLightPosition.x = kLightVec.X();
        kLightPosition.y = kLightVec.Y();
        kLightPosition.z = kLightVec.Z();
        kLightPosition.w = 1.0f;
        break;
    }

    // save the modelview transform
    D3DXMATRIX kOldModelViewMat;
    ms_hResult = m_pqDevice->GetTransform(D3DTS_VIEW,&kOldModelViewMat); 
    WML_DX_ERROR_CHECK(GetTransform);

    // compute the projection matrix for the light source
    D3DXMATRIX kShadowMat;
    D3DXMatrixShadow(&kShadowMat,&kLightPosition,&kPlane);

    D3DXMATRIX kNewModelViewMat;
    D3DXMatrixMultiply(&kNewModelViewMat,&kShadowMat,&kOldModelViewMat);
    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kNewModelViewMat); 
    WML_DX_ERROR_CHECK(SetTransform);

    // Reset the state, and and disable z-buffering
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Disable lighting and use flat shading.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Setup the first and only texture stage to pass the
    // the output semi-transparent black as the output which gets
    // blended during the alpha blending stage.
    D3DCOLOR kShadowBlendColor = D3DCOLOR_COLORVALUE(0.0,0.0,0.0,0.5);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_TEXTUREFACTOR,
        kShadowBlendColor);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_COLOROP,
        D3DTOP_SELECTARG1);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,
        D3DTOP_SELECTARG1);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_COLORARG1,
        D3DTA_TFACTOR);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,
        D3DTA_TFACTOR);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(1,D3DTSS_COLOROP,
        D3DTOP_DISABLE);
    WML_DX_ERROR_CHECK(SetTextureStageState);

    // Attenuate the currently stored color by using blending.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_DESTBLEND,
        D3DBLEND_INVSRCALPHA);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Only draw where the plane has been drawn, and don't allow the object
    // to alter render state.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILREF,
        rkPShadow.GetStencilValue());
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
        D3DSTENCILOP_ZERO);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILWRITEMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Draw the caster again.  TO DO.  Might have to disable culling to allow
    // out-of-view objects to cast shadows.
    m_bOverrideState = true;
    Renderer::Draw(spkCaster);
    m_bOverrideState = false;

    // disable stencil buffer
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
    WML_DX_ERROR_CHECK(SetRenderState);

    // restore the modelview transform
    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kOldModelViewMat); 
    WML_DX_ERROR_CHECK(SetTransform);
}
//----------------------------------------------------------------------------
