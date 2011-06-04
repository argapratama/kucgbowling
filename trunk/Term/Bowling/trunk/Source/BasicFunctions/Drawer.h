#pragma once

namespace Virgin
{

class Drawer
{
public:
    Drawer(void);
    ~Drawer(void);

    void TranslateTo(float x, float y, float z);
    void TranslateMore(float x, float y, float z);

private:
    float translateX_;
    float translateY_;
    float translateZ_;

};

}
