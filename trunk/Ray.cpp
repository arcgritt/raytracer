#include "Ray.h"
#include "float.h"

#include "cstdio"

Ray::Ray()
{

}

Ray::Ray(Vector _direction)
{
    m_direction = _direction;
    m_closestIntersection = FLT_MAX;
}

void Ray::printDebug()
{
    m_direction.printDebug();
    printf("Float Max: %f", m_closestIntersection);
}

Vector& Ray::getVector()
{
    return m_direction;
}

void Ray::intersection(const float &_intersectionDistance) {
    if(_intersectionDistance < m_closestIntersection) {
        m_closestIntersection = _intersectionDistance;
    }
}

float Ray::get_closest_intersection() {
    return m_closestIntersection;
}
