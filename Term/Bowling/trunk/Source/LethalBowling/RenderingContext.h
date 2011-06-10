#pragma once

namespace OpenGl
{

class RenderingContext
{
public:
    RenderingContext(HDC hdc);
    ~RenderingContext(void);

    void SetThisCurrent(HDC hdc);

private:
    void CreateContext(HDC hdc);
    void DestroyContext();
    
private:
    HGLRC handle_;
};

}
