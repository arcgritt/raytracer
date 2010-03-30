#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "Colour.h"
#include "Fragment.h"
#include "Material.h"
#include "Vector.h"

class RenderableObject
{
public:
    /// \brief the default constructor
    RenderableObject();

    Vector GetPosition() const { return m_position; }
    void SetPosition(const Vector& _position) { m_position = _position; }

    Colour GetColour() const { return m_colour; }
    void SetColour(const Colour& _colour) { m_colour = _colour; }

    Material GetMaterial() const { return m_material; }
    void SetMaterial(const Material& _material) { m_material = _material; }

    virtual float GetRadius() const =0;
    virtual float DoIntersection(Vector& _rayOrigin, Vector& _ray) =0;

    virtual Fragment GetFragment(Vector& _rayOrigin, Vector& _ray, const float _distance) =0;
private:
    Vector m_position;
    Colour m_colour;
    Material m_material;
};

#endif // RENDERABLEOBJECT_H
