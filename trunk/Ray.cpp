#include "Ray.h"
#include "float.h"

#include "cstdio"

Ray::Ray()
{

}

Ray::Ray(Vector& _direction)
{
    m_direction = _direction;
    m_closestIntersection = FLT_MAX;
}

void Ray::PrintDebug()
{
    m_direction.printDebug();
    printf("Float Max: %f", m_closestIntersection);
}

Vector& Ray::GetVector()
{
    return m_direction;
}

void Ray::Intersection(const float& _intersectionDistance, RenderableObject& _objectIntersected)
{
    if(_intersectionDistance < m_closestIntersection)
    {
        m_closestIntersection = _intersectionDistance;
        m_objectIntersected = &_objectIntersected;
    }
}
