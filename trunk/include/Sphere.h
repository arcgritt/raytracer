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
    Sphere(Vector, float, Material);
    float getRadius() const { return m_radius; }
    void SetRadius(float _radius) { m_radius = _radius; }
    float doIntersection(const Vector _rayOrigin, const Vector _ray);
    Fragment getFragment(const Vector _rayOrigin, const Vector _ray, const float _distance);
private:
    float m_radius;
};

#endif // SPHERE_H
