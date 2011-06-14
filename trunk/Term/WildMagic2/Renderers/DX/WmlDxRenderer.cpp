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
#include "WmlBumpMap.h"
#include "WmlTriMesh.h"
#include "WmlPolyline.h"
#include "WmlPolypoint.h"
#include "WmlParticles.h"
#include "WmlScreenPolygon.h"
using namespace Wml;
using namespace std;

HRESULT DxRenderer::ms_hResult = NULL;

WmlImplementRTTI(DxRenderer,Renderer);

//----------------------------------------------------------------------------
DxRenderer::DxRenderer (BOOL bFullScreen, HWND hDisplayWnd, int iWidth,
    int iHeight)
    :
    Renderer(iWidth,iHeight),
    m_bCursorVisible(true),
    m_bDeviceLost(false)
{    
    m_pqMain = Direct3DCreate9(D3D_SDK_VERSION);
    WML_DX_ERROR_CHECK_NULL(m_pqMain,Direct3DCreate9);

    D3DDISPLAYMODE kMode;
    ms_hResult = m_pqMain->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&kMode);
    WML_DX_ERROR_CHECK(GetAdapterDisplayMode);

    m_kPresent.BackBufferWidth = iWidth;
    m_kPresent.BackBufferHeight = iHeight;
    m_kPresent.BackBufferFormat = kMode.Format;
    m_kPresent.BackBufferCount = 1;
    m_kPresent.MultiSampleType = D3DMULTISAMPLE_NONE;
    m_kPresent.MultiSampleQuality = 0;
    m_kPresent.SwapEffect = D3DSWAPEFFECT_FLIP; 
    m_kPresent.hDeviceWindow = hDisplayWnd;
    m_kPresent.Windowed = !bFullScreen;
    m_kPresent.EnableAutoDepthStencil = TRUE;
    m_kPresent.AutoDepthStencilFormat = D3DFMT_D24S8;
    m_kPresent.Flags = 0;
    m_kPresent.FullScreen_RefreshRateInHz =
        ( bFullScreen? D3DPRESENT_RATE_DEFAULT : 0 );
    m_kPresent.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    ms_hResult = m_pqMain->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
        hDisplayWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_kPresent,
        &m_pqDevice);
    WML_DX_ERROR_CHECK(CreateDevice);

    // shader setup (disable shaders to start)
    m_pkCurPixelShader = NULL;
    m_pkCurVertexShader = NULL;

    // font handling
    RendererFont kDefaultFont;
    DWORD dwWeight = ( kDefaultFont.Bold() ? FW_BOLD : FW_REGULAR );
    HFONT hFont = CreateFont(kDefaultFont.Size(),0,0,dwWeight,
        (DWORD)kDefaultFont.Italic(),FALSE,FALSE,FALSE,DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
        VARIABLE_PITCH,kDefaultFont.Face().c_str());
    WML_DX_ERROR_CHECK_NULL(hFont,CreateFont);
    ms_hResult = D3DXCreateFont(m_pqDevice,hFont,&m_pqDefaultFont);
    WML_DX_ERROR_CHECK(D3DXCreateFont);

    EstablishCapabilities();
    InitializeState();
}
//----------------------------------------------------------------------------
DxRenderer::~DxRenderer ()
{
    int i;
    for (i = 0; i < m_iMaxTextureUnits; i++)
        m_pqDevice->SetTexture(i,NULL);

    // release all texture surfaces
    for (i = 0; i < (int)m_kDxTextures.size(); i++) 
    {
        ITexture* pqTexture = m_kDxTextures.back();
        pqTexture->Release();
        m_kDxTextures.pop_back();
    }

    // font handling
    m_pqDefaultFont.Release();
    map<unsigned int,IFontPtr>::iterator pkIter;
    for (pkIter = m_kFontMap.begin(); pkIter != m_kFontMap.end(); pkIter++)
    {
        IFontPtr pqFont = pkIter->second;
        pqFont.Release();
    }

    if ( !m_bCursorVisible )
        ShowCursor(true);
}
//----------------------------------------------------------------------------
inline bool TestCapBits (const DWORD dwCap, const DWORD dwCapMask)
{
    return dwCapMask == ( dwCap & dwCapMask );
}
//----------------------------------------------------------------------------
void DxRenderer::EstablishCapabilities ()
{
    // Query the device for its capabilities.
    D3DCAPS9 kDeviceCaps;
    ms_hResult = m_pqMain->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
        &kDeviceCaps);
    WML_DX_ERROR_CHECK(GetDeviceCaps);

    // Initialize the maximum number of texture units.
    // Use the maximum number of textures that can be placed
    // into the texture units simultaneously.  This number is
    // more relevant to how WM uses it than is the maximum
    // number of texture units.
    m_iMaxTextureUnits = kDeviceCaps.MaxSimultaneousTextures;

    // Multitexturing is supported if there is more than a
    // single texture unit available for textures.
    m_bCapMultitexture = ( m_iMaxTextureUnits > 1 );

    // When specular highlighting is enabled, DirectX always adds the
    // the specular color to the base color after the texture cascade
    // but before alpha blending.
    m_bCapSpecularAfterTexture = true;

    // Does the device support texture clamping to border?
    m_bCapTextureClampToBorder =
        TestCapBits(kDeviceCaps.TextureAddressCaps,D3DPTADDRESSCAPS_BORDER);

    // Does the device support texture combine?
    // In DirectX, this corresponds to the support for texture operations.
    // True if the device supports any texture operation.
    // If any are supported, then test for specific combine operations.
    if ( 0 != kDeviceCaps.TextureOpCaps )
    {
        m_bCapTextureApplyCombine = true;

        m_bCapTextureApplyCombineDot3 =
            TestCapBits(kDeviceCaps.TextureOpCaps,D3DTEXOPCAPS_DOTPRODUCT3);

        m_bCapTextureApplyAdd =
            TestCapBits(kDeviceCaps.TextureOpCaps,D3DTEXOPCAPS_ADD);
    }
    else
    {
        m_bCapTextureApplyCombine = false;
        m_bCapTextureApplyCombineDot3 = false;
        m_bCapTextureApplyAdd = false;
    }

    // Does the device support DOT3 bump mapping?
    m_bCapDot3BumpMapping =
        m_bCapTextureApplyCombineDot3 &&
        m_bCapMultitexture;

    // The fact that at least one stencil bit is available is given
    // by the fact that we got this far which means we have at least
    // 8 bit available as requested in the CreateDevice call.
    // Make note that all stencil operations used are supported.
    const bool bCapStencilOpsUsed = TestCapBits(kDeviceCaps.StencilCaps,
        D3DSTENCILOP_KEEP|D3DSTENCILOP_REPLACE);

    // Test for other capabilities.
    const bool bCapBlend = 
        TestCapBits(kDeviceCaps.PrimitiveMiscCaps,D3DPMISCCAPS_BLENDOP);
    const bool bCapColorWriteMask =
        TestCapBits(kDeviceCaps.PrimitiveMiscCaps,
            D3DPMISCCAPS_COLORWRITEENABLE);

    // Multiple levels of vertex shader support.  Find the highest
    // level supported (if any).
    if ( kDeviceCaps.VertexShaderVersion >= D3DVS_VERSION(2,0) )
    {
        // Vertex Shaders version 2.X are a superset of version 2.0.
        // It contains many of the same restrictions syntatically, but
        // allows for more instructions and more registers.  However, the
        // capabilities that the DxRenderer checks for are not as fine
        // grained as to be able to check exact number of temporary
        // registers used and instruction limits to test whether a program
        // will run or not.  Thus, if a card can run 2.0 and the user really
        // wants to run some arbitrary 2.x program, they can do so
        // AT THEIR OWN RISK.

        //m_iCapVertShaderVersion = Shader::VS_2_0;
        m_iCapVertShaderVersion = Shader::VS_2_X;
    }
    else if ( kDeviceCaps.VertexShaderVersion >= D3DVS_VERSION(1,1) )
    {
        m_iCapVertShaderVersion = Shader::VS_1_1;
    }
    else
    {
        m_iCapVertShaderVersion = Shader::UNSUPPORTED;
    }

    // Multiple levels of pixel shader support.  Find the highest
    // level supported (if any).;
    if ( kDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(2,0) )
    {
        // See note above about VS_2_X versions.  The same thing
        // applies here for PS_2_X vs. PS_2_0.

        //m_iCapPixShaderVersion = Shader::PS_2_0;
        m_iCapPixShaderVersion = Shader::PS_2_X;
    }
    else if ( kDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(1,3) )
    {
        m_iCapPixShaderVersion = Shader::PS_1_3;
    }
    else if ( kDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(1,2) )
    {
        m_iCapPixShaderVersion = Shader::PS_1_2;
    }
    else if ( kDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(1,1) )
    {
        m_iCapPixShaderVersion = Shader::PS_1_1;
    }
    else
    {
        m_iCapPixShaderVersion = Shader::UNSUPPORTED;
    }

    // Planar shadows are supported if the device supports:
    //  . at least one texture stage
    //  . at least one stencil buffer bit (already known)
    //  . all of the necessary stencil buffer operations
    //  . alpha blending is supported
    m_bCapPlanarShadow =
        ( m_iMaxTextureUnits > 0 ) &&
        bCapStencilOpsUsed &&
        bCapBlend;

    // Planar reflections are supported if the device supports:
    //  . at least one texture stage
    //  . at least one stencil buffer bit (already known)
    //  . all of the necessary stencil buffer operations
    //  . one user defined clip plane
    //  . writes to the color buffer can be enabled/disabled
    //  . alpha blending is supported
    m_bCapPlanarReflection =
        ( m_iMaxTextureUnits > 0 ) &&
        bCapStencilOpsUsed &&
        bCapColorWriteMask &&
