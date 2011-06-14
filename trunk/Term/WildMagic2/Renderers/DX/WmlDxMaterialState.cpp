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
using namespace Wml;

//----------------------------------------------------------------------------
void DxRenderer::SetMaterialState (MaterialState* pkState)
{
    D3DMATERIAL9 kD3DMaterial;

    kD3DMaterial.Emissive.r = pkState->Emissive().r;
    kD3DMaterial.Emissive.g = pkState->Emissive().g;
    kD3DMaterial.Emissive.b = pkState->Emissive().b;
    kD3DMaterial.Emissive.a = 1.0f;

    kD3DMaterial.Ambient.r = pkState->Ambient().r;
    kD3DMaterial.Ambient.g = pkState->Ambient().g;
    kD3DMaterial.Ambient.b = pkState->Ambient().b;
	kD3DMaterial.Ambient.a = pkState->Alpha();

    kD3DMaterial.Diffuse.r = pkState->Diffuse().r;
    kD3DMaterial.Diffuse.g = pkState->Diffuse().g;
    kD3DMaterial.Diffuse.b = pkState->Diffuse().b;
	kD3DMaterial.Diffuse.a = pkState->Alpha();

    kD3DMaterial.Specular.r = pkState->Specular().r;
    kD3DMaterial.Specular.g = pkState->Specular().g;
    kD3DMaterial.Specular.b = pkState->Specular().b;
 	kD3DMaterial.Specular.a = pkState->Alpha();
 
    kD3DMaterial.Power = pkState->Shininess();

    ms_hResult = m_pqDevice->SetMaterial(&kD3DMaterial);
    WML_DX_ERROR_CHECK(SetMaterial);

    // Enable per-vertex color which allows the system to include the
    // color defined for individual vertices in its lighting calculations. 
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Allow the diffuse and specular colors to come from the color
    // information specified along with the vertex.  Note that if
    // those particular colors are not defined along with the vertex
    // then the colors diffuse or specular color from the specified
    // material is used.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,
        D3DMCS_COLOR1);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE,
        D3DMCS_COLOR2);
    WML_DX_ERROR_CHECK(SetRenderState);

    // Use the ambient and emissive colors defined in the material.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,
        D3DMCS_MATERIAL);
    WML_DX_ERROR_CHECK(SetRenderState);
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE,
        D3DMCS_MATERIAL);
    WML_DX_ERROR_CHECK(SetRenderState);
}
//----------------------------------------------------------------------------
