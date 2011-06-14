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

DWORD DxRenderer::ms_adwShadeMode[ShadeState::SM_QUANTITY] =
{
    D3DSHADE_FLAT,      // ShadeState::SM_FLAT
    D3DSHADE_GOURAUD,   // ShadeState::SM_SMOOTH
};

//----------------------------------------------------------------------------
void DxRenderer::SetShadeState (ShadeState* pkState)
{
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_SHADEMODE,
        ms_adwShadeMode[pkState->Shade()]);
    WML_DX_ERROR_CHECK(SetRenderState);
}
//----------------------------------------------------------------------------
