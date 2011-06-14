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

DWORD DxRenderer::ms_adwAlphaSrcBlend[AlphaState::SBF_QUANTITY] =
{
    D3DBLEND_ZERO,          // AlphaState::SBF_ZERO
    D3DBLEND_ONE,           // AlphaState::SBF_ONE
    D3DBLEND_DESTCOLOR,     // AlphaState::SBF_DST_COLOR
    D3DBLEND_INVDESTCOLOR,  // AlphaState::SBF_ONE_MINUS_DST_COLOR
    D3DBLEND_SRCALPHA,      // AlphaState::SBF_SRC_ALPHA
    D3DBLEND_INVSRCALPHA,   // AlphaState::SBF_ONE_MINUS_SRC_ALPHA
    D3DBLEND_DESTALPHA,     // AlphaState::SBF_DST_ALPHA
    D3DBLEND_INVDESTALPHA,  // AlphaState::SBF_ONE_MINUS_DST_ALPHA
    D3DBLEND_SRCALPHASAT,   // AlphaState::SBF_SRC_ALPHA_SATURATE
};

DWORD DxRenderer::ms_adwAlphaDstBlend[AlphaState::DBF_QUANTITY] =
{
    D3DBLEND_ZERO,          // AlphaState::DBF_ZERO
    D3DBLEND_ONE,           // AlphaState::DBF_ONE
    D3DBLEND_SRCCOLOR,      // AlphaState::DBF_SRC_COLOR
    D3DBLEND_INVSRCCOLOR,   // AlphaState::DBF_ONE_MINUS_SRC_COLOR
    D3DBLEND_SRCALPHA,      // AlphaState::DBF_SRC_ALPHA
    D3DBLEND_INVSRCALPHA,   // AlphaState::DBF_ONE_MINUS_SRC_ALPHA
    D3DBLEND_DESTALPHA,     // AlphaState::DBF_DST_ALPHA
    D3DBLEND_INVDESTALPHA,  // AlphaState::DBF_ONE_MINUS_DST_ALPHA
};

DWORD DxRenderer::ms_adwAlphaTest[AlphaState::TF_QUANTITY] =
{
    D3DCMP_NEVER,           // AlphaState::TF_NEVER
    D3DCMP_LESS,            // AlphaState::TF_LESS
    D3DCMP_EQUAL,           // AlphaState::TF_EQUAL
    D3DCMP_LESSEQUAL,       // AlphaState::TF_LEQUAL
    D3DCMP_GREATER,         // AlphaState::TF_GREATER
    D3DCMP_NOTEQUAL,        // AlphaState::TF_NOTEQUAL
    D3DCMP_GREATEREQUAL,    // AlphaState::TF_GEQUAL
    D3DCMP_ALWAYS,          // AlphaState::TF_ALWAYS
};

//----------------------------------------------------------------------------
void DxRenderer::SetAlphaState (AlphaState* pkState)
{
    if ( pkState->BlendEnabled() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_SRCBLEND,
            ms_adwAlphaSrcBlend[pkState->SrcBlend()]);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_DESTBLEND,
            ms_adwAlphaDstBlend[pkState->DstBlend()]);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }

    if ( pkState->TestEnabled() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHAFUNC,
            ms_adwAlphaTest[pkState->Test()]);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHAREF,
            (DWORD)(255.0f*pkState->Reference()));
        WML_DX_ERROR_CHECK(SetRenderState);
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
}
//----------------------------------------------------------------------------
