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
void DxRenderer::SetDitherState (DitherState* pkState)
{
    if ( pkState->Enabled() )
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_DITHERENABLE,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_DITHERENABLE,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
}
//----------------------------------------------------------------------------
