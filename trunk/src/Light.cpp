#include "Light.h"

Light::Light()
{
}


Light::Light(Vector _position, float _radius, Material _material, float _magnitude)
{
    SetPosition(_position);
    SetRadius(_radius);
    SetMaterial(_material);
    SetMagnitude(_magnitude);
}
