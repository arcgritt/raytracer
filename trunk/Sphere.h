#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Colour.h"
#include "RenderableObject.h"

class Sphere: public RenderableObject
{
public:
    Sphere();
    Sphere(Vector, float);
    Sphere(Vector, float, Colour);
    float getRadius();
    //Vector getCenter();
    //Colour getColour();
private:
    //Vector m_center;
    float m_radius;
   // Colour m_colour;
};

#endif // SPHERE_H
