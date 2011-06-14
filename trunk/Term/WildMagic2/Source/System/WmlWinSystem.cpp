// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include <windows.h>
#include "WmlSystem.h"
using namespace Wml;

//----------------------------------------------------------------------------
void System::EndianCopy (int iSize, const void* pvSrc, void* pvDst)
{
    memcpy(pvDst,pvSrc,iSize);
}
//----------------------------------------------------------------------------
void System::EndianCopy (int iSize, int iQuantity, const void* pvSrc,
    void* pvDst)
{
    memcpy(pvDst,pvSrc,iSize*iQuantity);
}
//----------------------------------------------------------------------------
double System::GetTime ()
{
    // 64-bit quantities
    LARGE_INTEGER iFrequency, iCounter;

    QueryPerformanceFrequency(&iFrequency);
    QueryPerformanceCounter(&iCounter);
    return ((double)iCounter.QuadPart)/((double)iFrequency.QuadPart);
}
//----------------------------------------------------------------------------
