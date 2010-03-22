#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "Vector.h"
#include "Material.h"

class Fragment
{
public:
    Fragment();
    Fragment(const Vector& _position, const Vector& _normal, const Material& _material);

    Vector GetPosition() const { return m_position; }

    Vector GetNormal() const { return m_normal; }

    Material GetMaterial() const { return m_material; }
private:
    Vector m_position;
    Vector m_normal;
    Material m_material;
};

#endif // FRAGMENT_H
