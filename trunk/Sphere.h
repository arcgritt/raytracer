#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Colour.h"

class Sphere
{
public:
    Sphere();
    Sphere(Vector, float);
    float getRadius();
    Vector getCenter();
    Colour getColour();
private:
    Vector m_center;
    float m_radius;
    Colour m_colour;
};

#endif // SPHERE_H
