// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include "WmlDxException.h"
using namespace Wml;

//----------------------------------------------------------------------------
DxException::DxException (const char* acFile, unsigned int uiLine,
    const char* acMessage, HRESULT hResult)
{
    m_acFile = new char[strlen(acFile)+1];
    strcpy(m_acFile,acFile);

    m_uiLine = uiLine;
    m_hResult = hResult;

    m_acMessage = new char[strlen(acMessage)+strlen("\n")+1];
    strcpy(m_acMessage,"\n");
    strcat(m_acMessage,acMessage);
}
//----------------------------------------------------------------------------
DxException::~DxException ()
{
    delete[] m_acFile;
    delete[] m_acMessage;
}
//----------------------------------------------------------------------------
void DxException::Show (BOOL bShowMessageBox)
{
    DXTrace(m_acFile,m_uiLine,m_hResult,m_acMessage,bShowMessageBox);
}
//----------------------------------------------------------------------------
