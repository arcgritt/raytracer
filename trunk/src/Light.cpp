#include "Light.h"

Light::Light()
{
}


Light::Light(Vector _center, float _radius, Material _material, float _magnitude)
{
    setPosition(_center);
    SetRadius(_radius);
    setMaterial(_material);
    SetMagnitude(_magnitude);
}
