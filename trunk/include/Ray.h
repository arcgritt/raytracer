#ifndef RAY_H
#define RAY_H

#include "RenderableObject.h"
#include "Vector.h"

/// \todo Add another vector for the point of origin of the ray

class Ray
{
public:
    /// \brief the default constructor
    Ray();

    /// \brief constructs a new ray object
    /// @param[in] _direction               the direction of the ray
    Ray(Vector& _direction);

    /// \brief used to allow the ray object to encapsulate the objectID of the closest object which it intersects with
    /// @param[in] _intersectionDistance    the square distance of the object which the ray has intersected with
    /// @param[in] _objectIntersected       a pointer to the object which the ray has intersected with
    void Intersection(const float& _intersectionDistance, RenderableObject* _objectIntersected);

    /// \brief returns the direction of the ray
    /// \returns the direction of the ray
    Vector& GetVector();

    /// \brief returns the square distance of the closest intersection of this ray
    /// \returns the square distance of the closest intersection of this ray
    float GetClosestIntersection() const { return m_closestIntersection; }

    /// \brief returns a pointer to the closest object which the ray intersected
    /// \returns a pointer to the closest object which the ray intersected
    RenderableObject* GetObjectIntersected() const { return m_objectIntersected; }

    /// \brief Returns a string containing debug information about this object
    /// \returns a string containing debug information about this object
    const std::string GetDebugInformation();
private:

    Vector m_direction;

    float m_closestIntersection;

    RenderableObject* m_objectIntersected;
};

#endif // RAY_H
