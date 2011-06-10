#pragma once

namespace OpenGl
{

class PixelFormat;

class PixelFormatController
{
public:
    PixelFormatController();
    ~PixelFormatController(void);

    void SetPixelFormat(HDC hdc, const PixelFormat& format);
};

}
