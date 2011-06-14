// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifndef WMLDXRENDERER_H
#define WMLDXRENDERER_H

#include "WmlDxException.h"
#include "WmlRendererLibType.h"
#include "WmlRenderer.h"


namespace Wml
{

class Geometry;


class WML_RENDERER_ITEM DxRenderer : public Renderer 
{
    WmlDeclareRTTI;

public:
    DxRenderer (BOOL bFullScreen, HWND hDisplayWnd, int iWidth, int iHeight);
    virtual ~DxRenderer ();

    void EstablishCapabilities ();

    virtual void Resize (int iWidth, int iHeight);
    IDevice* GetDevice ();

    virtual bool BeginScene ();
    virtual void EndScene ();

    virtual void ToggleFullScreen (int& riNewWidth, int& riNewHeight);
    virtual bool IsWindowed (); 
    virtual void ShowCursor (bool bShow);

    virtual void DisplayBackBuffer ();

    // Clear the buffer in the full window.
    virtual void ClearBackBuffer ();
    virtual void ClearZBuffer ();
    virtual void ClearStencilBuffer ();
    virtual void ClearBuffers ();

    // Clear the buffer in the specified subwindow.
    virtual void ClearBackBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearZBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearStencilBuffer (int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearBuffers (int iXPos, int iYPos, int iWidth,
        int iHeight);

    // management of texture resources
    virtual void ReleaseTexture (Texture* pkTexture);
    virtual void ReleaseShader (Shader* pkShader);

    // Object drawing.
    virtual void Draw (const Particles& rkParticle);
    virtual void Draw (const Polyline& rkLine);
    virtual void Draw (const Polypoint& rkPoint);
    virtual void Draw (const ScreenPolygon& rkPolygon);
    virtual void Draw (const TriMesh& rkMesh);
    virtual void Draw (int iX, int iY, const ColorRGB& rkColor,
        const char* acText);
    virtual bool LoadFont (const RendererFont& rkFont);
    virtual void UnloadFont (const RendererFont& rkFont);
    virtual void Draw (int iX, int iY, const RendererFont& rkFont,
        const char* acText);

    // Object drawing using render effects.
    virtual void Draw (const PlanarShadow& rkPShadow);
    virtual void Draw (const PlanarReflection& rkPReflection);
    virtual void Draw (const ProjectedTexture& rkPTexture);
    virtual void Draw (const GlossMap& rkGlossMap);
    virtual void Draw (const BumpMap& rkBumpMap);

    // Support for 2D application layer.  The buffer passed to this routine
    // must be an array of 24-bit RGB values and must have have the width and
    // height of the back buffer.
    virtual void Draw (const unsigned char* aucBuffer);

    // capabilities
    bool SupportsShader (const VertexShader* pkShader) const;
    bool SupportsShader (const PixelShader* pkShader) const;

    // Cached matrix getters
    D3DXMATRIX* GetWorldMatrix ();
    D3DXMATRIX* GetProjMatrix ();
    D3DXMATRIX* GetViewMatrix ();

protected:

    // state management
    virtual void InitializeState ();
    virtual void SetAlphaState (AlphaState* pkState);
    virtual void SetCullState (CullState* pkState);
    virtual void SetDitherState (DitherState* pkState);
    virtual void SetFogState (FogState* pkState);
    virtual void SetLightState (LightState* pkState);
    virtual void SetMaterialState (MaterialState* pkState);
    virtual void SetPolygonOffsetState (PolygonOffsetState* pkState);
    virtual void SetShadeState (ShadeState* pkState);
    virtual void SetTextureState (TextureState* pkState);
    virtual void SetVertexColorState (VertexColorState* pkState);
    virtual void SetWireframeState (WireframeState* pkState);
    virtual void SetZBufferState (ZBufferState* pkState);

    virtual void OnDeviceLost ();
    virtual void ResetDevice ();

    // management of texture resources
    virtual ITexture* CreateTexture (Image* pkImage);

    void DrawPrimitive (const Geometry& rkPrimitive, D3DPRIMITIVETYPE eType,
        int iIQuantity, const int* aiIndices, int iPrimitiveQuantity);

    // common support used by Draw* methods
    void DrawSetupModelWorldTransform (const Geometry& rkPrimitive);
    void DrawSetupVertexBuffer (const Geometry& rkPrimitive);

    // called internally by DrawSetupVertexBuffer
    virtual bool SetCurrentVertexShader (VertexShader* pkShader);
    virtual bool SetCurrentPixelShader (PixelShader* pkShader);

    // helper functions
    void CompileShader (PixelShader* pkShader);
    void CompileShader (VertexShader* pkShader);

    // management of shaders
    virtual void CompileShader (Shader* pkShader);

    virtual void SetStateConst (float* afData, const Geometry& rkGeom,
        StateConstantType iType, int iTypeNum);
    virtual void SetPixelShaderConst (unsigned int uiRegister,
        float* afData, int iNumOfVector4s);
    virtual void SetPixelShaderConst (ShaderConstants* pkShaderConsts,
        const Geometry& rkGeom);
    virtual void SetVertexShaderConst (unsigned int uiRegister,
        float* afData, int iNumOfVector4s);
    virtual void SetVertexShaderConst (ShaderConstants* pkShaderConsts,
        const Geometry& rkGeom);

protected:
    IMainPtr m_pqMain;
    IDevicePtr m_pqDevice;
    D3DPRESENT_PARAMETERS m_kPresent;
    bool m_bDeviceLost;
    bool m_bCursorVisible;
    RECT m_rcWindow;

    // font handling
    IFontPtr m_pqDefaultFont;
    std::map<unsigned int,IFontPtr> m_kFontMap;

    // current model->world matrix (cached for shader usage)
    D3DXMATRIX m_kCurrentWorldMatrix;
    D3DXMATRIX m_kCurrentViewMatrix;
    D3DXMATRIX m_kCurrentProjMatrix;

    static DWORD ms_adwAlphaSrcBlend[];
    static DWORD ms_adwAlphaDstBlend[];
    static DWORD ms_adwAlphaTest[];
    static DWORD ms_adwCullType[];
    static DWORD ms_adwFogDensity[];
    static DWORD ms_adwShadeMode[];
    static DWORD ms_adwZBufferCompare[];
    static DWORD ms_adwTexMagFilter[];
    static DWORD ms_adwTexMinFilter[];
    static DWORD ms_adwTexMipFilter[];
    static DWORD ms_adwTexWrapModeU[];
    static DWORD ms_adwTexWrapModeV[];
    static DWORD ms_adwTexCombineSource[];
    static DWORD ms_adwTexCombineOperand[];
    static DWORD ms_adwTexFormat[];
    static int ms_aiTexSize[];

    // Setup texture stage to pass color and alpha to next stage.
    void SetTextureStageApplyPass (const int iUnit);

    // DirectX SetTextureStageState parameters corresponding to
    // WildMagic texture combine parameters.
    class WML_RENDERER_ITEM SetTextureStageStateApplyParms
    {
    public:

        // Constructors.
        explicit SetTextureStageStateApplyParms (const DWORD dwArg1);
        SetTextureStageStateApplyParms (const D3DTEXTUREOP eOp,
            const DWORD dwArg1, const DWORD dwArg2);
        SetTextureStageStateApplyParms (const D3DTEXTUREOP eOp,
            const DWORD dwArg1, const DWORD dwArg2, const DWORD dwArg3);

        // How many arguments are used for the operation?
        int NumArgs() const     { return m_iNumArgs; }

        // Retrieve the operation and the arguments.
        D3DTEXTUREOP Op() const { return m_eTextureOp; }
        DWORD Arg1() const      { return m_dwArg1; }
        DWORD Arg2() const      { return m_dwArg2; }
        DWORD Arg0() const      { return m_dwArg0; }

    private:
        // DirectX texture operation for specified function.
        D3DTEXTUREOP m_eTextureOp;

        // Number of args valid used for the operation.
        // Use in order: Arg1, then Arg2, and then Arg3.
        int m_iNumArgs;

        // Individual args for the operation.  Note that these use a
        // different indexing scheme in DX versus WM.
        DWORD m_dwArg1; // DX *ARG1 which typically is WM Arg0
        DWORD m_dwArg2; // DX *ARG2 which typically is WM Arg1
        DWORD m_dwArg0; // DX *ARG0 which typically is WM Arg2
    };

    // Convert WildMagic texture apply combine parameters into
    // DirectX SetTextureStageState parameters.  Returns indication
    // of whether or not the conversion was successful.
    bool ConvertToSetTextureStageStateApplyParms (
        SetTextureStageStateApplyParms* pParms,
        const Texture::ApplyCombineFunction eCombineFunction,
        const Texture::ApplyCombineScale eCombineScale,
        const DWORD dwArg0, const DWORD dwArg1, const DWORD dwArg2);

    // maintain a list of all textures, so that they can be released on exit
    std::vector<ITexture*> m_kDxTextures;

    // for error checking and exception handling
    static HRESULT ms_hResult;
};
    
WmlSmartPointer(DxRenderer);
#include "WmlDxRenderer.inl"

}

#endif
