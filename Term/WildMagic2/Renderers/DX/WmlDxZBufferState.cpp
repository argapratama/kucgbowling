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

DWORD DxRenderer::ms_adwZBufferCompare[ZBufferState::CF_QUANTITY] = 
{
    D3DCMP_NEVER,           // ZBufferState::CF_NEVER
    D3DCMP_LESS,            // ZBufferState::CF_LESS
    D3DCMP_EQUAL,           // ZBufferState::CF_EQUAL
    D3DCMP_LESSEQUAL,       // ZBufferState::CF_LEQUAL
    D3DCMP_GREATER,         // ZBufferState::CF_GREATER
    D3DCMP_NOTEQUAL,        // ZBufferState::CF_NOTEQUAL
    D3DCMP_GREATEREQUAL,    // ZBufferState::CF_GEQUAL
    D3DCMP_ALWAYS,          // ZBufferState::CF_ALWAYS
};

//----------------------------------------------------------------------------
void DxRenderer::SetZBufferState (ZBufferState* pkState)
{
    if( pkState->Enabled() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,
            ms_adwZBufferCompare[pkState->Compare()]);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
        WML_DX_ERROR_CHECK(SetRenderState);
    }

    if ( pkState->Writeable() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
}
//----------------------------------------------------------------------------
