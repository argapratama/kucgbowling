#include "Lighting.h"
#include <gl/GL.h>

namespace Virgin
{

Lighting::Lighting(void)
{
}


Lighting::~Lighting(void)
{
}


void Lighting::EnableLighting()
{
    glEnable(GL_LIGHTING);
}

void Lighting::DisableLighting()
{
    glDisable(GL_LIGHTING);
}

void Lighting::SetShadeModelFlat()
{
    glShadeModel(GL_FLAT);
}

void Lighting::SetShadeModelSmooth()
{
    glShadeModel(GL_SMOOTH);
}

}
