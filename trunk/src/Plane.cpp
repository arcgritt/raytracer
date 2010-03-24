#include "Plane.h"

Plane::Plane()
{
}

/*
Plane::Plane(Vector _position, float _x, float _y)
{
    SetPosition(_position);
    c_x = _x;
    c_y = _y;
}

Plane::Plane(Vector _position, float _x, float _y, Material _material)
{
    SetPosition(_position);
    c_x = _x;
    c_y = _y;
    SetMaterial(_material);
}

float Plane::doIntersection(Vector _rayOrigin, Vector _ray)
{

    surface normal:
        Vector(getPosition().



    //Vector u = _

    int
    intersect3D_SegmentPlane( Segment S, Plane Pn, Point* I )
    {
        Vector    u = S.P1 - S.P0;
        Vector    w = S.P0 - Pn.V0;

        float     D = dot(Pn.n, u);
        float     N = -dot(Pn.n, w);

        if (fabs(D) < SMALL_NUM) {          // segment is parallel to plane
            if (N == 0)                     // segment lies in plane
                return 2;
            else
                return 0;                   // no intersection
        }
        // they are not parallel
        // compute intersect param
        float sI = N / D;
        if (sI < 0 || sI > 1)
            return 0;                       // no intersection

        *I = S.P0 + sI * u;                 // compute segment intersect point
        return 1;
    }
}


Fragment Plane::getFragment(Vector _rayOrigin, Vector _ray, float _distance)
{


}
*/
