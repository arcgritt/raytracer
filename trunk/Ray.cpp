#include "Ray.h"
#include "float.h"

#include "cstdio"

Ray::Ray()
{

}

Ray::Ray(Vector _direction)
{
    m_direction = _direction;
    m_closest_intersection = FLT_MAX;
}

void Ray::printDebug()
{
    m_direction.printDebug();
    printf("Float Max: %f", m_closest_intersection);
}

Vector& Ray::getVector()
{
    return m_direction;
}

void Ray::intersection(const float &_intersection_distance, const int &_intersection_object)
{
    if(_intersection_distance < m_closest_intersection)
    {
        m_closest_intersection = _intersection_distance;
        m_intersection_object = _intersection_object;
    }
}