#if 0
        // NOTE: DX 8.1 must have a problem on nVidia GeForce cards
        // because it reports there are no user defined clip planes when
        // in fact there are.)
        ( kDeviceCaps.MaxUserClipPlanes > 0 ) &&
#endif
        bCapBlend;
}
//----------------------------------------------------------------------------
bool DxRenderer::LoadFont (const RendererFont& rkFont)
{
    DWORD dwWeight = ( rkFont.Bold() ? FW_BOLD : FW_REGULAR );

    HFONT hFont = CreateFont(rkFont.Size(),0,0,0,dwWeight,
        (bool)rkFont.Italic(),FALSE,FALSE,DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
        VARIABLE_PITCH,rkFont.Face().c_str());
    WML_DX_ERROR_CHECK_NULL(hFont,CreateFont);

    IFontPtr pqFont;
    ms_hResult = D3DXCreateFont(m_pqDevice,hFont,&pqFont);
    WML_DX_ERROR_CHECK(D3DXCreateFont);
    m_kFontMap[rkFont.GetID()] = pqFont;
    return true;
}
//----------------------------------------------------------------------------
void DxRenderer::UnloadFont (const RendererFont& rkFont)
{
    map<unsigned int,IFontPtr>::iterator pkIter =
        m_kFontMap.find(rkFont.GetID());

    if ( pkIter == m_kFontMap.end() )
        return;
    IFontPtr pqFont = pkIter->second;
    pqFont.Release();
    m_kFontMap.erase(pkIter);
}
//----------------------------------------------------------------------------
void DxRenderer::Resize (int, int)
{
}
//----------------------------------------------------------------------------
bool DxRenderer::BeginScene ()
{
    ms_hResult = m_pqDevice->TestCooperativeLevel();
    
    switch ( ms_hResult )
    {
    case D3DERR_DEVICELOST:
        if ( !m_bDeviceLost )
        {
            m_bDeviceLost = true;
            OnDeviceLost();
        }
        return false;
    case D3DERR_DEVICENOTRESET:
        ResetDevice();
        m_bDeviceLost = false;
        break;
    }

    ms_hResult = m_pqDevice->BeginScene();
    WML_DX_ERROR_CHECK(BeginScene);

    return true;
}
//----------------------------------------------------------------------------
void DxRenderer::EndScene ()
{
    ms_hResult = m_pqDevice->EndScene();
    WML_DX_ERROR_CHECK(EndScene);
}
//----------------------------------------------------------------------------
void DxRenderer::OnDeviceLost ()
{
    m_pqDefaultFont->OnLostDevice();
}
//----------------------------------------------------------------------------
void DxRenderer::ResetDevice ()
{
    ms_hResult = m_pqDevice->Reset(&m_kPresent);
    WML_DX_ERROR_CHECK(Reset);
    m_pqDefaultFont->OnResetDevice();
    InitializeState();
    m_spkCamera->Update();
}
//----------------------------------------------------------------------------
void DxRenderer::ShowCursor (bool bShow)
{
    if ( bShow != m_bCursorVisible )
    {
        m_bCursorVisible = bShow;
        ::ShowCursor((BOOL)bShow);
    }
}
//----------------------------------------------------------------------------
void DxRenderer::ToggleFullScreen (int& riNewWidth, int& riNewHeight)
{
    m_kPresent.Windowed = !m_kPresent.Windowed;

    if ( m_kPresent.Windowed )
    {
        m_kPresent.FullScreen_RefreshRateInHz = 0;
    }
    else
    {
        GetWindowRect(m_kPresent.hDeviceWindow,&m_rcWindow);
        m_kPresent.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }

    OnDeviceLost();
    ResetDevice();  

    if ( m_kPresent.Windowed )
    {
        SetWindowPos(m_kPresent.hDeviceWindow, 
            NULL, 
            m_rcWindow.left,
            m_rcWindow.top, 
            m_rcWindow.right - m_rcWindow.left,
            m_rcWindow.bottom - m_rcWindow.top,
            SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW);
    }

    riNewWidth = m_rcWindow.right - m_rcWindow.left + 1;
    riNewHeight = m_rcWindow.bottom - m_rcWindow.top + 1;
}
//----------------------------------------------------------------------------
bool DxRenderer::IsWindowed ()
{
    return ( m_kPresent.Windowed ? true : false );
}
//----------------------------------------------------------------------------
void DxRenderer::ClearBackBuffer ()
{
    ms_hResult = m_pqDevice->Clear(0,NULL,D3DCLEAR_TARGET,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearZBuffer ()
{
    ms_hResult = m_pqDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearStencilBuffer ()
{
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);

    ms_hResult = m_pqDevice->Clear(0,NULL,D3DCLEAR_STENCIL,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearBuffers ()
{
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);

    ms_hResult = m_pqDevice->Clear(0,NULL,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearBackBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    D3DRECT kRect;
    kRect.x1 = (long)iXPos;
    kRect.y1 = (long)iYPos;
    kRect.x2 = (long)(iXPos + iWidth - 1);
    kRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pqDevice->Clear(1,&kRect,D3DCLEAR_TARGET,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearZBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    D3DRECT kRect;
    kRect.x1 = (long)iXPos;
    kRect.y1 = (long)iYPos;
    kRect.x2 = (long)(iXPos + iWidth - 1);
    kRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pqDevice->Clear(1,&kRect,D3DCLEAR_ZBUFFER,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearStencilBuffer (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    D3DRECT kRect;
    kRect.x1 = (long)iXPos;
    kRect.y1 = (long)iYPos;
    kRect.x2 = (long)(iXPos + iWidth - 1);
    kRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);

    ms_hResult = m_pqDevice->Clear(1,&kRect,D3DCLEAR_STENCIL,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::ClearBuffers (int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    D3DRECT kRect;
    kRect.x1 = (long)iXPos;
    kRect.y1 = (long)iYPos;
    kRect.x2 = (long)(iXPos + iWidth - 1);
    kRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pqDevice->SetRenderState(D3DRS_STENCILMASK,~0);
    WML_DX_ERROR_CHECK(SetRenderState);

    ms_hResult = m_pqDevice->Clear(1,&kRect,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
        D3DCOLOR_COLORVALUE(m_kBackgroundColor.r,m_kBackgroundColor.g,
        m_kBackgroundColor.b,1.0f),1.0f,0);
    WML_DX_ERROR_CHECK(Clear);
}
//----------------------------------------------------------------------------
void DxRenderer::InitializeState ()
{
    Renderer::InitializeState();

    // Enable z-buffering.
    ms_hResult = m_pqDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
    WML_DX_ERROR_CHECK(SetRenderState);

    // If the card has more texture units than the WildMagic software
    // currently supports, then make sure that the first one following
    // the maximum number that the software supports is disabled because
    // DirectX will then disable all subsequent texture units.
    if ( m_iMaxTextureUnits > TextureState::MAX_TEXTURES )
    {
        int iUnit = TextureState::MAX_TEXTURES;

        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLOROP,
            D3DTOP_DISABLE);
        WML_DX_ERROR_CHECK(SetTextureStageState);
    }
}
//----------------------------------------------------------------------------
void DxRenderer::DisplayBackBuffer ()
{
    ms_hResult = m_pqDevice->Present(NULL,NULL,NULL,NULL);
    if ( ms_hResult != D3DERR_DEVICELOST )
        WML_DX_ERROR_CHECK(Present);
} 
//----------------------------------------------------------------------------
void DxRenderer::DrawSetupModelWorldTransform(const Geometry& rkPrimitive)
{
    // set model-to-world transformation
    const Matrix3f& rkRot = rkPrimitive.WorldRotate();
    const Vector3f& rkTrn = rkPrimitive.WorldTranslate();
    float fScale = rkPrimitive.WorldScale();

    // D3D does vector*matrix, but WildMagic does matrix*vector.
    m_kCurrentWorldMatrix(0,0) = fScale*rkRot[0][0];
    m_kCurrentWorldMatrix(0,1) = fScale*rkRot[1][0];
    m_kCurrentWorldMatrix(0,2) = fScale*rkRot[2][0];
    m_kCurrentWorldMatrix(0,3) = 0.0f;

    m_kCurrentWorldMatrix(1,0) = fScale*rkRot[0][1];
    m_kCurrentWorldMatrix(1,1) = fScale*rkRot[1][1];
    m_kCurrentWorldMatrix(1,2) = fScale*rkRot[2][1];
    m_kCurrentWorldMatrix(1,3) = 0.0f;

    m_kCurrentWorldMatrix(2,0) = fScale*rkRot[0][2];
    m_kCurrentWorldMatrix(2,1) = fScale*rkRot[1][2];
    m_kCurrentWorldMatrix(2,2) = fScale*rkRot[2][2];
    m_kCurrentWorldMatrix(2,3) = 0.0f;

    m_kCurrentWorldMatrix(3,0) = rkTrn.X();
    m_kCurrentWorldMatrix(3,1) = rkTrn.Y();
    m_kCurrentWorldMatrix(3,2) = rkTrn.Z();
    m_kCurrentWorldMatrix(3,3) = 1.0f;
    
    ms_hResult = m_pqDevice->SetTransform(D3DTS_WORLDMATRIX(0),
        &m_kCurrentWorldMatrix); 
    WML_DX_ERROR_CHECK(SetTransform);
}
//----------------------------------------------------------------------------
void DxRenderer::DrawSetupVertexBuffer(const Geometry& rkPrimitive)
{
    // What is max texture unit that might be needed for rendering effects?
    // If none, then should be -1 after loop.
    int iMaxNeededTextureUnit;
    for (iMaxNeededTextureUnit = TextureState::MAX_TEXTURES;
        iMaxNeededTextureUnit >= 0; iMaxNeededTextureUnit--)
    {
        if ( TextureUnitRequested(iMaxNeededTextureUnit) )
            break;
    }

    // Vertex shaders are picky about the input they receive.  If your
    // primitive has vertices, normals, and colors, but the program only
    // expects vertices and colors, then it should not send the normals.  
    // The shader will still run, but it will cause more overhead.  Thus
    // when shaders are enabled, it will override the behavior of the
    // vertex buffer.  To ensure realistic behavior, it will also check to
    // make sure that if a shader requests normals that the geometry must
    // also be able to send it, and will throw an assert otherwise.

    // Shader state needs to be set before the vertex buffer is set up

    // To facilitate this overriding, there are a set of booleans here, to be
    // used in this function:

    bool bHasVertexShader = (m_pkCurVertexShader != NULL);
    bool bHasPixelShader = (m_pkCurPixelShader != NULL);

    // Setup vertex format.
    // There will always be vertex coordinates
    const Vector3f* akVertex = rkPrimitive.Vertices();
    DWORD dwFormat = D3DFVF_XYZ;
    int iVertexSize = 3*sizeof(float);

    // Normal at each vertex?
    const Vector3f* akNormal = rkPrimitive.Normals();
    if ( akNormal && ( !bHasVertexShader || 
        m_pkCurVertexShader->NeedsNormals() ) )
    {
        dwFormat |= D3DFVF_NORMAL;
        iVertexSize += 3*sizeof(float);
    }
    else
    {
        // ensure that it isn't the case that there is a vertex shader
        // that needs normals, but the geometry just doesn't have any to send.
        assert( !bHasVertexShader || !m_pkCurVertexShader->NeedsNormals() );
    } 

    // Color at each vertex?
    // If a bump map is being drawn, the colors need to be calculated if
    // the bump map object has morphed since last time it was drawn.
    const ColorRGB* akColor = rkPrimitive.Colors();
    if ( akColor && ( !bHasVertexShader || 
        m_pkCurVertexShader->NeedsColor() ) )
    {
        dwFormat |= D3DFVF_DIFFUSE;
        iVertexSize += sizeof(DWORD);

        if ( NULL != m_pkCurrentBumpMap )
        {
            // Fill the color array with light direction vectors.  This uses
            // conceptual constness.  The typecast allows the color array to
            // be modified transparently by the renderer.  The typecast is
            // safe to do since the callers of DrawPrimitive make sure that
            // bump mapping is disabled for non-TriMesh objects.
            assert ( NULL != WmlDynamicCast(TriMesh,
                const_cast<Geometry*>(&rkPrimitive)) );
            m_pkCurrentBumpMap->ComputeLightVectors((TriMesh&)rkPrimitive);
        }
    }
    else
    {
        // ensure that it isn't the case that there is a vertex shader
        // that needs colors, but the geometry just doesn't have any to send.
        assert( !bHasVertexShader || !m_pkCurVertexShader->NeedsColor() ||
            akColor );
    }

    // Texture coordinate sets defined at each vertex?
    // Or will an automatic generation of texture coordinates
    // be used on a texture set?
    // NOTE: A texture coordinate set is always mapped to
    // the texture stage unit of the same index.
    assert ( 4 == TextureState::MAX_TEXTURES );
    const Vector2f* aakTexture[TextureState::MAX_TEXTURES] = {
        rkPrimitive.Textures(),rkPrimitive.Textures1(),
        rkPrimitive.Textures2(),rkPrimitive.Textures3()};

    // If there is bump map active, then setup the first texture unit for
    // its use and allow no other user-defined textures.  BumpMap will allow
    // user-defined textures to be drawn on another pass.
    const Vector2f* akTextureBump = rkPrimitive.TexturesBump();
    if ( (NULL != akTextureBump ) && ( NULL != m_pkCurrentBumpMap ) )
    {
        iMaxNeededTextureUnit = 0;
        dwFormat |= D3DFVF_TEXCOORDSIZE2(0);
        iVertexSize += 2*sizeof(float);
    }
    else
    {
        for (int iUnit = TextureState::MAX_TEXTURES-1; iUnit >= 0; iUnit--)
        {
            // Texture coordinate set defined?  Or texture unit needed
            // for a rendering effect?  If a unit is defined, then all
            // the units with indexes less than it must also be defined.

            // If vertex shaders are being used, assert that for every
            // texture coordinate that is needed, there are textures for it.
            if ( ( ( aakTexture[iUnit] ) || 
                ( iUnit <= iMaxNeededTextureUnit ) ) &&
                ( !bHasVertexShader || 
                m_pkCurVertexShader->NeedsTexCoords(iUnit) ) )
            {
                dwFormat |= D3DFVF_TEXCOORDSIZE2(iUnit);
                iVertexSize += 2*sizeof(float);
                if ( iUnit > iMaxNeededTextureUnit )
                {
                    iMaxNeededTextureUnit = iUnit;
                }
            }
            else
            {
                // Ensure that it isn't the case that there is a vertex shader
                // that needs tex coords, but the geometry just doesn't have
                // any to send.
                assert( !bHasVertexShader || 
                    !m_pkCurVertexShader->NeedsTexCoords(iUnit) );
            }
        }
    }

    // The index of the maximum texture unit needed determines
    // the maximum number of texture coordinate sets defined.
    dwFormat |= ((iMaxNeededTextureUnit+1) << D3DFVF_TEXCOUNT_SHIFT);

    // create a vertex buffer
    int iNumVertices = rkPrimitive.GetVertexQuantity();
    IVertexBufferPtr pqVertexBuffer;
    ms_hResult = m_pqDevice->CreateVertexBuffer(iVertexSize*iNumVertices,
        D3DUSAGE_WRITEONLY,dwFormat,D3DPOOL_MANAGED,&pqVertexBuffer,NULL);
    WML_DX_ERROR_CHECK(CreateVertexBuffer);


    // Pack the vertex buffer with Wild Magic data.  TO DO:  Some day allow
    // conditional compiling of the Wild Magic data to allow the format to
    // match what the renderer expects.  This will avoid repacking data in
    // a strided manner as occurs below.
    BYTE* pbVertices;
    ms_hResult = pqVertexBuffer->Lock(0,0,(void**)(&pbVertices),0);
    WML_DX_ERROR_CHECK(Lock);

    // In the Flexible Vertex Format, if the following vertex attributes
    // are defined, they must appear in the vertex "structure" in the
    // following order:
    //  . vertex coordinates
    //  . normal vector
    //  . color RGBA
    //  . texture coordinates

    // vertex, normal, color, 4 texture coords, END == 8 elements
    
    int iE = 0;
    BYTE* pbCurrentVertex = (BYTE*)pbVertices;
    int i;
    for (i = 0; i < iNumVertices; i++)
    {
        memcpy(pbCurrentVertex,akVertex,3*sizeof(float));
        pbCurrentVertex += iVertexSize;
        akVertex++;
    }
    pbVertices += 3*sizeof(float);

    if ( akNormal && ( !bHasVertexShader || 
        m_pkCurVertexShader->NeedsNormals() ) )
    {
        for (i = 0, pbCurrentVertex = pbVertices; i < iNumVertices; i++)
        {
            memcpy(pbCurrentVertex,akNormal,3*sizeof(float));
            pbCurrentVertex += iVertexSize;
            akNormal++;
        }
        pbVertices += 3*sizeof(float);
    }

    if ( akColor && ( !bHasVertexShader || 
        m_pkCurVertexShader->NeedsColor() ) )
    {
        for (i = 0, pbCurrentVertex = pbVertices; i < iNumVertices; i++)
        {
            DWORD dwColor = D3DCOLOR_COLORVALUE(akColor->r,akColor->g,
                akColor->b,1.0f);
            memcpy(pbCurrentVertex,&dwColor,sizeof(DWORD));
            pbCurrentVertex += iVertexSize;
            akColor++;
        }
        pbVertices += sizeof(DWORD);
    }

    // Bump map texture definition overrides all user-defined textures.
    // In doing so, it uses only the first texture unit.
    if ( (NULL != akTextureBump ) && ( NULL != m_pkCurrentBumpMap ) )
    {
        for (i = 0, pbCurrentVertex = pbVertices; i < iNumVertices;
            i++)
        {
            memcpy(pbCurrentVertex,akTextureBump,2*sizeof(float));
            pbCurrentVertex += iVertexSize;
            akTextureBump++;
        }
    }
    else
    {
        for (int iUnit = 0; iUnit <= iMaxNeededTextureUnit; iUnit++)
        {
            if ( aakTexture[iUnit] && ( !bHasVertexShader ||
                m_pkCurVertexShader->NeedsTexCoords(iUnit) ) )
            {
                const Vector2f* akTexture = aakTexture[iUnit];
                for (i = 0, pbCurrentVertex = pbVertices; i < iNumVertices;
                    i++)
                {
                    memcpy(pbCurrentVertex,akTexture,2*sizeof(float));
                    pbCurrentVertex += iVertexSize;
                    akTexture++;
                }
            }
            pbVertices += 2*sizeof(float);
        }
    }

    ms_hResult = pqVertexBuffer->Unlock();
    WML_DX_ERROR_CHECK(Unlock);

    ms_hResult = m_pqDevice->SetStreamSource(0,pqVertexBuffer,0,iVertexSize);
    WML_DX_ERROR_CHECK(SetStreamSource);

    ms_hResult = m_pqDevice->SetFVF(dwFormat);
    WML_DX_ERROR_CHECK(SetVertexShader);

    // Set the texture state for the bump map directly.
    if ( NULL != m_pkCurrentBumpMap )
    {
        SetTextureState(m_pkCurrentBumpMap->GetTextureState());
    }
}
//----------------------------------------------------------------------------
void DxRenderer::DrawPrimitive (const Geometry& rkPrimitive,
    D3DPRIMITIVETYPE eType, int iIQuantity, const int* aiIndices,
    int iPrimitiveQuantity)
{
    // Setup model-world transform and vertex buffer.
    DrawSetupModelWorldTransform(rkPrimitive);
    SetShaderConstants(&rkPrimitive);
    DrawSetupVertexBuffer(rkPrimitive);

    // create an index buffer
    unsigned int uiBufferLength = (unsigned int)(iIQuantity*sizeof(short));
    IIndexBufferPtr pqIndexBuffer;
    ms_hResult = m_pqDevice->CreateIndexBuffer(uiBufferLength,
        D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&pqIndexBuffer,
        NULL);
    WML_DX_ERROR_CHECK(CreateIndexBuffer);

    // Construct an index list.  D3D expects 'unsigned short' index values.
    // Wild Magic stores these as 'int' to allow for more than 65535 triangles
    // in a mesh.  Thus, the 'int' indices must be packaged appropriately.
    void* pbIndices;
    ms_hResult = pqIndexBuffer->Lock(0,uiBufferLength,&pbIndices,0);
    WML_DX_ERROR_CHECK(Lock);

    unsigned short* pusIndex = (unsigned short*) pbIndices;
    const int* piIndex = aiIndices;
    for (int i = 0; i < iIQuantity; i++)
        *pusIndex++ = (unsigned short)(*piIndex++);

    ms_hResult = pqIndexBuffer->Unlock();
    WML_DX_ERROR_CHECK(Unlock);

    ms_hResult = m_pqDevice->SetIndices(pqIndexBuffer);
    WML_DX_ERROR_CHECK(SetIndices);

    int iNumVertices;
    if ( eType == D3DPT_LINESTRIP )
    {
        iNumVertices = ((Polyline*)&rkPrimitive)->GetActiveQuantity();
        ms_hResult = m_pqDevice->DrawIndexedPrimitive(eType,0,0,iNumVertices,
            0,iPrimitiveQuantity);
    }
    else if ( eType == D3DPT_LINELIST )
    {
        iNumVertices = ((Polyline*)&rkPrimitive)->GetActiveQuantity();
        ms_hResult = m_pqDevice->DrawPrimitive(eType,0,iNumVertices/2);
    }
    else
    {
        iNumVertices = rkPrimitive.GetVertexQuantity();
        ms_hResult = m_pqDevice->DrawIndexedPrimitive(eType,0,0,iNumVertices,
            0,iPrimitiveQuantity);
    }

    WML_DX_ERROR_CHECK(DrawIndexedPrimitive);
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const TriMesh &rkMesh)
{
    DrawPrimitive(rkMesh,D3DPT_TRIANGLELIST,3*rkMesh.GetTriangleQuantity(),
        rkMesh.Connectivity(),rkMesh.GetTriangleQuantity());
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const Particles& rkParticle)
{
    const TriMesh& rkMesh = *rkParticle.GetMesh();
    DrawPrimitive(rkMesh,D3DPT_TRIANGLELIST,3*rkMesh.GetTriangleQuantity(),
        rkMesh.Connectivity(),rkMesh.GetTriangleQuantity());
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const Wml::Polyline& rkLine)
{
    if ( rkLine.GetActiveQuantity() < 2 )
    {
        // polyline needs at least one line segment
        return;
    }

    // bump mapping not supported for lines
    BumpMap* pkSave = m_pkCurrentBumpMap;
    m_pkCurrentBumpMap = NULL;

    int iAQuantity = rkLine.GetActiveQuantity();
    if ( rkLine.Contiguous() )
    {
        if ( rkLine.Closed() )
        {
            int* aiIndex = new int[iAQuantity+1];
            memcpy(aiIndex,rkLine.Indices(),iAQuantity*sizeof(int));
            aiIndex[iAQuantity] = aiIndex[0];
            DrawPrimitive(rkLine,D3DPT_LINESTRIP,iAQuantity+1,aiIndex,
                iAQuantity);
            delete[] aiIndex;
        }
        else
        {
            DrawPrimitive(rkLine,D3DPT_LINESTRIP,iAQuantity,rkLine.Indices(),
                iAQuantity-1);
        }
    }
    else
    {
        DrawPrimitive(rkLine,D3DPT_LINELIST,iAQuantity,rkLine.Indices(),
            iAQuantity);
    }

    m_pkCurrentBumpMap = pkSave;
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const Polypoint& rkPoint)
{
    if ( rkPoint.GetActiveQuantity() == 0 )
        return;

    // bump mapping not supported for points
    BumpMap* pkSave = m_pkCurrentBumpMap;
    m_pkCurrentBumpMap = NULL;

    // Setup model-world transform and vertex buffer.
    DrawSetupModelWorldTransform(rkPoint);
    // Shaders are not valid for polypoints because they don't use a vertex
    // buffer (as of now).
    SetShaderState(NULL);
    DrawSetupVertexBuffer(rkPoint);
    
    ms_hResult = m_pqDevice->DrawPrimitive(D3DPT_POINTLIST,0,
        rkPoint.GetActiveQuantity());
    WML_DX_ERROR_CHECK(DrawPrimitive);

    m_pkCurrentBumpMap = pkSave;
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const ScreenPolygon &rkPolygon)
{
    // retrieve current view transform
    D3DXMATRIX kCurrentView;
    ms_hResult = m_pqDevice->GetTransform(D3DTS_VIEW,&kCurrentView);
    WML_DX_ERROR_CHECK(GetTransform);
    
    // retrieve current projection transform
    D3DXMATRIX kCurrentProject;
    ms_hResult = m_pqDevice->GetTransform(D3DTS_PROJECTION,&kCurrentProject);
    WML_DX_ERROR_CHECK(GetTransform);

    // set up world matrix
    D3DXMATRIX kWMat;
    D3DXMatrixIdentity(&kWMat);
    ms_hResult = m_pqDevice->SetTransform(D3DTS_WORLDMATRIX(0),&kWMat); 
    WML_DX_ERROR_CHECK(SetTransform);

    // set up an orthogonal view frustum in normalized coordinates
    D3DXMATRIX kProject, kView;
    D3DXMatrixOrthoOffCenterRH(&kProject,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f);

    D3DXVECTOR3 kEye(0.0f,0.0f,1.0f);
    D3DXVECTOR3 kAt(0.0f,0.0f,0.0f);
    D3DXVECTOR3 kUp(0.0f,1.0f,0.0f);
    D3DXMatrixLookAtRH(&kView,&kEye,&kAt,&kUp);

    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kView);
    WML_DX_ERROR_CHECK(SetTransform);

    ms_hResult = m_pqDevice->SetTransform(D3DTS_PROJECTION,&kProject);
    WML_DX_ERROR_CHECK(SetTransform);

    // Shaders do not work for screen polygons (right now).  If it was desired
    // to be able to do so, something different would have to be done for the
    // state constants, because this routine circumvents the camera.  Probably
    // the renderer would store the eye and lookat vectors as well and the
    // camera would update those in the same way it currently updates the
    // other model, view, and projection matrices.
    SetShaderState(NULL);

    // setup the vertex buffer
    DrawSetupVertexBuffer(*(rkPolygon.Mesh()));
    
    int iNumVertices = rkPolygon.Mesh()->GetVertexQuantity();
    ms_hResult = m_pqDevice->DrawPrimitive(D3DPT_TRIANGLEFAN,0,
        iNumVertices-2);
    WML_DX_ERROR_CHECK(DrawPrimitive);

    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&kCurrentView);
    WML_DX_ERROR_CHECK(SetTransform);

    ms_hResult = m_pqDevice->SetTransform(D3DTS_PROJECTION,&kCurrentProject);
    WML_DX_ERROR_CHECK(SetTransform);
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (int iX, int iY, const ColorRGB& rkColor,
    const char* acText)
{
    // disable shaders for text
    SetShaderState(NULL);

    RECT kText;
    kText.bottom = iY;
    kText.top = iY;
    kText.left = iX;
    kText.right = iX;
    
    m_pqDefaultFont->Begin();

    D3DCOLOR kColor = D3DCOLOR_COLORVALUE(rkColor.r,rkColor.g,rkColor.b,1.0f);

    ms_hResult = m_pqDefaultFont->DrawTextA(acText,-1,&kText,
        DT_LEFT | DT_BOTTOM | DT_CALCRECT,
        kColor);
    WML_DX_ERROR_CHECK(DrawTextA);

    ms_hResult = m_pqDefaultFont->DrawTextA(acText,-1,&kText,
        DT_LEFT | DT_BOTTOM,
        kColor);
    WML_DX_ERROR_CHECK(DrawTextA);

    m_pqDefaultFont->End();
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (int iX, int iY, const RendererFont& rkFont,
    const char* acText)
{
    // disable shaders for text
    SetShaderState(NULL);

    map<unsigned int,IFontPtr>::iterator pkIter =
        m_kFontMap.find(rkFont.GetID());

    if ( pkIter == m_kFontMap.end() )
        return;
    
    IFontPtr pqFont = pkIter->second;

    RECT kText;
    kText.bottom = iY;
    kText.top = iY;
    kText.left = iX;
    kText.right = iX;

    ColorRGB kColor = rkFont.Color();
    D3DCOLOR kD3DColor = D3DCOLOR_COLORVALUE(kColor.r,kColor.g,kColor.b,1.0f);

    pqFont->Begin();

    ms_hResult = pqFont->DrawTextA(acText,-1,&kText,
        DT_LEFT | DT_BOTTOM | DT_CALCRECT,
        kD3DColor);
    WML_DX_ERROR_CHECK(DrawTextA);

    ms_hResult = pqFont->DrawTextA(acText,-1,&kText,
        DT_LEFT | DT_BOTTOM,
        kD3DColor);
    WML_DX_ERROR_CHECK(DrawTextA);

    pqFont->End();
}
//----------------------------------------------------------------------------
void DxRenderer::Draw (const unsigned char* aucBuffer)
{
    // disable shaders for text
    SetShaderState(NULL);

    if ( !aucBuffer )
        return;

    IDirect3DSurface9* pkBackBuffer = NULL;
    HRESULT hResult = m_pqDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,
        &pkBackBuffer);
    assert( hResult == D3D_OK && pkBackBuffer );
    if ( hResult != D3D_OK || !pkBackBuffer )
        return;

    RECT kSrcRect = { 0, 0, m_iWidth-1, m_iHeight-1 };
    hResult = D3DXLoadSurfaceFromMemory(
        pkBackBuffer,
        NULL,
        NULL,
        aucBuffer,
        D3DFMT_R8G8B8,
        3*m_iWidth,
        NULL,
        &kSrcRect,
        D3DX_FILTER_NONE,
        0);
    assert( hResult == D3D_OK );
}
//----------------------------------------------------------------------------
