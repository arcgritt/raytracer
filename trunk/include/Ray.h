#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "RenderableObject.h"

class Ray
{
public:
    /// \brief the default constructor
    Ray();

    Ray(Vector& _direction);

    void Intersection(const float& _intersectionDistance, RenderableObject* _objectIntersected);

    //void PrintDebug();

    Vector& GetVector();

    float GetClosestIntersection() const { return m_closestIntersection; }

    RenderableObject* GetObjectIntersected() const { return m_objectIntersected; }

    /// \brief Returns a string containing debug information about this object
    const std::string GetDebugInformation();
private:
    Vector m_direction;
    float m_closestIntersection;
    RenderableObject* m_objectIntersected;
    //Ray* m_reflection;
};

#endif // RAY_H
