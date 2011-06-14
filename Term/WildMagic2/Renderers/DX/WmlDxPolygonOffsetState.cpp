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
void DxRenderer::SetPolygonOffsetState (PolygonOffsetState*)
{
    // TO DO.  The render state code should be
    //     m_pqDevice->SetRenderState(D3DRS_ZBIAS,iValue);
    // where 0 <= iValue <= 16.  The larger the value, the greater the
    // depth offset.  I need to come up with a scheme that supports the
    // scale/bias parameters for OpenGL's polygon offset and the z-bias for
    // DirectX.  Perhaps iValue = max(min(int(scale/bias),16),0).
}
//----------------------------------------------------------------------------
