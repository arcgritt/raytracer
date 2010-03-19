#include "Light.h"

Light::Light()
{
}


Light::Light(Vector _center, float _radius, Colour _colour, float _magnitude)
{
    setPosition(_center);
    SetRadius(_radius);
    setMaterial(Material(_colour));
    SetMagnitude(_magnitude);
}
