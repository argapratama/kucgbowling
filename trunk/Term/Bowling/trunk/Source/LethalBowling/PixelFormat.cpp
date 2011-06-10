#include "PixelFormat.h"

namespace OpenGl
{

PixelFormat::PixelFormat(uint16 version, uint32 flags, byte pixelType, byte colorBits, byte redBits, byte redShift, byte greenBits,
        byte greenShift, byte blueBits, byte blueShift, byte alphaBits, byte alphaShift, byte accumBits, byte accumRedBits,
        byte accumGreenBits, byte accumBlueBits, byte accumAlphaBits, byte depthBits, byte stencilBits, byte auxBuffers,
        byte layerType, uint32 layerMask, uint32 visibleMask, uint32 damageMask)
{
   /* description_.(sizeof(description_), version, flags, pixelType, colorBits, redBits, redShift, greenBits, greenShift,
    blueBits, blueShift, alphaBits, alphaShift, accumBits, accumRedBits, accumGreenBits, accumBlueBits, accumAlphaBits,
    depthBits, stencilBits, auxBuffers, layerType, 0, layerMask, visibleMask, damageMask)*/
    
    description_.nSize = sizeof(description_);
    description_.nVersion = version;
    description_.dwFlags = flags;
    description_.iPixelType = pixelType;
    description_.cColorBits = colorBits;
    description_.cRedBits = redBits;
    description_.cRedShift = redShift;
    description_.cGreenBits = greenBits;
    description_.cGreenShift = greenShift;
    description_.cBlueBits = blueBits;
    description_.cBlueShift = blueShift;
    description_.cAlphaBits = alphaBits;
    description_.cAlphaShift = alphaShift;
    description_.cAccumBits = accumBits;
    description_.cAccumRedBits = accumRedBits;
    description_.cAccumGreenBits = accumGreenBits;
    description_.cAccumBlueBits = accumBlueBits;
    description_.cAccumAlphaBits = accumAlphaBits;
    description_.cDepthBits = depthBits;
    description_.cStencilBits = stencilBits;
    description_.cAuxBuffers = auxBuffers;
    description_.iLayerType = layerType;
    description_.bReserved = 0;
    description_.dwLayerMask = layerMask;
    description_.dwVisibleMask = visibleMask;
    description_.dwDamageMask = damageMask;
}

PixelFormat::~PixelFormat(void)
{
}

const PIXELFORMATDESCRIPTOR* PixelFormat::GetPtr() const
{
    return &description_;
}

}
