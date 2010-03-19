#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "Vector.h"
#include "Material.h"
#include "Fragment.h"

class RenderableObject
{
public:
    RenderableObject();

    Vector getPosition() const { return m_position; }
    void setPosition(const Vector& _position) { m_position = _position; }

    Material getMaterial() const { return m_material; }
    void setMaterial(const Material& _material) { m_material = _material; }

    virtual float getRadius() const =0;
    virtual float doIntersection(const Vector _cam, const Vector _ray) =0;
    virtual Fragment getFragment(const Vector _cam, const Vector _ray, const float _distance) =0;
    //virtual
private:
    Vector m_position;
    Material m_material;
};

#endif // RENDERABLEOBJECT_H
