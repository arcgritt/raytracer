#include "Light.h"

Light::Light()
{
}


Light::Light(Vector _position, float _radius, Material _material, float _magnitude)
{
    setPosition(_position);
    SetRadius(_radius);
    setMaterial(_material);
    SetMagnitude(_magnitude);
}
