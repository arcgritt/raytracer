#include "Sphere.h"


#include <cmath>

#include <cstdio>

Sphere::Sphere()
{

}

Sphere::Sphere(const Vector &_center, const float _radius, const Colour &_colour, const Material &_material)
{
    SetPosition(_center);
    m_radius = _radius;
    SetColour(_colour);
    SetMaterial(_material);
}

float Sphere::DoIntersection(Vector &_rayOrigin, Vector &_ray) // SpherePrimitive::intersect(const Ray& ray, float* t)
{
    // source: http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection

    Vector dst = _rayOrigin-GetPosition();

    //Compute A, B and C coefficients
    float a = Vector::Dot(_ray, _ray); //_ray.dot(_ray);
    float b = 2 * Vector::Dot(_ray, dst); //_ray.dot(dst);
    float c = Vector::Dot(dst, dst) - (GetRadius() * GetRadius());
    //float c = dst.dot(dst) - (getRadius() * getRadius());

    //Find discriminant
    float disc = b * b - 4 * a * c;

    // if discriminant is negative there are no real roots, so return
    // false as ray misses sphere
    if (disc < 0)
        return -1;

    // compute q as described above
    float distSqrt = sqrtf(disc);
    float q;
    if (b < 0)
    {
        q = (-b - distSqrt)/2.0;
    }
    else
    {
        q = (-b + distSqrt)/2.0;
    }

    // compute t0 and t1
    float t0 = q / a;
    float t1 = c / q;

    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0)
    {
        return -1;
    }

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0)
    {
        return t1;
    }
    // else the intersection point is at t0
    else
    {
        return t0;
    }
}

Fragment Sphere::GetFragment(Vector &_rayOrigin, Vector &_ray, const float _distance)
{
    // point of intersection in world space
    Vector point = _ray * _distance + _rayOrigin;

    // normal = point - center
    Vector normal = point - GetPosition();
    normal.Normalise();

    return Fragment(point, normal, GetColour(), GetMaterial());
}
