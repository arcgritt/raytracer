#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Colour.h"
#include "RenderableObject.h"

class Sphere: public RenderableObject
{
public:
    Sphere();

    Sphere(Vector _center, float _radius);

    Sphere(Vector _center, float _radius, Colour _colour, Material _material);

    float GetRadius() const { return m_radius; }
    void SetRadius(const float _radius) { m_radius = _radius; }

    float DoIntersection(Vector& _rayOrigin, Vector& _ray);

    Fragment GetFragment(Vector& _rayOrigin, Vector& _ray, const float _distance);

private:
    float m_radius;
};

#endif // SPHERE_H
