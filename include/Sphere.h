#ifndef SPHERE_H
#define SPHERE_H

#include "Colour.h"
#include "RenderableObject.h"
#include "Vector.h"

/// \file Sphere.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Sphere
/// \brief Renderable sphere object which contains the algorithmic code for detecting an intersection and holds the radius of the sphere. Inherits from RenderableObject.
/// \todo

class Sphere: public RenderableObject {
    public:
        /// \brief the default constructor
        Sphere();
        
        /// \brief constructs a new sphere
        /// @param[in] _center      the center position of this object
        /// @param[in] _radius      the radius of the sphere
        /// @param[in] _colour      the colour of this object
        /// @param[in] _material    the material of this object
        Sphere(
            const Vector& _center,
            const float _radius,
            const Colour& _colour,
            const Material& _material);
            
        /// \brief returns the radius of the sphere
        /// \returns the radius of the sphere
        float GetRadius() const {
            return m_radius;
        }
        
        /// \brief tests whether the input ray intersects with this sphere
        /// @param[in] _rayOrigin   the point of origin of the ray
        /// @param[in] _ray         the direction of the ray
        /// \returns the square of the distance between the ray's origin and the closest intersection point (most rays intersect a sphere twice). Returns -1 if there was no intersection
        float DoIntersection(
            Vector& _rayOrigin,
            Vector& _ray
        );
        
        /// \brief retrieves a fragment containing the information necessary to shade this object
        /// @param[in] _rayOrigin   the point of origin of the ray
        /// @param[in] _ray         the direction of the ray
        /// @param[in] _distance    the distance between the ray's origin and the point of intersection (saves calculating it again)
        /// \returns a fragment containing the information necessary to shade this object
        Fragment GetFragment(
            Vector& _rayOrigin,
            Vector& _ray,
            const float _distance
        );
    private:
        /// Radius of the sphere
        float m_radius;
        
        /// Squared radius of the sphere. Used in intersection algorithm, so precalculation saves computation
        float m_squareRadius;
    protected:
        /// \brief sets the radius of the sphere
        /// @param[in] _radius      the radius of the sphere
        void SetRadius(const float _radius) {
            m_radius = _radius;
        }
};

#endif // SPHERE_H
