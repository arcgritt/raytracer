#ifndef LIGHT_H
#define LIGHT_H

#include "Sphere.h"

/// \file Light.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Light
/// \brief Light object which is used to calculate lighting information. Inherits from Sphere.
/// \todo

class Light : public Sphere
{
public:
    /// \brief The default constructor
    Light();

    /// \brief Constructs a new light
    /// @param[in] _position    the position of the light
    /// @param[in] _radius      the radius of the light
    /// @param[in] _material    the material to render the light as
    /// @param[in] _magnitude   the magnitude of the light
    Light(const Vector& _position, const float _radius, Material _material, const float _magnitude);

    /// \brief Returns the magnitude of the light source
    /// \returns the magnitude of the light source
    float GetMagnitude() const { return c_magnitude; }

    /// \brief Sets the magnitude of the light to a new value
    /// @param[in] _magnitude   the new magnitude of the light
    void SetMagnitude(const float _magnitude) { c_magnitude = _magnitude; }

private:
    /// Magnitude/intensity of the light
    float c_magnitude;
};

#endif // LIGHT_H
