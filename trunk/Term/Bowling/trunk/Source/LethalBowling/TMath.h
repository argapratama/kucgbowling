#pragma once

#include <math.h>

namespace Virgin
{
class Math
{
public:
    static float Epsilon;
    static double PI;
    static double E;

public:
    template<typename T>
    static T Abs(T value)
    {
        return abs(value);
    }

    template<typename T>
    static T Sqrt(T value)
    {
        return sqrt(value);
    }

    //
    // »ï°¢ ÇÔ¼ö
    //

    template<typename T>
    static T Sin(T value)
    {
        return sin(value);
    }

    template<typename T>
    static T Asin(T value)
    {
        return asin(value);
    }

    template<typename T>
    static T Cos(T value)
    {
        return cos(value);
    }

    template<typename T>
    static T Acos(T value)
    {
        return acos(value);
    }

    template<typename T>
    static T Tan(T value)
    {
        return tan(value);
    }

    template<typename T>
    static T Atan(T value)
    {
        return atan(value);
    }

    template<typename T>
    static T Atan2(T valueY, T valueX)
    {
        return atan2(valueY, valueX);
    }
    
    static double DegreesToRadians(double degrees)
    {
        return degrees / 57.29578;
    }

    static double RadiansToDegrees(double radians)
    {
        return radians * 57.29578;
    }
};

}
