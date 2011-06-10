#pragma once

namespace Virgin
{

class Lighting
{
public:
    Lighting(void);
    ~Lighting(void);

    void EnableLighting();
    void DisableLighting();
    void SetShadeModelFlat();
    void SetShadeModelSmooth();
};

}
