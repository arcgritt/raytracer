#include "Fragment.h"

Fragment::Fragment()
{
}

Fragment::Fragment(const Vector &_position, const Vector &_normal, const Material &_material)
{
    m_position = _position;
    m_normal = _normal;
    m_material = _material;
}
