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

int DxRenderer::ms_aiTexSize[Image::IT_QUANTITY] =
{
    4,    // Image::IT_RGBA4444
    3,    // Image::IT_RGB888
    4,    // Image::IT_RGBA5551
    4,    // Image::IT_RGBA8888
};

DWORD DxRenderer::ms_adwTexFormat[Image::IT_QUANTITY] =
{
    D3DFMT_A4R4G4B4,    // Image::IT_RGBA4444
    D3DFMT_R8G8B8,      // Image::IT_RGB888
    D3DFMT_A1R5G5B5,    // Image::IT_RGBA5551
    D3DFMT_A8R8G8B8,    // Image::IT_RGBA8888
};

DWORD DxRenderer::ms_adwTexMagFilter[Texture::FM_QUANTITY] =
{
    D3DTEXF_POINT,      // Texture::FM_NEAREST
    D3DTEXF_LINEAR,     // Texture::FM_LINEAR
};

DWORD DxRenderer::ms_adwTexMinFilter[Texture::MM_QUANTITY] =
{
    D3DTEXF_POINT,  // Texture::MM_NONE
    D3DTEXF_POINT,  // Texture::MM_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR
    D3DTEXF_POINT,  // Texture::MM_NEAREST_NEAREST
    D3DTEXF_POINT,  // Texture::MM_NEAREST_LINEAR
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_LINEAR
};

DWORD DxRenderer::ms_adwTexMipFilter[Texture::MM_QUANTITY] =
{
    D3DTEXF_NONE,   // Texture::MM_NONE
    D3DTEXF_NONE,   // Texture::MM_NEAREST
    D3DTEXF_NONE,   // Texture::MM_LINEAR
    D3DTEXF_POINT,  // Texture::MM_NEAREST_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_NEAREST_LINEAR
    D3DTEXF_POINT,  // Texture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_LINEAR
};

DWORD DxRenderer::ms_adwTexWrapModeU[Texture::WM_QUANTITY] =
{
    D3DTADDRESS_CLAMP,      // Texture::WM_CLAMP_S_CLAMP_T
    D3DTADDRESS_CLAMP,      // Texture::WM_CLAMP_S_WRAP_T
    D3DTADDRESS_WRAP,       // Texture::WM_WRAP_S_CLAMP_T
    D3DTADDRESS_WRAP,       // Texture::WM_WRAP_S_WRAP_T
    D3DTADDRESS_BORDER,     // Texture::WM_CLAMP_BORDER_S_CLAMP_BORDER_T
};

DWORD DxRenderer::ms_adwTexWrapModeV[Texture::WM_QUANTITY] =
{
    D3DTADDRESS_CLAMP,      // Texture::WM_CLAMP_S_CLAMP_T
    D3DTADDRESS_WRAP,       // Texture::WM_CLAMP_S_WRAP_T
    D3DTADDRESS_CLAMP,      // Texture::WM_WRAP_S_CLAMP_T
    D3DTADDRESS_WRAP,       // Texture::WM_WRAP_S_WRAP_T
    D3DTADDRESS_BORDER,     // Texture::WM_CLAMP_BORDER_S_CLAMP_BORDER_T
};

DWORD DxRenderer::ms_adwTexCombineSource[Texture::ACS_QUANTITY] =
{
    D3DTA_TEXTURE,  // Texture::ACS_TEXTURE
    D3DTA_DIFFUSE,  // Texture::ACS_PRIMARY_COLOR
    D3DTA_TFACTOR,  // Texture::ACS_CONSTANT
    D3DTA_CURRENT,  // Texture::ACS_PREVIOUS
};

DWORD DxRenderer::ms_adwTexCombineOperand[Texture::ACO_QUANTITY] =
{
    0,                                    // Texture::ACO_SRC_COLOR
    D3DTA_COMPLEMENT,                     // Texture::ACO_ONE_MINUS_SRC_COLOR
    D3DTA_ALPHAREPLICATE,                 // Texture::ACO_SRC_ALPHA
    D3DTA_COMPLEMENT|D3DTA_ALPHAREPLICATE,// Texture::ACO_ONE_MINUS_SRC_ALPHA
};

