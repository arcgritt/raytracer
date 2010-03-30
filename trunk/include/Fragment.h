#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "Colour.h"
#include "Material.h"
#include "Vector.h"

class Fragment
{
public:
    /// \brief the default constructor
    Fragment();

    /// \brief constructs a new object containing information relevant to colour calculations for this intersection
    /// @param[in] _position    the point of intersection
    /// @param[in] _normal      the surface normal of the intersected object
    /// @param[in] _colour      the colour of the intersected object
    /// @param[in] _material    the material of the intersected object
    Fragment(const Vector& _position, const Vector& _normal, const Colour& _colour, const Material& _material);

    /// \brief returns the point of intersection
    /// \returns  the point of intersection
    Vector GetPosition() const { return c_position; }

    /// \brief returns the surface normal of the intersected object
    /// \returns the surface normal of the intersected object
    Vector GetNormal() const { return c_normal; }

    /// \brief returns the colour of the intersected object
    /// \returns the colour of the intersected object
    Colour GetColour() const { return c_colour; }

    /// \brief returns the material of the intersected object
    /// \returns the material of the intersected object
    Material GetMaterial() const { return c_material; }

private:
    /// the point of intersection
    Vector c_position;
    /// the surface normal of the intersected object
    Vector c_normal;
    /// the colour of the intersected object
    Colour c_colour;
    /// the material of the intersected object
    Material c_material;
};

#endif // FRAGMENT_H
