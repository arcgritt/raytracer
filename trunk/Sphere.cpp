#include "Sphere.h"


#include "cmath"

Sphere::Sphere()
{

}

Sphere::Sphere(Vector _center, float _radius)
{
    setPosition(_center);
    m_radius = _radius;
}

Sphere::Sphere(Vector _center, float _radius, Colour _colour)
{
    setPosition(_center);
    m_radius = _radius;
    setMaterial(Material(_colour));
}

/*Fragment Sphere::doIntersection(const Vector _ray, const Vector _cam)
{
    Vector dst = _cam-getPosition(); // distance from camera to sphere center

    float b = dst.dot(_ray); // angle between vector to sphere center and vector to pixel
    float c = dst.dot(dst) - getRadius()*getRadius(); // distance from camera to sphere center, squared
    float d = b*b - c;

    if(d >= 0) // if there is a hit
    {
        //hit = true;
        float intersection_distance = -b - sqrt(d);
        //pixel_rays[i].intersection(intersection_distance, j);

        Vector position = _ray * intersection_distance;
        Vector normal = getCenter();
        //Fragment hit_fragment = Fragment(const Vector &_position, const Vector &_normal, const Material &_material)
    }
}
*/

float Sphere::doIntersection(Vector _cam, Vector _ray)
{
    Vector dst = _cam-getPosition(); // distance from camera to sphere center

    float b = dst.dot(_ray); // angle between vector to sphere center and vector to pixel
    float c = dst.dot(dst) - getRadius()*getRadius(); // distance from camera to sphere center, squared
    float d = b*b - c;

    if(d >= 0) {
        return -b - sqrt(d);
    }

    return d;
}

Fragment Sphere::getFragment(Vector _cam, Vector _ray)
{
    Vector dst = _cam-getPosition(); // distance from camera to sphere center

    float b = dst.dot(_ray); // angle between vector to sphere center and vector to pixel
    float c = dst.dot(dst) - getRadius()*getRadius(); // distance from camera to sphere center, squared
    float d = b*b - c;

    float distance_from_cam = -b - sqrt(d);

    Vector point = _ray * distance_from_cam;
    Vector normal = point - getPosition();
    normal.normalise();

    return Fragment(point, normal, getMaterial());
}
