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

DWORD DxRenderer::ms_adwCullType[CullState::FT_QUANTITY] = 
{
    D3DCULL_CCW,  // CullState::FT_CCW (front CCW -> cull backface CCW in DX)
    D3DCULL_CW,   // CullState::FT_CW  (front CW -> cull backface CW in DX)
};

//----------------------------------------------------------------------------
void DxRenderer::SetCullState (CullState* pkState)
{
    if ( pkState->Enabled() )
    {
        if ( m_bReverseCullState )
        {
            if ( ms_adwCullType[pkState->CullFace()] == D3DCULL_CW )
            {
                ms_hResult = m_pqDevice->SetRenderState(D3DRS_CULLMODE,
                    D3DCULL_CCW);
                WML_DX_ERROR_CHECK(SetRenderState);
            }
            else
            {
                ms_hResult = m_pqDevice->SetRenderState(D3DRS_CULLMODE,
                    D3DCULL_CW);
                WML_DX_ERROR_CHECK(SetRenderState);
            }
        } 
        else
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_CULLMODE,
                ms_adwCullType[pkState->CullFace()]);
            WML_DX_ERROR_CHECK(SetRenderState);
        }
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
}
//----------------------------------------------------------------------------
