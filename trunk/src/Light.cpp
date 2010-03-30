#include "Light.h"

Light::Light()
{
}


Light::Light(const Vector& _position, const float _radius, Material _material, const float _magnitude)
{
    SetPosition(_position);
    SetRadius(_radius);
    SetMaterial(_material);
    SetMagnitude(_magnitude);
}
