#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "Vector.h"
#include "Material.h"

class RenderableObject
{
public:
    RenderableObject();

    Vector& getPosition() { return m_position; }
    void setPosition(const Vector _position) { m_position = _position; }

    Material& getMaterial() { return m_material; }
    void setMaterial(const Material _material) { m_material = _material; }

    virtual float getRadius() =0;
private:
    Vector m_position;
    Material m_material;
};

#endif // RENDERABLEOBJECT_H
