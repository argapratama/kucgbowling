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
#include "WmlCommand.h"
#include "WmlImage.h"
using namespace Wml;

//----------------------------------------------------------------------------
int main (int iArgQuantity, char** apcArgument)
{
    if ( iArgQuantity <= 1 )
        return -1;

    Command* pkCommand = new Command(iArgQuantity,apcArgument);
    if ( !pkCommand )
        return -2;

    char* acInputFile = NULL;
    pkCommand->Filename(acInputFile);
    if ( !acInputFile )
    {
        delete pkCommand;
        return -3;
    }

    char* acOutputFile = NULL;
    pkCommand->Filename(acOutputFile);
    if ( !acOutputFile )
    {
        delete pkCommand;
        delete[] acInputFile;
        return -4;
    }

    HBITMAP hImage = (HBITMAP) LoadImage(NULL,acInputFile,IMAGE_BITMAP,0,0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if ( !hImage )
    {
        delete pkCommand;
        delete[] acInputFile;
        delete[] acOutputFile;
        return -5;
    }

    DIBSECTION dibSection;
    GetObject(hImage,sizeof(DIBSECTION),&dibSection);

    int iWidth = dibSection.dsBm.bmWidth;
    int iHeight = dibSection.dsBm.bmHeight;
    int iQuantity = dibSection.dsBm.bmWidth*dibSection.dsBm.bmHeight;
    if ( dibSection.dsBm.bmBitsPixel != 24 )
    {
        delete pkCommand;
        delete[] acInputFile;
        delete[] acOutputFile;
        return -6;
    }

    // Windows BMP stores BGR, need to invert to RGB.
    unsigned char* aucSrc = (unsigned char*) dibSection.dsBm.bmBits;
    unsigned char* aucDst = new unsigned char[3*iQuantity];
    for (int i = 0, i0 = 0, i1 = 1, i2 = 2; i < iQuantity; i++)
    {
        aucDst[i0] = aucSrc[i2];
        aucDst[i1] = aucSrc[i1];
        aucDst[i2] = aucSrc[i0];
        i0 += 3;
        i1 += 3;
        i2 += 3;
    }

    DeleteObject(hImage);

    Image* pkImage = new Image(Image::IT_RGB888,iWidth,iHeight,aucDst);

    assert( pkImage );
    if ( !pkImage )
    {
        delete pkCommand;
        delete[] acInputFile;
        delete[] acOutputFile;
        delete[] aucDst;
        return -7;
    }

    if ( !pkImage->Save(acOutputFile) )
    {
        delete pkCommand;
        delete[] acInputFile;
        delete[] acOutputFile;
        delete pkImage;
        return -8;
    }

    delete pkCommand;
    delete[] acInputFile;
    delete[] acOutputFile;
    delete pkImage;

    return 0;
}
//----------------------------------------------------------------------------
