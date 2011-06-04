#include "Light.h"
#include <gl/GL.h>

namespace Virgin
{

Light::Light(void)
{
    //float ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    //float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    //float position[] = { 0.0, 0.0, 2.0, 1.0 };

    //glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, LightAmbient);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, LightAmbient);
    //glLightfv(GL_LIGHT1, GL_POSITION, LightAmbient);
    //
    //glEnable(GL_LIGHT1);

    
}

Light::~Light(void)
{
}

void Light::SetAmbient(float r, float g, float b)
{
    ambient_.R = r;
    ambient_.G = g;
    ambient_.B = b;
    ambient_.A = 1.0;

    float values[] = { r, g, b, 1.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, values);
}

void Light::SetDiffuse(float r, float g, float b)
{
    diffuse_.R = r;
    diffuse_.G = g;
    diffuse_.B = b;
    diffuse_.A = 1.0;

    float values[] = { r, g, b, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, values);
}

void Light::SetSpecular(float r, float g, float b)
{
    specular_.R = r;
    specular_.G = g;
    specular_.B = b;
    specular_.A = 1.0;

    float values[] = { r, g, b, 1.0 };
    glLightfv(GL_LIGHT1, GL_SPECULAR, values);
}

void Light::MoveTo(float x, float y, float z)
{
    location_.X = x;
    location_.Y = y;
    location_.Z = z;

    float values[] = { x, y, z, 0.0/* 1: Point Light 0: Directional Light */ };
    glLightfv(GL_LIGHT1, GL_POSITION, values);
}

void Light::Enable()
{
    glEnable(GL_LIGHT1);
}

void Light::Disable()
{
    glDisable(GL_LIGHT1);
}

}
