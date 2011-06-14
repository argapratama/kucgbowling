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
#include "WmlAmbientLight.h"
#include "WmlDirectionalLight.h"
#include "WmlPointLight.h"
#include "WmlSpotLight.h"
using namespace Wml;

static float gs_fSqrtMaxReal = Mathf::Sqrt(Mathf::MAX_REAL);

//----------------------------------------------------------------------------
void DxRenderer::SetLightState (LightState* pkState)
{
    int iQuantity = pkState->GetQuantity();

    if ( m_eOverrideLightingMode != OLM_DISABLE && iQuantity > 0 )
    {
        // if all lights are off, nothing to do
        int i;
        Light* pkLight;
        for (i = 0; i < iQuantity; i++)
        {
            pkLight = pkState->Get(i);
            if ( pkLight->On() )
                break;
        }
        if ( i == iQuantity )
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
            WML_DX_ERROR_CHECK(SetRenderState);
            return;
        }

        // At least one light source is on, so enable the use of lighting.
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
        WML_DX_ERROR_CHECK(SetRenderState);


        // This is enabled if any of the active lights need it.
        bool bSpecularEnable = false;

        for (i = 0; i < iQuantity; i++)
        {
            pkLight = pkState->Get(i);

            // Disable this light source.
            if ( !pkLight->On() )
            {
                ms_hResult = m_pqDevice->LightEnable(i,FALSE);
                WML_DX_ERROR_CHECK(LightEnable);
                continue;
            }


            // Enable the light source.
            ms_hResult = m_pqDevice->LightEnable(i,TRUE);
            WML_DX_ERROR_CHECK(LightEnable);


            // If a light source wants specular after texture, then enable
            // specular highlighting because DirectX automatically provides
            // specular after texture.
            if ( pkLight->SpecularAfterTexture() )
            {
                bSpecularEnable = true;
            }


            D3DLIGHT9 kD3DLight;
            kD3DLight.Falloff = 1.0f;
            kD3DLight.Theta = 0.0f;
            kD3DLight.Phi = 0.0f;
            kD3DLight.Range = gs_fSqrtMaxReal;
            ColorRGB kTmpColor;

            // ambient
            kD3DLight.Ambient.a = 1.0f;
            if ( OLM_ONLY_SPECULAR == m_eOverrideLightingMode )
            {
                kD3DLight.Ambient.r = 0.0f;
                kD3DLight.Ambient.g = 0.0f;
                kD3DLight.Ambient.b = 0.0f;
            }
            else
            {
                kTmpColor = pkLight->Intensity()*pkLight->Ambient();
                kTmpColor.Clamp();
                kD3DLight.Ambient.r = kTmpColor.r;
                kD3DLight.Ambient.g = kTmpColor.g;
                kD3DLight.Ambient.b = kTmpColor.b;
            }

            // diffuse
            kD3DLight.Diffuse.a = 1.0f;
            if ( OLM_ONLY_SPECULAR == m_eOverrideLightingMode ||
                Light::LT_AMBIENT == pkLight->GetType() )
            {
                kD3DLight.Diffuse.r = 0.0f;
                kD3DLight.Diffuse.g = 0.0f;
                kD3DLight.Diffuse.b = 0.0f;
            }
            else
            {
                kTmpColor = pkLight->Intensity()*pkLight->Diffuse();
                kTmpColor.Clamp();
                kD3DLight.Diffuse.r = kTmpColor.r;
                kD3DLight.Diffuse.g = kTmpColor.g;
                kD3DLight.Diffuse.b = kTmpColor.b;
            }

            // specular
            kD3DLight.Specular.a = 1.0f;
            if ( OLM_ONLY_NON_SPECULAR == m_eOverrideLightingMode ||
                Light::LT_AMBIENT == pkLight->GetType() )
            {
                kD3DLight.Specular.r = 0.0f;
                kD3DLight.Specular.g = 0.0f;
                kD3DLight.Specular.b = 0.0f;
            }
            else
            {
                kTmpColor = pkLight->Intensity()*pkLight->Specular();
                kTmpColor.Clamp();
                kD3DLight.Specular.r = kTmpColor.r;
                kD3DLight.Specular.g = kTmpColor.g;
                kD3DLight.Specular.b = kTmpColor.b;

                // DirectX only has an option to enable specular highlighting
                // or not.  If enabled, specular automatically occurs after
                // texture processing but before alpha blending.
                if ( ( kD3DLight.Specular.r > 0.0f ) ||
                     ( kD3DLight.Specular.g > 0.0f ) ||
                     ( kD3DLight.Specular.b > 0.0f ) )
                {
                    bSpecularEnable = true;
                }
            }

            if ( pkLight->Attenuate() )
            {
                kD3DLight.Attenuation0 = pkLight->Constant();
                kD3DLight.Attenuation1 = pkLight->Linear();
                kD3DLight.Attenuation2 = pkLight->Quadratic();
            }
            else
            {
                kD3DLight.Attenuation0 = 1.0f;
                kD3DLight.Attenuation1 = 0.0f;
                kD3DLight.Attenuation2 = 0.0f;
            }


            switch ( pkLight->GetType() )
            {
            case Light::LT_AMBIENT:
            {
                // These parameters are probably not necessary since the
                // diffuse and specular components of the light are black.
                // The values are the same defaults that are used in the
                // OpenGL renderer.
                kD3DLight.Type = D3DLIGHT_DIRECTIONAL;
                kD3DLight.Direction.x = 0.0f;
                kD3DLight.Direction.y = 0.0f;
                kD3DLight.Direction.z = 1.0f;
                break;
            }
            case Light::LT_DIRECTIONAL:
            { 
                kD3DLight.Type = D3DLIGHT_DIRECTIONAL;
                DirectionalLight* pkDL = (DirectionalLight*)pkLight;
                kD3DLight.Direction.x = pkDL->Direction().X();
                kD3DLight.Direction.y = pkDL->Direction().Y();
                kD3DLight.Direction.z = pkDL->Direction().Z();
                break;
            }
            case Light::LT_POINT:
            {
                kD3DLight.Type = D3DLIGHT_POINT;
                PointLight* pkPL = (PointLight*)pkLight;
                kD3DLight.Position.x = pkPL->Location().X();
                kD3DLight.Position.y = pkPL->Location().Y();
                kD3DLight.Position.z = pkPL->Location().Z();
                break;
            }
            case Light::LT_SPOT:
            {
                kD3DLight.Type = D3DLIGHT_SPOT;
                SpotLight* pkSL = (SpotLight*)pkLight;
                kD3DLight.Position.x = pkSL->Location().X();
                kD3DLight.Position.y = pkSL->Location().Y();
                kD3DLight.Position.z = pkSL->Location().Z();
                kD3DLight.Direction.x = pkSL->Direction().X();
                kD3DLight.Direction.y = pkSL->Direction().Y();
                kD3DLight.Direction.z = pkSL->Direction().Z();
                kD3DLight.Phi = 2.1f*pkSL->GetAngle();
                kD3DLight.Theta = 2.0f*pkSL->GetAngle();
                kD3DLight.Falloff = pkSL->Exponent();  
                break;
            }
            }

            ms_hResult = m_pqDevice->SetLight(i,&kD3DLight);
            WML_DX_ERROR_CHECK(SetLight);
        }


        // Disable the remainder of the lights.
        for (i = iQuantity; i < LightState::MAX_LIGHTS; i++)
        {
            ms_hResult = m_pqDevice->LightEnable(i,FALSE);
            WML_DX_ERROR_CHECK(LightEnable);
        }


        // No global ambient scene color
        float afAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_AMBIENT,
            D3DCOLOR_COLORVALUE(afAmbient[0],afAmbient[1],afAmbient[2],
            afAmbient[3]));
        WML_DX_ERROR_CHECK(SetRenderState);


        // Specular after texture is enabled if specular highlighting
        // is enabled.
        if ( bSpecularEnable )
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_SPECULARENABLE,
                TRUE);
            WML_DX_ERROR_CHECK(SetRenderState);

            // Use orthogonal specular highlights, i.e., instruct system
            // to act as though the viewpoint is infinitely distant on the
            // z-axis.  This is as opposed to using camera-relative
            // specular highlights.  Note that orthogonal specular highlights
            // should be used when orthogonal projection is used.
            // NOTE: The camera must have been configured so that the
            // the eye coordinates are left-handed!
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_LOCALVIEWER,FALSE);
            WML_DX_ERROR_CHECK(SetRenderState);
        }
        else
        {
            ms_hResult = m_pqDevice->SetRenderState(D3DRS_SPECULARENABLE,
                FALSE);
            WML_DX_ERROR_CHECK(SetRenderState);
        }
    }
    else
    {
        ms_hResult = m_pqDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
        WML_DX_ERROR_CHECK(SetRenderState);
    }
}
//----------------------------------------------------------------------------
