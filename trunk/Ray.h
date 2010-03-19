#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray
{
public:
    Ray();
    Ray(Vector);
    void intersection(const float&, const int&);
    void printDebug();
    Vector& getVector();
    float get_closest_intersection() const { return m_closest_intersection; }
    int get_intersection_object() const { return m_intersection_object; }
private:
    float m_closest_intersection;
    unsigned int m_intersection_object;
    Vector m_direction;
};

#endif // RAY_H
