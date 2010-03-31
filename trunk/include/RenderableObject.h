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

    /// \brief returns the position of this object
    /// \returns the position of this object
    Vector GetPosition() const { return m_position; }

    /// \brief returns the colour of this object
    /// \returns the colour of this object
    Colour GetColour() const { return m_colour; }

    /// \brief returns the material of this object
    /// \returns the material of this object
    Material GetMaterial() const { return m_material; }

    /// \brief returns the radius of this object
    /// \returns the radius of this object
    float GetRadius() const;

    /// \brief checks if the input ray intersects with this object
    /// @param[in] _rayOrigin   the origin of the ray to perform the intersection test with
    /// @param[in] _ray         the direction of the ray to perform the intersection test with
    /// \returns -1 if no intersection occured, or the square distance from _rayOrigin to the point of intersection
    virtual float DoIntersection(Vector& _rayOrigin, Vector& _ray) =0;

    /// \brief retrieves a fragment containing the information necessary to shade this object
    /// @param[in] _rayOrigin   the point of origin of the ray
    /// @param[in] _ray         the direction of the ray
    /// @param[in] _distance    the distance between the ray's origin and the point of intersection (saves calculating it again)
    /// \returns a fragment containing the information necessary to shade this object
    virtual Fragment GetFragment(Vector& _rayOrigin, Vector& _ray, const float _distance) =0;
protected:
    /// \brief sets the position of this object
    /// @param[in] _the new position of this object
    void SetPosition(const Vector& _position) { m_position = _position; }

    /// \brief
    /// @param[in] _
    void SetColour(const Colour& _colour) { m_colour = _colour; }

    /// \brief
    /// @param[in] _
    void SetMaterial(const Material& _material) { m_material = _material; }
private:
    Vector m_position;
    Colour m_colour;
    Material m_material;
};

#endif // RENDERABLEOBJECT_H
