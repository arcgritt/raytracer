#ifndef LIGHT_H
#define LIGHT_H

#include "Sphere.h"

class Light : public Sphere
{
public:
    /// \brief the default constructor
    Light();

    /// \brief constructs a new light
    /// @param[in] _position    the position of the light
    /// @param[in] _radius      the radius of the light
    /// @param[in] _material    the material to render the light as
    /// @param[in] _magnitude   the magnitude of the light
    Light(const Vector& _position, const float _radius, Material _material, const float _magnitude);

    /// \brief returns the magnitude of the light source
    /// \returns the magnitude of the light source
    float GetMagnitude() const { return c_magnitude; }

    /// \brief sets the magnitude of the light to a new value
    /// @param[in] _magnitude   the new magnitude of the light
    void SetMagnitude(const float _magnitude) { c_magnitude = _magnitude; }

private:
    float c_magnitude;
};

#endif // LIGHT_H