//----------------------------------------------------------------------------
DxRenderer::SetTextureStageStateApplyParms::SetTextureStageStateApplyParms (
    const DWORD dwArg1)
{
    m_iNumArgs = 1;
    m_eTextureOp = D3DTOP_SELECTARG1;
    m_dwArg1 = dwArg1;    
}
//----------------------------------------------------------------------------
DxRenderer::SetTextureStageStateApplyParms::SetTextureStageStateApplyParms (
    const D3DTEXTUREOP eOp, const DWORD dwArg1, const DWORD dwArg2)
{
    m_iNumArgs = 2;
    m_eTextureOp = eOp;
    m_dwArg1 = dwArg1;
    m_dwArg2 = dwArg2;
}
//----------------------------------------------------------------------------
DxRenderer::SetTextureStageStateApplyParms::SetTextureStageStateApplyParms (
    const D3DTEXTUREOP eOp, const DWORD dwArg1, const DWORD dwArg2,
    const DWORD dwArg3)
{
    // IMPORTANT!  For triadic operations, the DX documentation refers
    // to Arg1 which is really stored in *ARG0, Arg2 which is really
    // stored in *ARG1, and Arg3 which is really stored in *ARG2.
    m_iNumArgs = 3;
    m_eTextureOp = eOp;
    m_dwArg0 = dwArg1;
    m_dwArg1 = dwArg2;
    m_dwArg2 = dwArg3;
}
//----------------------------------------------------------------------------
void DxRenderer::SetTextureStageApplyPass (const int iUnit)
{
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLOROP,
        D3DTOP_SELECTARG1);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_ALPHAOP,
        D3DTOP_SELECTARG1);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLORARG1,
        D3DTA_CURRENT);
    WML_DX_ERROR_CHECK(SetTextureStageState);
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_ALPHAARG1,
        D3DTA_CURRENT);
    WML_DX_ERROR_CHECK(SetTextureStageState);
}
//----------------------------------------------------------------------------
bool DxRenderer::ConvertToSetTextureStageStateApplyParms (
    SetTextureStageStateApplyParms* pParms,
    const Texture::ApplyCombineFunction eCombineFunction,
    const Texture::ApplyCombineScale eCombineScale,
    const DWORD dwArg0, const DWORD dwArg1, const DWORD dwArg2)
{
    assert ( 0 != pParms );
    bool bReturnSuccess = true;

    switch ( eCombineScale )
    {
    case Texture::ACSC_FOUR:
        if ( Texture::ACF_MODULATE == eCombineFunction )
        {
            *pParms = SetTextureStageStateApplyParms(D3DTOP_MODULATE4X,
                dwArg0,dwArg1);
        }
        else
        {
            // 4X not supported for texture combine function
            assert ( false );
            bReturnSuccess = false;
        }
        break;

    case Texture::ACSC_TWO:
        if ( Texture::ACF_MODULATE == eCombineFunction )
        {
            *pParms = SetTextureStageStateApplyParms(D3DTOP_MODULATE2X,
                dwArg0,dwArg1);
        }
        else if ( Texture::ACF_ADD_SIGNED == eCombineFunction )
        {
            *pParms = SetTextureStageStateApplyParms(D3DTOP_ADDSIGNED2X,
                dwArg0,dwArg1);
        }
        else
        {
            // 2X not supported for texture combine function
            assert ( false );
            bReturnSuccess = false;
        }
        break;

    case Texture::ACSC_ONE:
        switch ( eCombineFunction )
        {
        case Texture::ACF_REPLACE:
            *pParms = SetTextureStageStateApplyParms(dwArg0);
            break;
        case Texture::ACF_MODULATE:
            *pParms = SetTextureStageStateApplyParms(D3DTOP_MODULATE,
                dwArg0,dwArg1);
            break;
        case Texture::ACF_ADD:
            *pParms = SetTextureStageStateApplyParms(D3DTOP_ADD,
                dwArg0,dwArg1);
            break;
        case Texture::ACF_ADD_SIGNED:
            *pParms = SetTextureStageStateApplyParms(D3DTOP_ADDSIGNED,
                dwArg0,dwArg1);
            break;
        case Texture::ACF_SUBTRACT:
            *pParms = SetTextureStageStateApplyParms(D3DTOP_SUBTRACT,
                dwArg0,dwArg1);
            break;
        case Texture::ACF_INTERPOLATE:
            // Notice the change in the parameter order.  That is
            // because the indexing is not identical between WM and DX.
            *pParms = SetTextureStageStateApplyParms(D3DTOP_LERP,dwArg2,
                dwArg0,dwArg1);
            break;
        case Texture::ACF_DOT3_RGB:
            if ( m_bCapTextureApplyCombineDot3 )
            {
                *pParms = SetTextureStageStateApplyParms(D3DTOP_DOTPRODUCT3,
                    dwArg0,dwArg1);
            }
            else
            {
                bReturnSuccess = false;
            }
            break;
        case Texture::ACF_DOT3_RGBA:
            if ( m_bCapTextureApplyCombineDot3 )
            {
                *pParms = SetTextureStageStateApplyParms(D3DTOP_DOTPRODUCT3,
                    dwArg0,dwArg1);
            }
            else
            {
                bReturnSuccess = false;
            }
            break;
        default:
            // Texture combine function not implemented.
            assert ( false );
            bReturnSuccess = false;
            break;
        }
        break;

    default:
        // Output texture combine scale factor not supported.
        assert ( false );
        bReturnSuccess = false;
        break;
    }

    return bReturnSuccess;
}
//----------------------------------------------------------------------------
void DxRenderer::SetTextureState (TextureState* pkState)
{
    // Due to DX9 considerations, this must be called after the Renderer's
    // current vertex shader has been set (so we can tell if the vertex shader
    // is on or not).

    // Details: every call to SetTextureStage( iUnit, D3DTSS_TEXCOORDINDEX,
    // iUnit + foo ) must have foo == 0 for the programmable pipeline.  In
    // DX8.1 these were quietly ignored, but they decided to throw some errors
    // in DX9.  Also, every call to SetTextureStage( iUnit,
    // D3DTSS_TEXTURETRANSFORMFLAGS, foo ) must have foo == D3DTTFF_DISABLE
    // for shaders too.
    const bool bVertShader = (m_pkCurVertexShader != NULL);

    // What is the maximum number of texture units?  The minimum of
    //  . maximum number of texture units available on the card OR
    //  . maximum number of texture units supported by WildMagic
    int iMaxTextureUnits = ( m_iMaxTextureUnits < TextureState::MAX_TEXTURES )
        ? m_iMaxTextureUnits : TextureState::MAX_TEXTURES;

    int iUnit;

    // Loop through each of the possible textures.
    // Enable each one that is defined.
    // Determine the maximum index of the texture units in use.
    int iMaxTextureUnitInUse = -1;
    for (iUnit = 0; iUnit < iMaxTextureUnits; iUnit++)
    {
        // Note if this texture unit was reserved for use by a render effect.
        // TO DO.  Note that if a texture is in this unit by being stored
        // there for a render effect AND a texture is defined for this unit,
        // the texture for that render effect will be lost for all subsequent
        // renderings of the parts model as part of this iteration of
        // the effect.
        if ( TextureUnitRequested(iUnit) )
        {
            iMaxTextureUnitInUse = iUnit;
        }

        // Skip if texture not defined for this stage.
        Texture* pkTexture = pkState->Get(iUnit);
        if ( NULL == pkTexture )
        {
            continue;
        }

        // Skip if texture image not defined for this stage.
        Image* pkTextureImage = pkTexture->GetImage();
        if ( NULL == pkTextureImage )
        {
            continue;
        }

        // Set the texture for this stage.
        // Create the texture in the device if not already done so.
        ITexture* pqTexture;
        pkTexture->GetUserData(sizeof(ITexture*),&pqTexture);
        if ( pqTexture == NULL )
        {
            pqTexture = CreateTexture(pkTextureImage);
            if ( pqTexture == NULL )
                continue;
            pkTexture->SetUserData(sizeof(ITexture*),&pqTexture);
        }
        ms_hResult = m_pqDevice->SetTexture(iUnit,pqTexture);
        WML_DX_ERROR_CHECK(SetTexture);


        // If we get here, we are going to define this texture stage
        // below, so mark its index as being used.
        iMaxTextureUnitInUse = iUnit;


        // Set the texture priority.  In WM this value should be in [0,1],
        // but in DX, this value can be any DWORD value.
        float fPriority = pkTexture->Priority();
        DWORD dwPriority;
        if ( fPriority < 0.0f )
        {
            dwPriority = 0;
        }
        else if ( fPriority > 1.0f )
        {
            dwPriority = 0xFFFFFFFF;
        }
        else
        {
            dwPriority = DWORD(fPriority*0xFFFFFFFF);
        }
        pqTexture->SetPriority(dwPriority);


        // Setup the texture apply (combine) mode.
        // Legend for the texture combine mode defintions.
        // Legend symbols mainly taken from the OpenGL "red book".
        //  C - result color (RGB)
        //  A - result alpha
        //  Ct - texture color
        //  At - texture alpha
        //  Cf - fragment (current) color
        //  Af - fragment (current) alpha
        //  Cc - constant color
        //  Ac - constant alpha
        //  C1 - color argument 1
        //  A1 - alpha argument 1
        //  C2 - alpha argument 2
        //  A2 - alpha argument 2

        // Default is to pass the texture input to the output.
        static const SetTextureStageStateApplyParms kApplyParmsPass(
            D3DTA_CURRENT);
        SetTextureStageStateApplyParms kApplyParmsColor = kApplyParmsPass;
        SetTextureStageStateApplyParms kApplyParmsAlpha = kApplyParmsPass;

        switch ( pkTexture->Apply() )
        {
        case Texture::AM_REPLACE:
            {
                // C = Ct, Ct=C1
                static const SetTextureStageStateApplyParms
                    kApplyParmsColorReplace(D3DTA_TEXTURE);

                // A = At, At=A1
                static const SetTextureStageStateApplyParms
                    kApplyParmsAlphaReplace(D3DTA_TEXTURE);

                kApplyParmsColor = kApplyParmsColorReplace;
                kApplyParmsAlpha = kApplyParmsAlphaReplace;
            }
            break;

        case Texture::AM_DECAL:
            {
                // C = At*Ct + (1-At)*Cf, Ct=C1, Cf=C2
                static const SetTextureStageStateApplyParms
                    kApplyParmsColorDecal(D3DTOP_BLENDTEXTUREALPHA,
                    D3DTA_TEXTURE,D3DTA_CURRENT);

                // A = Af, Af=A1
                static const SetTextureStageStateApplyParms
                    kApplyParmsAlphaDecal(D3DTA_CURRENT);

                kApplyParmsColor = kApplyParmsColorDecal;
                kApplyParmsAlpha = kApplyParmsAlphaDecal;
            }
            break;

        case Texture::AM_MODULATE:
            {
                // C = Ct*Cf, Ct=C1, Cf=C2
                static const SetTextureStageStateApplyParms
                    kApplyParmsColorModulate(D3DTOP_MODULATE,D3DTA_TEXTURE,
                    D3DTA_CURRENT);

                // A = At*Af, At=A1, Af=A2
                static const SetTextureStageStateApplyParms
                    kApplyParmsAlphaModulate(D3DTOP_MODULATE,D3DTA_TEXTURE,
                    D3DTA_CURRENT);

                kApplyParmsColor = kApplyParmsColorModulate;
                kApplyParmsAlpha = kApplyParmsAlphaModulate;
            }
            break;

        case Texture::AM_BLEND:
            {
                // C = Ct*Cc + (1-Ct)*Cf, Ct=C1, Cc=C2, Cf=C3
                static const SetTextureStageStateApplyParms
                    kApplyParmsColorBlend(D3DTOP_LERP,D3DTA_TEXTURE,
                    D3DTA_TFACTOR,D3DTA_CURRENT);

                // A= At*Af, At=A1, Af=A2
                static const SetTextureStageStateApplyParms
                    kApplyParmsAlphaBlend(D3DTOP_MODULATE,D3DTA_TEXTURE,
                    D3DTA_CURRENT);

                kApplyParmsColor = kApplyParmsColorBlend;
                kApplyParmsAlpha = kApplyParmsAlphaBlend;
            }
            break;

        case Texture::AM_ADD:
            // If texture add combine mode is selected and
            // is not supported by the device, then pass current
            // texture input directly to output without any processing.
            if ( m_bCapTextureApplyAdd )
            {
                // C = Ct + Cf, Ct=C1, Cf=C2
                static const SetTextureStageStateApplyParms
                    kApplyParmsColorAdd(D3DTOP_ADD,D3DTA_TEXTURE,
                    D3DTA_CURRENT);

                // A = At + Af, At=C1, Af=A2
                static const SetTextureStageStateApplyParms
                    kApplyParmsAlphaAdd(D3DTOP_ADD,D3DTA_TEXTURE,
                    D3DTA_CURRENT);

                kApplyParmsColor = kApplyParmsColorAdd;
                kApplyParmsAlpha = kApplyParmsAlphaAdd;
            }
            break;

        case Texture::AM_COMBINE:
            // If generalized texture combine mode is selected and
            // is not supported by the device, then pass current
            // texture input directly to output without any processing.
            if ( m_bCapTextureApplyCombine )
            {
                // Retrieve the color args and the color combine parms.
                DWORD dwColorArg0 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc0RGB()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp0RGB()];
                DWORD dwColorArg1 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc1RGB()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp1RGB()];
                DWORD dwColorArg2 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc2RGB()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp2RGB()];
                bool bValidCombineColor =
                    ConvertToSetTextureStageStateApplyParms(&kApplyParmsColor,
                    pkTexture->CombineFuncRGB(),pkTexture->CombineScaleRGB(),
                    dwColorArg0,dwColorArg1,dwColorArg2);


                // Retrieve the alpha args.
                DWORD dwAlphaArg0 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc0Alpha()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp0Alpha()];
                DWORD dwAlphaArg1 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc1Alpha()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp1Alpha()];
                DWORD dwAlphaArg2 =
                    ms_adwTexCombineSource[pkTexture->CombineSrc2Alpha()] |
                    ms_adwTexCombineOperand[pkTexture->CombineOp2Alpha()];
                bool bValidCombineAlpha =
                    ConvertToSetTextureStageStateApplyParms(&kApplyParmsAlpha,
                    pkTexture->CombineFuncAlpha(),
                    pkTexture->CombineScaleAlpha(),dwAlphaArg0,dwAlphaArg1,
                    dwAlphaArg2);


                // If either color or alpha texture combine function
                // is not supported, then just setup the texture stage
                // to pass the input to the output.
                if ( bValidCombineColor && !bValidCombineAlpha )
                {
                    kApplyParmsColor = kApplyParmsPass;
                }
                else if ( !bValidCombineColor && bValidCombineAlpha )
                {
                    kApplyParmsAlpha = kApplyParmsPass;
                }
            }
            break;

        default:
            // Apply mode without implementation.
            assert ( false );
            break;
        }


        // WM supports 3- and 4-component textures.  The texture color
        // combine operation is the same regardless of whether the texture
        // used in the operation has 3- or 4-components.  However, the
        // texture alpha combine operation does change in the case of a
        // 3-component texture.  In that case, the alpha from the previous
        // stage is passed as the output of this stage.
        if ( 3 == ms_aiTexSize[pkTextureImage->GetType()] )
        {
            kApplyParmsAlpha = kApplyParmsPass;
        }


        // Set the texture color combine parameters.
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLOROP,
            kApplyParmsColor.Op());
        WML_DX_ERROR_CHECK(SetTextureStageState);
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLORARG1,
            kApplyParmsColor.Arg1());
        WML_DX_ERROR_CHECK(SetTextureStageState);
        if ( kApplyParmsColor.NumArgs() > 1 )
        {
            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_COLORARG2,kApplyParmsColor.Arg2());
            WML_DX_ERROR_CHECK(SetTextureStageState);
        }
        if ( kApplyParmsColor.NumArgs() > 2 )
        {
            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_COLORARG0,kApplyParmsColor.Arg0());
            WML_DX_ERROR_CHECK(SetTextureStageState);
        }

        // Set the texture alpha combine parameters.
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_ALPHAOP,
            kApplyParmsAlpha.Op());
        WML_DX_ERROR_CHECK(SetTextureStageState);
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_ALPHAARG1,
            kApplyParmsAlpha.Arg1());
        WML_DX_ERROR_CHECK(SetTextureStageState);
        if ( kApplyParmsAlpha.NumArgs() > 1 )
        {
            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_ALPHAARG2,kApplyParmsAlpha.Arg2());
            WML_DX_ERROR_CHECK(SetTextureStageState);
        }
        if ( kApplyParmsAlpha.NumArgs() > 2 )
        {
            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_ALPHAARG0,kApplyParmsAlpha.Arg0());
            WML_DX_ERROR_CHECK(SetTextureStageState);
        }


        // The AF_BLEND texture apply mode uses a constant color
        // for the texture blend operation.  This same constant color
        // may be used by the AF_COMBINE texture apply mode depending
        // on the combine operation.
        // NOTE: If any other texture stage also has the AM_BLEND mode or
        // the AM_COMBINE mode with ACS_CONSTANT as one of its operands,
        // then there is a resource conflict as there is only a single
        // constant texture color for use with all texture units.
        // NOTE: WM only has ColorRGB, but border color is RGBA.  Assume A=0
        // for now, but use ColorRGBA when WM2.x arrives.
        const ColorRGB& rkBlendColor = pkTexture->BlendColor();
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_TEXTUREFACTOR,
            D3DCOLOR_COLORVALUE(rkBlendColor.r,rkBlendColor.g,rkBlendColor.b,
            0.0f));
        WML_DX_ERROR_CHECK(SetRenderState);


        // Setup texture magnification, minification, and mipmap filters.
        ms_hResult = m_pqDevice->SetSamplerState(iUnit,D3DSAMP_MAGFILTER,
            ms_adwTexMagFilter[pkTexture->Filter()]);
        WML_DX_ERROR_CHECK(SetSamplerState);

        ms_hResult = m_pqDevice->SetSamplerState(iUnit,D3DSAMP_MINFILTER,
            ms_adwTexMinFilter[pkTexture->Mipmap()]);
        WML_DX_ERROR_CHECK(SetSamplerState);

        ms_hResult = m_pqDevice->SetSamplerState(iUnit,D3DSAMP_MIPFILTER,
            ms_adwTexMipFilter[pkTexture->Mipmap()]);
        WML_DX_ERROR_CHECK(SetSamplerState);


        // Check for special setup if border texture addressing mode is used.
        Texture::WrapMode eWrapMode = pkTexture->Wrap();
        if ( Texture::WM_CLAMP_BORDER_S_CLAMP_BORDER_T == eWrapMode )
        {
            // If not supported, then change to regular clamping.
            if ( !m_bCapTextureClampToBorder )
            {
                eWrapMode = Texture::WM_CLAMP_S_CLAMP_T;
            }

            // Otherwise, setup the border color.
            // WM only has ColorRGB, but border color is RGBA.  Assume A=0
            // for now, but use ColorRGBA when WM2.x arrives.
            else
            {
                const ColorRGB& rkBorderColor = pkTexture->BorderColor();
                ms_hResult = m_pqDevice->SetSamplerState(iUnit,
                    D3DSAMP_BORDERCOLOR,
                    D3DCOLOR_COLORVALUE(rkBorderColor.r,rkBorderColor.g,
                    rkBorderColor.b,0.0f));
                WML_DX_ERROR_CHECK(SetSamplerState);
            }
        }


        // Setup texture addressing mode.
        ms_hResult = m_pqDevice->SetSamplerState(iUnit,D3DSAMP_ADDRESSU,
            ms_adwTexWrapModeU[eWrapMode]);
        WML_DX_ERROR_CHECK(SetSamplerState);
        ms_hResult = m_pqDevice->SetSamplerState(iUnit,D3DSAMP_ADDRESSV,
            ms_adwTexWrapModeV[eWrapMode]);
        WML_DX_ERROR_CHECK(SetSamplerState);


        // Set up environment mapping
        // This is done through texture coordinate generation.
        // A vertex texture coordinate set must still be associated with
        // the texture unit, regardless.  That texture coordinate set
        // has the same index as the texture unit.
        switch ( pkTexture->Envmap() )
        {
        case Texture::EM_NONE:
            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU+iUnit);
            WML_DX_ERROR_CHECK(SetTextureStageState);

            ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_DISABLE);
            WML_DX_ERROR_CHECK(SetTextureStageState);
            break;

        case Texture::EM_SPHERE:
            {
                // Use the vertex normal to compute the following
                // texture coordinate transformation:
                //  u = 0.5 + Nx / 2
                //  v = 0.5 + Ny / 2

                // Bias and scale the texture so that it covers the near
                // plane.  Note that integral screen coordinates represent
                // pixel centers whereas integral texture coordinates
                // represent texel boundaries.  We also need to know the
                // dimensions of the texture being projected.
                float fOffsetX = 0.5f + (0.5f / pkTextureImage->GetWidth());
                float fOffsetY = 0.5f + (0.5f / pkTextureImage->GetHeight());
                D3DXMATRIX kMatrixTexture(
                    0.5f,0.0f,0.0f,0.0f,
                    0.0f,0.5f,0.0f,0.0f,
                    0.0f,0.0f,1.0f,0.0f,
                    fOffsetX,fOffsetY,0.0f,1.0f);
                ms_hResult = m_pqDevice->SetTransform(
                    D3DTRANSFORMSTATETYPE(D3DTS_TEXTURE0+iUnit),
                    &kMatrixTexture);
                WML_DX_ERROR_CHECK(SetTransform);

                ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                    D3DTSS_TEXCOORDINDEX,(bVertShader ? 
                    D3DTSS_TCI_PASSTHRU:D3DTSS_TCI_CAMERASPACENORMAL)+iUnit);
                WML_DX_ERROR_CHECK(SetTextureStageState);

                ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
                    D3DTSS_TEXTURETRANSFORMFLAGS,(bVertShader ?
                    D3DTTFF_DISABLE : D3DTTFF_COUNT2));
                WML_DX_ERROR_CHECK(SetTextureStageState);
            }
            break;

        case Texture::EM_IGNORE:
            // Do not alter the texure generation status.  This allows
            // complex texturing outside of texture state to exist
            // peacefully.
            break;

        default:
            // Environment map without implementation.
            assert ( false );
            break;
        }
    }


    // All texture units in series from the first through the maximum index
    // of those in use must be enabled.  This is a requirement of DirectX
    // since once a disabled texture unit is found, that unit and all those
    // following it are also disabled.  All the texture units before the
    // last one being used which are not being used (reserved or used
    // by the texture state) must be enabled to simply pass the input
    // straight through to the output.
    for (iUnit = 0; iUnit < iMaxTextureUnitInUse; iUnit++)
    {
        // Skip reserved texture units
        if ( TextureUnitRequested(iUnit) )
        {
            continue;
        }

        // Skip units defined by the texture state.
        Texture* pkTexture = pkState->Get(iUnit);
        if ( NULL != pkTexture )
        {
            continue;
        }

        // Enable texture stage (color and alpha) to output its input.
        SetTextureStageApplyPass(iUnit);

        // No automatic texture coordinate generation.
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
            D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU+iUnit);
        WML_DX_ERROR_CHECK(SetTextureStageState);
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
            D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_DISABLE);
        WML_DX_ERROR_CHECK(SetTextureStageState);

        // Unassociate the texture for this stage.
        ms_hResult = m_pqDevice->SetTexture(iUnit,NULL);
        WML_DX_ERROR_CHECK(SetTexture);
    }
    

    // Disable the first texture unit immediately following the
    // last one enabled.
    if ( (iMaxTextureUnitInUse+1) < iMaxTextureUnits )
    {
        int iUnit = iMaxTextureUnitInUse + 1;

        // Enable each texture stage (color and alpha) to output its input.
        ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_COLOROP,
            D3DTOP_DISABLE);
        WML_DX_ERROR_CHECK(SetTextureStageState);

        // Unassociate the texture for each stage.
        ms_hResult = m_pqDevice->SetTexture(iUnit,NULL);
        WML_DX_ERROR_CHECK(SetTexture);
    }
}
//----------------------------------------------------------------------------
ITexture* DxRenderer::CreateTexture (Image* pkImage)
{
    // 16-bit textures are not supported.
    switch ( pkImage->GetType() )
    {
    default:
    case Image::IT_RGBA4444:
    case Image::IT_RGBA5551:
        assert ( false );
        return NULL;
        break;
    case Image::IT_RGB888:
    case Image::IT_RGBA8888:
        break;
    }


    // Get parameters which define image header.
    int iSize = ms_aiTexSize[pkImage->GetType()];
    int iWidth = pkImage->GetWidth();
    int iHeight = pkImage->GetHeight();
    int iQuantity = iWidth*iHeight;
    int iDataBytes = iSize*iQuantity;
    int iFileBytes = iDataBytes + sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPV4HEADER);

    // reverse byte order (Windows stores BGR (lowest byte to highest byte,
    // MIF stores RGB)
    unsigned char* aucData = pkImage->GetData();
    unsigned char* aucFileInMemory = new unsigned char[iFileBytes];
    unsigned char* aucRData = aucFileInMemory + sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPV4HEADER);
    unsigned char* pucTmp = aucData;

    // window bmps are stored as top-down
    if ( iSize == 3 )
    {
        for (int i = 0; i < iQuantity; i++)
        {
            int iPixel = 3*i;
            aucRData[iPixel + 0] = aucData[iPixel + 2];
            aucRData[iPixel + 1] = aucData[iPixel + 1];
            aucRData[iPixel + 2] = aucData[iPixel + 0];
        }
    }
    else
    {
        for (int i = 0; i < iQuantity; i++)
        {
            int iPixel = 4*i;
            aucRData[iPixel + 0] = aucData[iPixel + 2];
            aucRData[iPixel + 1] = aucData[iPixel + 1];
            aucRData[iPixel + 2] = aucData[iPixel + 0];
            aucRData[iPixel + 3] = aucData[iPixel + 3];
        }
    }

    BITMAPFILEHEADER* pkFileHeader = (BITMAPFILEHEADER*)aucFileInMemory;
    pkFileHeader->bfType = 0x4d42;  // "BM"
    pkFileHeader->bfSize = iDataBytes;
    pkFileHeader->bfReserved1 = 0;
    pkFileHeader->bfReserved2 = 0;
    pkFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPV4HEADER);

    BITMAPV4HEADER* pkV4Header = (BITMAPV4HEADER*)(aucFileInMemory +
        sizeof(BITMAPFILEHEADER));
    pkV4Header->bV4Size = sizeof(BITMAPV4HEADER);
    pkV4Header->bV4Width = iWidth;
    pkV4Header->bV4Height = -iHeight;
    pkV4Header->bV4Planes = 1;
    pkV4Header->bV4BitCount = ( iSize == 3 ? 24 : 32 );
    pkV4Header->bV4V4Compression = ( iSize == 3 ? BI_RGB : BI_BITFIELDS );
    pkV4Header->bV4SizeImage = ( iSize == 3 ? 0 : iDataBytes );
    pkV4Header->bV4XPelsPerMeter = 0;
    pkV4Header->bV4YPelsPerMeter = 0;
    pkV4Header->bV4ClrUsed = 0;
    pkV4Header->bV4ClrImportant = 0;
    pkV4Header->bV4RedMask   = 0x00FF0000;
    pkV4Header->bV4GreenMask = 0x0000FF00;
    pkV4Header->bV4BlueMask  = 0x000000FF;
    pkV4Header->bV4AlphaMask = 0xFF000000;
    pkV4Header->bV4CSType = LCS_sRGB;
    pkV4Header->bV4GammaRed = 0;
    pkV4Header->bV4GammaGreen = 0;
    pkV4Header->bV4GammaBlue = 0;

    ITexture* pqTexture; 
    try
    {
        ms_hResult = D3DXCreateTextureFromFileInMemoryEx(
            m_pqDevice, 
            aucFileInMemory, 
            iFileBytes,
            0,                  // take width from file
            0,                  // take height from file
            0,                  // create full mip chain
            0,
            (D3DFORMAT)ms_adwTexFormat[pkImage->GetType()],
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,       // D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER 
            D3DX_DEFAULT,       // D3DX_FILTER_BOX
            0x00000000,         // disable opaque colorkey
            NULL,               // D3DXIMAGE_INFO
            NULL,               // no PALETTEENTRY
            &pqTexture
        );
        WML_DX_ERROR_CHECK(CreateTexture);
    }
    catch( DxException* pkDxEx )
    {
        delete[] aucFileInMemory;
        throw pkDxEx;
    }
    
    delete[] aucFileInMemory;
    return pqTexture; 
}
//----------------------------------------------------------------------------
void DxRenderer::ReleaseTexture (Texture* pkTexture)
{
    assert( pkTexture );
    if ( NULL != pkTexture )
    {
        ITexture* pqTexture;
        pkTexture->GetUserData(sizeof(ITexture*),&pqTexture);
        if ( pqTexture != NULL )
        {
            pqTexture->Release();
            pqTexture = NULL;
            pkTexture->SetUserData(sizeof(ITexture*),&pqTexture);
        }
    }
}
//----------------------------------------------------------------------------
