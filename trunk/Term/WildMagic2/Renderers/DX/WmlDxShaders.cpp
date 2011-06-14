// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include "WmlVertexShader.h"
#include "WmlPixelShader.h"
#include "WmlDxCamera.h"
#include "WmlDxRenderer.h"
#include "WmlGeometry.h"

using namespace Wml;

//----------------------------------------------------------------------------
void DxRenderer::CompileShader(Shader* pkShader)
{
    if ( pkShader->GetType() == Shader::PIXEL_SHADER )
    {
        CompileShader((PixelShader*)pkShader);
    }
    else if ( pkShader->GetType() == Shader::VERTEX_SHADER )
    {
        CompileShader((VertexShader*)pkShader);
    }
    else
    {
        assert( !"Bad type to compile!" );
    }
}
//----------------------------------------------------------------------------
void DxRenderer::CompileShader (PixelShader* pkShader)
{
    IDirect3DPixelShader9* pkPixelShader;
    pkShader->GetUserData(sizeof(IDirect3DPixelShader9*),&pkPixelShader);
    if ( pkPixelShader )
        return;

    // compiled program
    LPD3DXBUFFER pkCompiledShader;
    LPD3DXBUFFER pkErrors;

    ms_hResult = D3DXAssembleShader(pkShader->GetProgram(Shader::DIRECTX),
        (UINT)strlen(pkShader->GetProgram(Shader::DIRECTX)), 0, NULL, NULL,
        &pkCompiledShader, &pkErrors);
    WML_DX_ERROR_CHECK(D3DXAssembleShader);
    assert( pkCompiledShader );

    ms_hResult = m_pqDevice->CreatePixelShader( 
        (DWORD*)(pkCompiledShader->GetBufferPointer()),&pkPixelShader);
    pkShader->SetUserData(sizeof(IDirect3DPixelShader9*),&pkPixelShader);
    WML_DX_ERROR_CHECK(CreatePixelShader);

    // release buffers (if needed)
    if ( pkCompiledShader )
    {
        pkCompiledShader->Release();
    }
    if ( pkErrors )
    {
        pkErrors->Release();
    }
}
//----------------------------------------------------------------------------
void DxRenderer::CompileShader (VertexShader* pkShader)
{
    IDirect3DVertexShader9* pkVertexShader;
    pkShader->GetUserData(sizeof(IDirect3DPixelShader9*),&pkVertexShader);
    if ( pkVertexShader )
        return;

    // compile program
    LPD3DXBUFFER pkCompiledShader;
    LPD3DXBUFFER pkErrors; 

    ms_hResult = D3DXAssembleShader(pkShader->GetProgram(Shader::DIRECTX),
        (UINT)strlen(pkShader->GetProgram(Shader::DIRECTX)), NULL, NULL, NULL,
        &pkCompiledShader, &pkErrors);
    WML_DX_ERROR_CHECK(D3DXAssembleShader);
    assert( pkCompiledShader );

    ms_hResult = m_pqDevice->CreateVertexShader( 
        (DWORD*)(pkCompiledShader->GetBufferPointer()),&pkVertexShader);
    pkShader->SetUserData(sizeof(IDirect3DPixelShader9*),&pkVertexShader);
    WML_DX_ERROR_CHECK(CreatePixelShader);

    // release compiled program and error buffers (if needed)
    if ( pkCompiledShader )
    {
        pkCompiledShader->Release();
    }
    if ( pkErrors )
    {
        pkErrors->Release();
    }
}
//----------------------------------------------------------------------------
void DxRenderer::ReleaseShader(Shader* pkShader)
{
    if ( !pkShader )
        return;

    if ( pkShader->GetType() == Shader::VERTEX_SHADER )
    {
        IDirect3DVertexShader9* pkVShader;
        pkShader->GetUserData(sizeof(IDirect3DVertexShader9*),&pkVShader);
        delete pkVShader;
        pkVShader = NULL;
        pkShader->SetUserData(sizeof(IDirect3DVertexShader9*),&pkVShader);
        return;
    }

    if ( pkShader->GetType() == Shader::PIXEL_SHADER )
    {
        IDirect3DPixelShader9* pkPShader;
        pkShader->GetUserData(sizeof(IDirect3DPixelShader9*),&pkPShader);
        delete pkPShader;
        pkPShader = NULL;
        pkShader->SetUserData(sizeof(IDirect3DPixelShader9*),&pkPShader);
        return;
    }

    // Should not get here.
    assert( false );
}
//----------------------------------------------------------------------------
bool DxRenderer::SetCurrentVertexShader (VertexShader* pkShader)
{
    // if setting to NULL, then disabling shaders
    if ( pkShader )
    {
        // if the renderer can't support this shader, quit out
        if ( !SupportsShader(pkShader) )
            return false;

        // if this shader is not the current one, compile it and set it
        if ( m_pkCurVertexShader != pkShader )
        {
            IDirect3DVertexShader9* pkVShader;
            pkShader->GetUserData(sizeof(IDirect3DVertexShader9*),&pkVShader);
            if ( !pkVShader )
                CompileShader(pkShader);

            ms_hResult = m_pqDevice->SetVertexShader(pkVShader);
            WML_DX_ERROR_CHECK(SetVertexShader);
            m_pkCurVertexShader = pkShader;
        }
        return true;
    }
    else
    {
        if ( m_pkCurVertexShader != NULL )
        {
            m_pqDevice->SetVertexShader(NULL);
            WML_DX_ERROR_CHECK(SetVertexShader);
            m_pkCurVertexShader = NULL;
        }
        return false;
    }
}
//----------------------------------------------------------------------------
bool DxRenderer::SetCurrentPixelShader (PixelShader* pkShader)
{
    if ( pkShader )
    {
        if ( !SupportsShader(pkShader) )
            return false;

        if ( m_pkCurPixelShader != pkShader )
        {
            IDirect3DPixelShader9* pkPShader;
            pkShader->GetUserData(sizeof(IDirect3DPixelShader9*),&pkPShader);
            if ( !pkPShader )
                CompileShader(pkShader);

            ms_hResult = m_pqDevice->SetPixelShader(pkPShader);
            WML_DX_ERROR_CHECK(SetPixelShader);
            m_pkCurPixelShader = pkShader;
        }
        return true;
    }
    else
    {
        if ( m_pkCurPixelShader != NULL )
        {
            m_pqDevice->SetPixelShader(NULL);
            WML_DX_ERROR_CHECK(SetPixelShader);
            m_pkCurPixelShader = NULL;
        }
        return false;
    }
}
//----------------------------------------------------------------------------
inline void TransformMatrix (float* afData, int iTransform)
{
    // This is a convenience routine to transform a generic D3DX matrix
    // (passed in as afData) by some method.  This method is only called
    // by SetStateConst below.  This is just to eliminate some repeated
    // code and to eliminate a lot of case statements.

    // Also, due to the way D3D stores its matrices and the way shaders
    // expect them, everything is transposed here 

    switch( iTransform )
    {
        case SC_NORMAL:
            D3DXMatrixTranspose( (D3DXMATRIX*)afData, (D3DXMATRIX*)afData );
            break;
        case SC_INVERSE:
            D3DXMatrixInverse( (D3DXMATRIX*)afData, NULL,
                (D3DXMATRIX*)afData );
            D3DXMatrixTranspose( (D3DXMATRIX*)afData, (D3DXMATRIX*)afData );
            break;
        case SC_INVERSETRANSPOSE:
            D3DXMatrixInverse( (D3DXMATRIX*)afData, NULL,
                (D3DXMATRIX*)afData );
            break;
        case SC_TRANSPOSE:
        default:
            // do nothing
            break;
    }
}
//----------------------------------------------------------------------------
void DxRenderer::SetStateConst (float* afData, const Geometry& rkGeom,
    StateConstantType iType, int iTypeNum)
{
    // This function entails a giant case statement (from enumeration in 
    // WmlStateConstantType.h) to allow for automatic setting of renderer
    // state without intervention from (or exposure to) the user.

    // I'm not sure what to do with the 4th component for most of these
    // vectors, and so they'll be 1.0f for positions, 0.0f for vectors,
    // and 1.0f for colors.

    // This function could have been in geometry too, because most of the 
    // state that is gathered here comes from geometry.  However, logically,
    // it's a renderer call to set constants and so it's here.

    // Lots of hacky Vector?f->float* and D3DXMATRIX->float* conversions here.
    // A lot of this following code assumes that both WmlVector?f and 
    // D3DXMATRIX pointers can be cast to and from float* pointers.

    // Temporary matrices and variables
    D3DXMATRIX* pkMat;
    D3DXMATRIX* pkMat2;

    switch( iType )
    {
        // General Renderer State
        case RENDERER_MODVIEW:
            pkMat = GetWorldMatrix();
            pkMat2 = GetViewMatrix();
            D3DXMatrixMultiply( (D3DXMATRIX*)afData, pkMat, pkMat2 );
            TransformMatrix( afData, iTypeNum );
            break;
        case RENDERER_PROJ:
            pkMat = GetProjMatrix();
            memcpy(afData,pkMat,16*sizeof(float));
            TransformMatrix( afData, iTypeNum );
            break;
        case RENDERER_MODVIEWPROJ:
            pkMat = GetWorldMatrix();
            pkMat2 = GetViewMatrix();
            // worldview
            D3DXMatrixMultiply( (D3DXMATRIX*)afData, pkMat, pkMat2 );
            pkMat = GetProjMatrix();
            // worldviewproj
            D3DXMatrixMultiply( (D3DXMATRIX*)afData, (D3DXMATRIX*)afData,
                pkMat );
            TransformMatrix( afData, iTypeNum );
            break;
        case RENDERER_MOD:
            pkMat = GetWorldMatrix();
            memcpy(afData,pkMat,16*sizeof(float));
            TransformMatrix( afData, iTypeNum );
            break;

        default:
            // otherwise, fall through to generic renderer
            Renderer::SetStateConst(afData, rkGeom, iType, iTypeNum);
            break;
    }


}
//----------------------------------------------------------------------------
void DxRenderer::SetPixelShaderConst (unsigned int uiRegister,
    float* afData, int iNumOfVector4s)
{
    ms_hResult = m_pqDevice->SetPixelShaderConstantF(uiRegister, afData,
        iNumOfVector4s);
    WML_DX_ERROR_CHECK(SetPixelShaderConstantF);
}
//----------------------------------------------------------------------------
void DxRenderer::SetPixelShaderConst (ShaderConstants* pkShaderConsts,
    const Geometry& rkGeom)
{
    for (int i = 0; i < pkShaderConsts->GetNumConstants(); i++ )
    {
        // If a state constant, update it before setting it.
        // This could probably be done more intelligently than setting
        // it every time.
        ShaderConst* pkConst = pkShaderConsts->GetConstant(i);

        StateConstantType iType = pkConst->GetType();
        if ( (  iType != USER_DEFINED ) && ( iType != NUMERICAL_CONSTANT ) )
        {
            SetStateConst( pkConst->GetData(), rkGeom,
                iType, pkConst->GetTypeOption() );
        }

        ms_hResult = m_pqDevice->SetPixelShaderConstantF( 
            pkConst->GetRegister(), pkConst->GetData(), 
            pkConst->GetSize() );
        WML_DX_ERROR_CHECK(SetPixelShaderConstantF);
    }
}
//----------------------------------------------------------------------------
void DxRenderer::SetVertexShaderConst (unsigned int uiRegister,
    float* afData, int iNumOfVector4s)
{
    ms_hResult = m_pqDevice->SetVertexShaderConstantF(uiRegister, afData,
        iNumOfVector4s);
    WML_DX_ERROR_CHECK(SetVertexShaderConstantF);
}
//----------------------------------------------------------------------------
void DxRenderer::SetVertexShaderConst (ShaderConstants* pkShaderConsts,
    const Geometry& rkGeom)
{
    for (int i = 0; i < pkShaderConsts->GetNumConstants(); i++ )
    {
        // if a state constant, update it before setting it
        // this could probably be done more intelligently than setting
        // it every time.
        ShaderConst* pkConst = pkShaderConsts->GetConstant(i);

        StateConstantType iType = pkConst->GetType();
        if ( (  iType != USER_DEFINED ) && ( iType != NUMERICAL_CONSTANT ) )
        {
            SetStateConst( pkConst->GetData(), rkGeom,
                iType, pkConst->GetTypeOption() );
        }

        ms_hResult = m_pqDevice->SetVertexShaderConstantF( 
            pkConst->GetRegister(), pkConst->GetData(), 
            pkConst->GetSize() );
        WML_DX_ERROR_CHECK(SetVertexShaderConstantF);
    }
}
//----------------------------------------------------------------------------