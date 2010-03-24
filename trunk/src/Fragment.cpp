#include "Fragment.h"

Fragment::Fragment()
{
}

Fragment::Fragment(const Vector& _position, const Vector& _normal, const Material& _material)
{
    c_position = _position;
    c_normal = _normal;
    c_material = &_material;
}
