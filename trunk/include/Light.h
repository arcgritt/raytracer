#ifndef LIGHT_H
#define LIGHT_H

#include "Sphere.h"

class Light : public Sphere
{
public:
    Light();
    Light(Vector _position, float, Material _material, float);
    float GetMagnitude() { return c_magnitude; }
    void SetMagnitude(float &_magnitude) { c_magnitude = _magnitude; }
private:
    float c_magnitude;
};

#endif // LIGHT_H
