#include "RenderingContext.h"
#include "OpenGlException.h"
#include <gl/GL.h>

using Virgin::OpenGlException;

namespace OpenGl
{

RenderingContext::RenderingContext(HDC hdc)
    : handle_(nullptr)
{
    CreateContext(hdc);
}

RenderingContext::~RenderingContext(void)
{
    if(handle_ != nullptr)
    {
    }
}

void RenderingContext::SetThisCurrent(HDC hdc)
{
    if(!wglMakeCurrent(hdc, handle_))
    {
        throw OpenGlException(L"Can't activate the GL rendering context");
    }
}

void RenderingContext::CreateContext(HDC hdc)
{
    if((handle_ = wglCreateContext(hdc)) == nullptr)
    {
        throw OpenGlException(L"Can't create a GL rendering context");
    }
}

void RenderingContext::DestroyContext()
{
    if(handle_ != nullptr)
    {
        if(!wglMakeCurrent(nullptr, nullptr))
        {
            throw OpenGlException(L"Release of DC and RC failed");
        }

        if(!wglDeleteContext(handle_))
        {
            throw OpenGlException(L"Release Rendering Context failed");
        }

        handle_ = nullptr;
    }
}

}
