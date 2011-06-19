#pragma once

namespace Virgin
{

class PointD
{
public:
    PointD()
        : X(0), Y(0)
    {}

    int X;
    int Y;
};

class PointF
{
public:
    PointF()
        : X(0.0f), Y(0.0f)
    {
    }

    float X;
    float Y;
};

}
