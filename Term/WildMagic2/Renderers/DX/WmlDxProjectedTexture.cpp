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
#include "WmlProjectedTexture.h"
#include "WmlDxCamera.h"
using namespace Wml;

//----------------------------------------------------------------------------
void DxRenderer::Draw (const ProjectedTexture& rkPTexture)
{
    float fNear, fFar, fLeft, fRight, fTop, fBottom;
    D3DXMATRIX kMatrixViewCamera;
    D3DXMATRIX kMatrixInverseViewCamera;
    D3DXMATRIX kMatrixViewProjector;
    D3DXMATRIX kMatrixProjectionProjector;
    D3DXMATRIX kMatTmp1, kMatTmp2;
    D3DXMATRIX kMatrixTextureProjector;

    // If multitexturing is not supported, then we cannot render a
    // projected texture onto the objects.  But render the objects anyway.
    if ( !m_bCapMultitexture )
    {
        Renderer::Draw(rkPTexture.GetObjects());
        return;
    }


    // Reserve an available texture unit, but use one on at the end of the
    // sequence to allow room for the model if it needs to use any
    // texture units prior to the ProjectedTexture texture.  If one is
    // not available, then we cannot render a projected texture onto
    // the objects.  But render the objects anyway.
    int iUnit = RequestTextureUnit();
    if ( iUnit < 0 )
    {
        Renderer::Draw(rkPTexture.GetObjects());
        return;
    }


    // Fill the texture state object and bind it.
    Texture* pkTexture = rkPTexture.GetTexture();
    TextureState* pkTS = rkPTexture.GetTextureState();
    pkTS->Set(iUnit,pkTexture);
    SetTextureState(pkTS);
    pkTS->Remove(iUnit);


    // Setup the inverse for the current camera viewing transform. - 
    // Texture coordinates will be obtained from camera space position,
    // but that camera viewing transform needs to be undone to get
    // back to world coordinates.
    ms_hResult = m_pqDevice->GetTransform(D3DTS_VIEW,&kMatrixViewCamera); 
    WML_DX_ERROR_CHECK(GetTransform);
    D3DXMatrixInverse(&kMatrixInverseViewCamera,NULL,&kMatrixViewCamera);
    

    // Setup viewing transform for the projector.
    // Setup a lookat matrix using the projected texture camera
    // viewpoint and view direction.
    const Vector3f& rkCameraLoc = rkPTexture.GetCamera()->GetLocation();
    const Vector3f& rkCameraDir = rkPTexture.GetCamera()->GetDirection();
    const Vector3f& rkCameraUp = rkPTexture.GetCamera()->GetUp();
    const Vector3f& rkCameraLookAt = rkCameraLoc + rkCameraDir;
    D3DXVECTOR3 kProjectorEye(rkCameraLoc.X(),rkCameraLoc.Y(),
        rkCameraLoc.Z());
    D3DXVECTOR3 kProjectorUp(rkCameraUp.X(),rkCameraUp.Y(),rkCameraUp.Z());
    D3DXVECTOR3 kProjectorLookAt(rkCameraLookAt.X(),rkCameraLookAt.Y(),
        rkCameraLookAt.Z());
    D3DXMatrixLookAtRH(&kMatrixViewProjector,&kProjectorEye,&kProjectorLookAt,
        &kProjectorUp);


    // Setup the projection transform for the projector - ProjectionProjector.
    // Setup a right-handed off-center perspective projection matrix using
    // the projected texture camera frustrum.
    rkPTexture.GetCamera()->GetFrustum(fNear,fFar,fLeft,fRight,fTop,fBottom);
    D3DXMatrixPerspectiveOffCenterRH(&kMatrixProjectionProjector,fLeft,fRight,
        fBottom,fTop,fNear,fFar);


    // Bias and scale the texture so that it covers the near plane.
    // Note that integral screen coordinates represent pixel centers
    // whereas integral texture coordinates represent texel boundaries.
    // We also need to know the dimensions of the texture being projected.
    Image* pkTextureImage = pkTexture->GetImage();
    float fOffsetX = 0.5f + (0.5f / pkTextureImage->GetWidth());
    float fOffsetY = 0.5f + (0.5f / pkTextureImage->GetHeight());
    D3DXMATRIX kMatrixScaleBiasTexture(
        0.5f,0.0f,0.0f,0.0f,
        0.0f,0.5f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        fOffsetX,fOffsetY,0.0f,1.0f);


    // Create the projected texture transform by combining the
    // following transformations in the given order (left to right):
    //  . kMatrixInverseViewCamera
    //  . kMatrixViewProjector
    //  . kMatrixProjectionProjector
    //  . kMatrixScaleBiasTexture
    D3DXMatrixMultiply(&kMatrixTextureProjector,
        D3DXMatrixMultiply(&kMatTmp1,&kMatrixInverseViewCamera,
            &kMatrixViewProjector),
        D3DXMatrixMultiply(&kMatTmp2,&kMatrixProjectionProjector,
            &kMatrixScaleBiasTexture));
    ms_hResult = m_pqDevice->SetTransform(
        D3DTRANSFORMSTATETYPE(D3DTS_TEXTURE0+iUnit),&kMatrixTextureProjector);
    WML_DX_ERROR_CHECK(SetTransform);


    // Use the texture coordinate set defined for this stage, but the
    // texture coordinates for this stage are based on the transformed
    // vertex position.
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,D3DTSS_TEXCOORDINDEX,
        D3DTSS_TCI_CAMERASPACEPOSITION|iUnit);
    WML_DX_ERROR_CHECK(SetTextureStageState);


    // All four dimenions of the texture transform are processed.
    // The coordinates are then dealt with as a projected texture.
    ms_hResult = m_pqDevice->SetTextureStageState(iUnit,
        D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT4|D3DTTFF_PROJECTED);
    WML_DX_ERROR_CHECK(SetTextureStageState);


    // Draw the objects as usual
    Renderer::Draw(rkPTexture.GetObjects());

    // No longer need the reserved texture unit.
    ReleaseTextureUnit(iUnit);
}
//----------------------------------------------------------------------------
