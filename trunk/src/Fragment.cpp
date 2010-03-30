#include "Fragment.h"

Fragment::Fragment()
{
}

Fragment::Fragment(const Vector& _position, const Vector& _normal, const Vector &_reverseNormal, const Colour& _colour, const Material& _material)
{
    c_position = _position;
    c_normal = _normal;
    c_reverseNormal = _reverseNormal;
    c_colour = _colour;
    c_material = &_material;
}
