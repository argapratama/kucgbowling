#pragma once

#include "PrimitiveType.h"

namespace OpenGl
{

class PixelFormat
{
public:
    PixelFormat(uint16 version, uint32 flags, byte pixelType, byte colorBits, byte redBits, byte redShift, byte greenBits,
        byte greenShift, byte blueBits, byte blueShift, byte alphaBits, byte alphaShift, byte accumBits, byte accumRedBits,
        byte accumGreenBits, byte accumBlueBits, byte accumAlphaBits, byte depthBits, byte stencilBits, byte auxBuffers,
        byte layerType, uint32 layerMask, uint32 visibleMask, uint32 damageMask);

    ~PixelFormat(void);

    const PIXELFORMATDESCRIPTOR* GetPtr() const;

private:
    PIXELFORMATDESCRIPTOR description_;
};

}
