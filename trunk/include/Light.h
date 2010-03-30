#ifndef LIGHT_H
#define LIGHT_H

#include "Sphere.h"

class Light : public Sphere
{
public:
    /// \brief the default constructor
    Light();

    Light(const Vector& _position, const float _radius, Material _material, const float _magnitude);

    float GetMagnitude() const { return c_magnitude; }

    void SetMagnitude(const float &_magnitude) { c_magnitude = _magnitude; }

private:
    float c_magnitude;
};

#endif // LIGHT_H
