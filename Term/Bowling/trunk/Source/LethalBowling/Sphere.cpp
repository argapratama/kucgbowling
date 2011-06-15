#include "Sphere.h"

namespace Virgin
{

Sphere::Sphere ()
    :
    m_kCenter(Vector3::ZERO)
{
    m_fRadius = (float)0.0;
}
//----------------------------------------------------------------------------
Vector3& Sphere::Center ()
{
    return m_kCenter;
}
//----------------------------------------------------------------------------
const Vector3& Sphere::Center () const
{
    return m_kCenter;
}
//----------------------------------------------------------------------------
float& Sphere::Radius ()
{
    return m_fRadius;
}
//----------------------------------------------------------------------------
const float& Sphere::Radius () const
{
    return m_fRadius;
}

}