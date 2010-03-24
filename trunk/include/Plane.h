#ifndef PLANE_H
#define PLANE_H

#include "RenderableObject.h"
#include "Vector.h"
#include "Material.h"

class Plane : public RenderableObject
{
public:
    Plane();
    /*
    Plane(Vector _position, float _x, float _y);
    Plane(Vector _position, float _x, float _y, Material _material);
    float doIntersection(const Vector _rayOrigin, const Vector _ray);
    Fragment getFragment(const Vector _rayOrigin, const Vector _ray, const float _distance);
private:
    float c_x;
    float c_y;*/
};



#endif // PLANE_H
