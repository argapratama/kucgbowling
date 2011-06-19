#pragma once

namespace Virgin
{

struct Color
{
public:
    Color();
    Color(float r, float g, float b, float a);
    ~Color();

public:
    float R;
    float G;
    float B;
    float A;
};

}
