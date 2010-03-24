#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "Vector.h"
#include "Material.h"

class Fragment
{
public:
    Fragment();

    /// \brief
    /// @param[in] _position    the position (point) of this pixel fragment
    /// @param[in] _normal      the  
    /// @param[in] _material
    Fragment(const Vector& _position, const Vector& _normal, const Material& _material);

    /// \brief
    /// \returns the position (point) of this pixel fragment
    Vector GetPosition() const { return c_position; }

    /// \brief
    /// \returns the surface normal of the object of this pixel fragment
    Vector GetNormal() const { return c_normal; }

    /// \brief
    /// \returns a pointer to the material of the object of this pixel fragment
    const Material* GetMaterial() const { return c_material; }

private:
    Vector c_position;
    Vector c_normal;
    const Material* c_material;
};

#endif // FRAGMENT_H
