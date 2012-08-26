#include <cstdio>
#include <float.h>

#include "Ray.h"


//----------------------------------------------------------------------------------------------------------------------
Ray::Ray()
{

}

//----------------------------------------------------------------------------------------------------------------------
Ray::Ray(Vector& _direction)
{
  m_direction = _direction;
  m_closestIntersection = FLT_MAX;
}

//----------------------------------------------------------------------------------------------------------------------
Vector& Ray::GetVector()
{
  return m_direction;
}

//----------------------------------------------------------------------------------------------------------------------
void Ray::Intersection(const float& _intersectionDistance, RenderableObject* _objectIntersected)
{
  if(_intersectionDistance < m_closestIntersection)
  {
    m_closestIntersection = _intersectionDistance;
    m_objectIntersected = _objectIntersected;
  }
}

//----------------------------------------------------------------------------------------------------------------------
const std::string Ray::GetDebugInformation()
{
  char tmp[256];
  sprintf(tmp, "Closest Intersection: %f", m_closestIntersection);
  return std::string(tmp);
}
