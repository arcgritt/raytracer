#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray
{
public:
    Ray();
    Ray(Vector);
    void intersection(const float&);
    void printDebug();
    Vector& getVector();
    float get_closest_intersection();
private:
    float m_closestIntersection;
    unsigned int m_intersectionObject;
    Vector m_direction;
};

#endif // RAY_H
