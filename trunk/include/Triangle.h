#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Colour.h"
#include "RenderableObject.h"
#include "Vector.h"

/// \file Triangle.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Triangle
/// \brief Renderable triangle object which contains the algorithmic code for detecting an intersection and holds the vertices of the triangle. Inherits from RenderableObject.
/// \todo

class Triangle : public RenderableObject
{
public:
    /// \brief the default constructor
    Triangle();

    /// \brief constructs a new triangle with colour and material properties
    /// @param[in] _v0          the point of the first vertex which forms this triangle
    /// @param[in] _v1          the point of the second vertex which forms this triangle
    /// @param[in] _v2          the point of the third vertex which forms this triangle
    /// @param[in] _colour      the colour of this triangle
    /// @param[in] _material    the material used to shade this triangle
    Triangle(const Vector& _v0, const Vector& _v1, const Vector& _v2, const Colour& _colour, const Material& _material);

    /// \brief tests whether the input ray intersects with this triangle
    /// @param[in] _rayOrigin   the point of origin of the ray
    /// @param[in] _ray         the direction of the ray
    /// \returns the square of the distance between the ray's origin and the intersection point . Returns -1 if there was no intersection
    float DoIntersection(Vector& _rayOrigin, Vector& _ray);

    /// \brief retrieves a fragment containing the information necessary to shade this object
    /// @param[in] _rayOrigin   the point of origin of the ray
    /// @param[in] _ray         the direction of the ray
    /// @param[in] _distance    the distance between the ray's origin and the point of intersection (saves calculating it again)
    /// \returns a fragment containing the information necessary to shade this object
    Fragment GetFragment(Vector& _rayOrigin, Vector& _ray, const float _distance);
private:
    /// Point 0 of the triangle
    Vector m_v0;

    /// Point 1 of the triangle
    Vector m_v1;

    /// Point 2 of the triangle
    Vector m_v2;

    /// Edge 1 of the triangle (P1 - P0)
    Vector m_edge1;

    /// Edge 2 of the triangle (P2 - P0)
    Vector m_edge2;


    float m_u;
    float m_v;
    float m_w;

    /// Surface normal of the triangle
    Vector m_normal;

};

#endif // TRIANGLE_H
