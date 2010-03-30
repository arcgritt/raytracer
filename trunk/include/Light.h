#ifndef LIGHT_H
#define LIGHT_H

#include "Sphere.h"

class Light : public Sphere
{
public:
    /// \brief the default constructor
    Light();

    Light(Vector _position, float _radius, Material _material, float _magnitude);

    float GetMagnitude() const { return c_magnitude; }

    void SetMagnitude(float &_magnitude) { c_magnitude = _magnitude; }

private:
    float c_magnitude;
};

#endif // LIGHT_H
