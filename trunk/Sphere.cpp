#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(Vector _center, float _radius)
{
    m_center = _center;
    m_radius = _radius;
}

float Sphere::getRadius()
{
    return m_radius;
}

Vector Sphere::getCenter()
{
    return m_center;
}

Colour Sphere::getColour()
{
    return m_colour;
}
