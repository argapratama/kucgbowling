#include "StdAfx.h"
#include "PixelFormatController.h"
#include "PixelFormat.h"
#include "OpenGlException.h"

using Virgin::OpenGlException;

namespace OpenGl
{

PixelFormatController::PixelFormatController(   )
{
}


PixelFormatController::~PixelFormatController(void)
{
}

void PixelFormatController::SetPixelFormat(HDC hdc, const PixelFormat& format)
{
    int pixelFormat;
    if((pixelFormat = ChoosePixelFormat(hdc, format.GetPtr())) == 0)
    {
        throw OpenGlException(L"Can't find a suitable PixelFormat");
    }

    if(!::SetPixelFormat(hdc, pixelFormat, format.GetPtr()))
    {
        throw OpenGlException(L"Can't set the PixelFormat");
    }
}

}
