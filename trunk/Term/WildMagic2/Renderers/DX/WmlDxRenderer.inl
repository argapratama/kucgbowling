// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

//----------------------------------------------------------------------------
inline IDevice* DxRenderer::GetDevice ()
{
    return m_pqDevice;
}
//----------------------------------------------------------------------------
inline D3DXMATRIX* DxRenderer::GetWorldMatrix ()
{
    return &m_kCurrentWorldMatrix;
}
//----------------------------------------------------------------------------
inline D3DXMATRIX* DxRenderer::GetProjMatrix ()
{
    return &m_kCurrentProjMatrix;
}
//----------------------------------------------------------------------------
inline D3DXMATRIX* DxRenderer::GetViewMatrix ()
{
    return &m_kCurrentViewMatrix;
}
//----------------------------------------------------------------------------
inline bool DxRenderer::SupportsShader (const VertexShader* pkShader) const
{
    return ( pkShader && (m_iCapVertShaderVersion >= 
        pkShader->GetVersion(Shader::DIRECTX)) );
}
//----------------------------------------------------------------------------
inline bool DxRenderer::SupportsShader (const PixelShader* pkShader) const
{
    return ( pkShader && (m_iCapPixShaderVersion >=
        pkShader->GetVersion(Shader::DIRECTX)) );
}
//----------------------------------------------------------------------------