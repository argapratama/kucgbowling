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

#include <fstream>
using namespace std;

//----------------------------------------------------------------------------
static void SaveImage (const char* acFilename, int iWidth, int iHeight,
    unsigned char* aucData, int iSize)
{
    ofstream kOStr(acFilename,ios::out|ios::binary);
    if ( !kOStr )
        return;

    int iQuantity = iWidth*iHeight;
    int iDataBytes = iSize*iQuantity;

    // reverse byte order (Windows stores BGR (lowest byte to highest byte,
    // MIF stores RGB)
    unsigned char* aucRData = new unsigned char[iDataBytes];
    unsigned char* pucTmp = aucData;
    int i, i0, i1, i2, i3;

    if ( iSize == 3 )
    {
        for (i = 0, i0 = 0, i1 = 1, i2 = 2; i < iQuantity; i++)
        {
            aucRData[i0] = aucData[i2];
            aucRData[i1] = aucData[i1];
            aucRData[i2] = aucData[i0];
            i0 += 3;
            i1 += 3;
            i2 += 3;
        }
    }
    else
    {
        for (i = 0, i0 = 0, i1 = 1, i2 = 2, i3 = 3; i < iQuantity; i++)
        {
            aucRData[i0] = aucData[i2];
            aucRData[i1] = aucData[i1];
            aucRData[i2] = aucData[i0];
            aucRData[i3] = aucData[i3];
            i0 += 4;
            i1 += 4;
            i2 += 4;
            i3 += 4;
        }
    }

    BITMAPFILEHEADER kFileHeader;
    kFileHeader.bfType = 0x4d42;  // "BM"
    kFileHeader.bfSize =
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER) +
        iDataBytes;
    kFileHeader.bfReserved1 = 0;
    kFileHeader.bfReserved2 = 0;
    kFileHeader.bfOffBits =
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER);

    BITMAPINFOHEADER kInfoHeader;
    kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    kInfoHeader.biWidth = iWidth;
    kInfoHeader.biHeight = iHeight;
    kInfoHeader.biPlanes = 1;
    kInfoHeader.biBitCount = ( iSize == 3 ? 24 : 32 );
    kInfoHeader.biCompression = BI_RGB;
    kInfoHeader.biSizeImage = 0;
    kInfoHeader.biXPelsPerMeter = 0;
    kInfoHeader.biYPelsPerMeter = 0;
    kInfoHeader.biClrUsed = 0;
    kInfoHeader.biClrImportant = 0;

    kOStr.write((const char*)&kFileHeader,sizeof(BITMAPFILEHEADER));
    kOStr.write((const char*)&kInfoHeader,sizeof(BITMAPINFOHEADER));
    kOStr.write((const char*)aucRData,iDataBytes*sizeof(unsigned char));

    kOStr.close();

    delete[] aucRData;
}
//----------------------------------------------------------------------------
int main (int iArgQuantity, char** apcArgument)
{
    if ( iArgQuantity <= 1 )
        return -1;

    Command* pkCommand = new Command(iArgQuantity,apcArgument);
    if ( !pkCommand )
        return -2;

    char* acInputFile;
    pkCommand->Filename(acInputFile);
    if ( !acInputFile )
    {
        delete pkCommand;
        return -3;
    }

    char* acOutputFile;
    pkCommand->Filename(acOutputFile);
    if ( !acOutputFile )
    {
        delete pkCommand;
        delete[] acInputFile;
        return -4;
    }

    Image* pkImage = Image::Load(acInputFile);
    int iSize;
    switch ( pkImage->GetType() )
    {
    case Image::IT_RGB888:
        iSize = 3;
        break;
    case Image::IT_RGBA8888:
        iSize = 4;
        break;
    default:
        delete pkCommand;
        delete[] acInputFile;
        delete[] acOutputFile;
        delete pkImage;
        return -5;
    }

    SaveImage(acOutputFile,pkImage->GetWidth(),pkImage->GetHeight(),
        pkImage->GetData(),iSize);

    delete pkCommand;
    delete[] acInputFile;
    delete[] acOutputFile;
    delete pkImage;
    return 0;
}
//----------------------------------------------------------------------------
