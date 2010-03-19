#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(Vector _center, float _radius)
{
    setPosition(_center);
    m_radius = _radius;
}

Sphere::Sphere(Vector _center, float _radius, Colour _colour)
{
    setPosition(_center);
    m_radius = _radius;
    setMaterial(Material(_colour));
}

float Sphere::getRadius()
{
    return m_radius;
}
