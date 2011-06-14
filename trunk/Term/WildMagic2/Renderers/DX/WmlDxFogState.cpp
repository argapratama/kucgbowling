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

DWORD DxRenderer::ms_adwFogDensity[FogState::DF_QUANTITY] = 
{
    D3DFOG_LINEAR,  // FogState::DF_LINEAR
    D3DFOG_EXP,     // FogState::DF_EXP
    D3DFOG_EXP2,    // FogState::DF_EXPSQR
};

//----------------------------------------------------------------------------
void DxRenderer::SetFogState (FogState* pkState)
{
    if ( pkState->Enabled() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGENABLE,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGSTART,
            *((DWORD*)(&pkState->Start())));
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGEND,
            *((DWORD*)(&pkState->End())));
        WML_DX_ERROR_CHECK(SetRenderState);

        D3DCOLOR dwFogColor = D3DCOLOR_COLORVALUE(pkState->Color().r,
            pkState->Color().g,pkState->Color().b,0.0f);
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGCOLOR,dwFogColor);
        WML_DX_ERROR_CHECK(SetRenderState);

        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGDENSITY,
            *((DWORD*)(&pkState->Density())));
        WML_DX_ERROR_CHECK(SetRenderState);

        if ( pkState->AFunction() == FogState::AF_PER_PIXEL )
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGTABLEMODE,
                ms_adwFogDensity[pkState->DFunction()]);
            WML_DX_ERROR_CHECK(SetRenderState);
        }
        else
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGVERTEXMODE,
                ms_adwFogDensity[pkState->DFunction()]);    
            WML_DX_ERROR_CHECK(SetRenderState);
        }
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_FOGENABLE,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
   }   
}
//----------------------------------------------------------------------------
