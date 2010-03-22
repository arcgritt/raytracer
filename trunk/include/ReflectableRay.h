#ifndef REFLECTABLERAY_H
#define REFLECTABLERAY_H

#include "Ray.h"

class ReflectableRay : public Ray
{
public:
    ReflectableRay();
    ReflectableRay(Vector& _direction);
    //Ray GetReflectedRay() { return m_reflection&; }
    //void SetReflectedRay(Ray& _reflection) { m_reflection = _reflection; }
private:

};

#endif // REFLECTABLERAY_H
