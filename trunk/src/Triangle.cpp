#include "include/Triangle.h"

#include <cstdlib>

//----------------------------------------------------------------------------------------------------------------------
Triangle::Triangle()
{

}

//----------------------------------------------------------------------------------------------------------------------
Triangle::Triangle(const Vector &_v0, const Vector &_v1, const Vector &_v2, const Colour &_colour, const Material &_material) {
    m_v0 = _v0;
    m_v1 = _v1;
    m_v2 = _v2;
    SetColour(_colour);
    SetMaterial(_material);
    m_normal = Vector::Cross(_v0, _v1);

    m_u = 0.0;
    m_v = 0.0;
    m_w = 0.0;

    // calculate the edge
    m_edge1 = m_v1 - m_v0;
    m_edge2 = m_v2 - m_v0;

    // the center of the tri is the 3 verts average
    Vector m_center = (m_v0 + m_v1 + m_v2) / 3.0;
    SetPosition(m_center);
}


// intersect_RayTriangle(): intersect a ray with a 3D triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 = disjoint (no intersect)
//             1 = intersect in unique point I1
//             2 = are in the same plane

/*float Triangle::DoIntersection(Vector &_rayOrigin, Vector &_ray)

//float intersect_RayTriangle( Ray R, Triangle T, Point* I )
{
    Vector    u, v, n;             // triangle vectors
    Vector    dir, w0, w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = m_v1 - m_v0;
    v = m_v2 - m_v0;
    n = Vector::Cross(u, v);             // cross product
    //if (n == (Vector)0)            // triangle is degenerate
     //   return -2;                 // do not deal with this case

    dir = _ray - _rayOrigin;             // ray direction vector
    w0 = _rayOrigin - m_v0;
    a = -Vector::Dot(n, w0);//dot(n,w0);
    b = Vector::Dot(n, dir); //dot(n,dir);
    if (b < -0.001f || b > 0.001f) {     // ray is parallel to triangle plane
        if (a == 0)                // ray lies in triangle plane
            return -1;
        else return -1;             // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                   // ray goes away from triangle
        return -1;                  // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    Vector pointIntersection = _rayOrigin + dir * r;           // intersect point of ray and plane

    return r*r;

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = Vector::Dot(u,u);
    uv = Vector::Dot(u,v);
    vv = Vector::Dot(v,v);
    w = pointIntersection - m_v0;
    wu = Vector::Dot(w,u);
    wv = Vector::Dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)        // I is outside T
        return -1;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return -1;

    return r;                      // I is in T
}*/

//----------------------------------------------------------------------------------------------------------------------
float Triangle::DoIntersection(Vector &_rayOrigin, Vector &_ray)
{
    // Calculate the ray direction
    Vector dir = _ray - _rayOrigin;

    // get the vector of the first edge
    Vector pvec = Vector::Cross(dir, m_edge2);

    // calculate the determinant
    float det = Vector::Dot(m_edge1, pvec);

    // if this is 0 no hit
    if (det > -0.00001f && det < 0.00001)
    {
        return -1;
    }

    // get the inverse det
    float inv_det = 1.0f / det;

    // calculate the 2nd vector
    Vector tvec = _rayOrigin - m_v0;

    // get the dot product of this and inv det
    m_u = Vector::Dot(tvec, pvec) * inv_det;

    // if out of range no hit
    if (m_u < -0.001f || m_u > 1.001f)
    {
        return -1;
    }

    // check the 2nd vector edge
    Vector qvec = Vector::Cross(tvec, m_edge1);

    // get the dot product
    m_v = Vector::Dot(dir, qvec) * inv_det;

    // if out of range no hit
    if (m_v < -0.001f || m_u + m_v > 1.001f)
    {
        return -1;
    }

    // check the final value
    m_w = Vector::Dot(m_edge2, qvec) * inv_det;

    // if less than 0 no hit
    if (m_w <= 0)
    {
        return -1;
    }

    // otherwise we are inside the triangle
    // so get the hit point
    // see http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm#intersect_RayTriangle()
    // get intersect point of ray with triangle plane
    // calculate the normal

    Vector n = Vector::Cross(m_v0, m_v2);
    float a = Vector::Dot(-n, tvec);
    float b = Vector::Dot(n, dir);
    float r = a/b;

    Vector vec = dir*r;
    return vec.SquareLength();

    /*
    // intersect point of ray and plane
    Vector m_hitPoint = _rayOrigin + (r * dir);
    Vector direction = m_hitPoint-_rayOrigin;

    float distance = direction.SquareLength();

    return distance;*/
}

//----------------------------------------------------------------------------------------------------------------------
Fragment Triangle::GetFragment(Vector &_rayOrigin, Vector &_ray, float _distance)
{
    Vector point = _ray * _distance + _rayOrigin;

    return Fragment(point, m_normal, GetColour(), GetMaterial());
}
