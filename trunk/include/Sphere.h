#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Colour.h"
#include "RenderableObject.h"

class Sphere: public RenderableObject
{
public:
    /// \brief the default constructor
    Sphere();

    /// \brief constructs a new sphere
    /// @param[in] _center      the center position of this object
    /// @param[in] _radius      the radius of the sphere
    /// @param[in] _colour      the colour of this object
    /// @param[in] _material    the material of this object
    Sphere(Vector _center, float _radius, Colour _colour, Material _material);

    /// \brief returns the radius of the sphere
    /// \returns the radius of the sphere
    float GetRadius() const { return m_radius; }


    /// \brief sets the radius of the sphere
    /// @param[in] _radius      the radius of the sphere
    void SetRadius(const float _radius) { m_radius = _radius; }

    /// \brief tests whether the input ray intersects with this sphere
    /// @param[in] _rayOrigin   the point of origin of the ray
    /// @param[in] _ray         the direction of the ray
    /// \returns the square of the distance between the ray's origin and the closest intersection point (most rays intersect a sphere twice). Returns -1 if there was no intersection
    float DoIntersection(Vector& _rayOrigin, Vector& _ray);

    /// \brief retrieves a fragment containing the information necessary to shade this object
    /// @param[in] _rayOrigin   the point of origin of the ray
    /// @param[in] _ray         the direction of the ray
    /// @param[in] _distance    the distance between the ray's origin and the point of intersection (saves calculating it again)
    /// \returns a fragment containing the information necessary to shade this object
    Fragment GetFragment(Vector& _rayOrigin, Vector& _ray, const float _distance);

private:
    float m_radius;
};

#endif // SPHERE_H
