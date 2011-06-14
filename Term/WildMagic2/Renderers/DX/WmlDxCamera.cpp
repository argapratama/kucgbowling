// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include "WmlDxCamera.h"
#include "WmlDxRenderer.h"
using namespace Wml;

HRESULT DxCamera::ms_hResult = NULL;

WmlImplementRTTI(DxCamera,Camera);
WmlImplementStream(DxCamera);

//----------------------------------------------------------------------------
DxCamera::DxCamera (DxRenderer* pkRenderer, float fWidth, float fHeight)
{
    m_fWidth = fWidth;
    m_fHeight = fHeight;
    m_pkRenderer = pkRenderer;

    m_pqDevice = pkRenderer->GetDevice();
    
    OnFrustumChange();
    OnViewPortChange();
    OnFrameChange();    
}
//----------------------------------------------------------------------------
DxCamera::DxCamera ()
{
    m_fWidth = m_fHeight = 0.0f;
}
//----------------------------------------------------------------------------
void DxCamera::OnResize (int iWidth, int iHeight)
{
    Camera::OnResize(iWidth,iHeight);
    m_fWidth = (float)iWidth;
    m_fHeight = (float)iHeight;
}
//----------------------------------------------------------------------------
void DxCamera::OnFrustumChange ()
{
    Camera::OnFrustumChange();

    // WM uses right handed coordinates.  DX uses left handed coordinates.    
    // Define as if for right handed coordinates and then negate the
    // the z row.
    D3DXMATRIX& rkProjMatrix = *m_pkRenderer->GetProjMatrix();

    if ( GetUsePerspective() )
    {
        D3DXMatrixPerspectiveOffCenterRH(&rkProjMatrix,m_fFrustumL,
            m_fFrustumR,m_fFrustumB,m_fFrustumT,m_fFrustumN,m_fFrustumF);
    }
    else
    {
        D3DXMatrixOrthoOffCenterRH(&rkProjMatrix,m_fFrustumL,
            m_fFrustumR,m_fFrustumB,m_fFrustumT,m_fFrustumN,m_fFrustumF);
    }
    rkProjMatrix(2,0) = -rkProjMatrix(2,0);
    rkProjMatrix(2,1) = -rkProjMatrix(2,1);
    rkProjMatrix(2,2) = -rkProjMatrix(2,2);
    rkProjMatrix(2,3) = -rkProjMatrix(2,3);
                            
    ms_hResult = m_pqDevice->SetTransform(D3DTS_PROJECTION,&rkProjMatrix);
    WML_DX_ERROR_CHECK(SetTransform);
}
//----------------------------------------------------------------------------
void DxCamera::OnViewPortChange()
{
    Camera::OnViewPortChange();

    D3DVIEWPORT9 kViewport;
    kViewport.X = (DWORD)(m_fPortL*m_fWidth);
    kViewport.Y = (DWORD)(m_fPortB*m_fHeight);
    kViewport.Width = (DWORD)((m_fPortR - m_fPortL)*m_fWidth);
    kViewport.Height = (DWORD)((m_fPortT - m_fPortB)*m_fHeight);
    kViewport.MinZ = 0.0f;
    kViewport.MaxZ = 1.0f;

    ms_hResult = m_pqDevice->SetViewport(&kViewport);
    WML_DX_ERROR_CHECK(SetViewport);
}
//----------------------------------------------------------------------------
void DxCamera::OnFrameChange()
{
    Camera::OnFrameChange();

    // WM uses right handed coordinates.  DX uses left handed coordinates.
    // Define as if for right handed coordinates and then negate the
    // the z column.
    D3DXMATRIX& rkViewMatrix = *m_pkRenderer->GetViewMatrix();

    D3DXVECTOR3 kEye(m_kLocation.X(),m_kLocation.Y(),m_kLocation.Z());
    D3DXVECTOR3 kAt(m_kLocation.X()+m_kDirection.X(),
        m_kLocation.Y()+m_kDirection.Y(),m_kLocation.Z()+m_kDirection.Z());
    D3DXVECTOR3 kUp(m_kUp.X(),m_kUp.Y(),m_kUp.Z());
    D3DXMatrixLookAtRH(&rkViewMatrix,&kEye,&kAt,&kUp);
    rkViewMatrix(0,2) = -rkViewMatrix(0,2);
    rkViewMatrix(1,2) = -rkViewMatrix(1,2);
    rkViewMatrix(2,2) = -rkViewMatrix(2,2);
    rkViewMatrix(3,2) = -rkViewMatrix(3,2);

    ms_hResult = m_pqDevice->SetTransform(D3DTS_VIEW,&rkViewMatrix);
    WML_DX_ERROR_CHECK(SetTransform);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
Object* DxCamera::Factory (Stream& rkStream)
{
    DxCamera* pkObject = new DxCamera;
    Stream::Link* pkLink = new Stream::Link(pkObject);
    pkObject->Load(rkStream,pkLink);
    return pkObject;
}
//----------------------------------------------------------------------------
void DxCamera::Load (Stream& rkStream, Stream::Link* pkLink)
{
    Camera::Load(rkStream,pkLink);
    StreamRead(rkStream,m_fWidth);
    StreamRead(rkStream,m_fHeight);
}
//----------------------------------------------------------------------------
void DxCamera::Link (Stream& rkStream, Stream::Link* pkLink)
{
    Camera::Link(rkStream,pkLink);
}
//----------------------------------------------------------------------------
bool DxCamera::Register (Stream& rkStream)
{
    return Camera::Register(rkStream);
}
//----------------------------------------------------------------------------
void DxCamera::Save (Stream& rkStream)
{
    Camera::Save(rkStream);

    // native data
    StreamWrite(rkStream,m_fWidth);
    StreamWrite(rkStream,m_fHeight);
}
//----------------------------------------------------------------------------
StringTree* DxCamera::SaveStrings ()
{
    // TO DO.  Finish implementation.
    StringTree* pkTree = new StringTree(1,0,1,0);
    pkTree->SetString(0,MakeString(&ms_kRTTI,GetName()));
    pkTree->SetChild(0,Camera::SaveStrings());
    return pkTree;
}
//----------------------------------------------------------------------------
int DxCamera::GetMemoryUsed () const
{
    int iBaseSize = sizeof(DxCamera) - sizeof(Camera);
    int iTotalSize = iBaseSize + Camera::GetMemoryUsed();
    return iTotalSize;
}
//----------------------------------------------------------------------------
int DxCamera::GetDiskUsed () const
{
    return Camera::GetDiskUsed() +
        sizeof(m_fWidth) +
        sizeof(m_fHeight);
}
//----------------------------------------------------------------------------
