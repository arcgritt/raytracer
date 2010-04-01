#ifndef RAY_H
#define RAY_H

#include "RenderableObject.h"
#include "Vector.h"

/// \file Ray.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Ray
/// \brief Encapsulates the information belonging to a ray or which has a 1:1 relationship with a ray
/// \todo Add another vector for the point of origin of the ray

class Ray
{
public:
  /// \brief The default constructor
  Ray();

  /// \brief Constructs a new ray object
  /// @param[in] _direction               the direction of the ray
  Ray(
      Vector& _direction
      );

  /// \brief Used to allow the ray object to encapsulate the objectID of the closest object which it intersects with
  /// @param[in] _intersectionDistance    the square distance of the object which the ray has intersected with
  /// @param[in] _objectIntersected       a pointer to the object which the ray has intersected with
  void Intersection(
      const float& _intersectionDistance,
      RenderableObject* _objectIntersected
      );

  /// \brief Returns the direction of the ray
  /// \returns the direction of the ray
  Vector& GetVector();

  /// \brief Returns the square distance of the closest intersection of this ray
  /// \returns the square distance of the closest intersection of this ray
  float GetClosestIntersection() const { return m_closestIntersection; }

  /// \brief Returns a pointer to the closest object which the ray intersected
  /// \returns a pointer to the closest object which the ray intersected
  RenderableObject* GetObjectIntersected() const { return m_objectIntersected; }

  /// \brief Returns a string containing debug information about this object
  /// \returns a string containing debug information about this object
  const std::string GetDebugInformation();
private:
  /// Direction of the ray
  Vector m_direction;

  /// Square distance to the closest intersection of the ray
  float m_closestIntersection;

  /// Pointer to the closest object intersected by the ray, which is at m_closestIntersection
  RenderableObject* m_objectIntersected;
};

#endif // RAY_H
