// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifndef WMLDXEXCEPTION_H
#define WMLDXEXCEPTION_H

#include "WmlDxUtility.h"
#include "WmlRendererLibType.h"

namespace Wml
{

class WML_RENDERER_ITEM DxException
{
public:
    DxException (const char* acFile, unsigned int uiLine,
        const char* acMessage, HRESULT hResult);

    ~DxException ();
    
    void Show (BOOL bShowMessageBox = FALSE);

private:
    char* m_acFile;
    unsigned int m_uiLine;
    char* m_acMessage;
    HRESULT m_hResult;
};

// This macro assumes the existence of Wml::DxRenderer::ms_hResult and should
// only be called in Wml::DxRendererer functions.  The message is usually the
// name of the offending function and should be a single identifier (no
// blanks, commas, etc.).
#define WML_DX_ERROR_CHECK(message) \
{ \
    if ( FAILED(ms_hResult) ) \
    { \
        throw new DxException(__FILE__,__LINE__,#message,ms_hResult); \
    } \
}

// Macro for throwing exceptions when the first parameter is NULL.
#define WML_DX_ERROR_CHECK_NULL(value,message) \
{ \
    if ( !value  ) \
    { \
        throw new DxException(__FILE__,__LINE__,#message,NULL); \
    } \
}

}

#endif
