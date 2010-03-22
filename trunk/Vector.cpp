#include "Vector.h"
#include <stdio.h>
#include <cmath>

Vector::Vector()
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
    m_w = 1.0f;
}

Vector::Vector(float _x, float _y, float _z)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_w = 1.0f;
}

Vector::Vector(float _x, float _y, float _z, float _w)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_w = _w;
}

void Vector::printDebug()
{
    printf("Vector information: %f, %f, %f, %f \n", m_x, m_y, m_z, m_w);
}

void Vector::normalise()
{
    // source Jon Macey
    float length=sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
    m_x/=length;
    m_y/=length;
    m_z/=length;
}

float Vector::Length()
{
    return sqrt(SquareLength());
}

float Vector::SquareLength()
{
    return m_x*m_x + m_y*m_y + m_z*m_z;
}


float Vector::dot(const Vector &_v)
{
    // source Jon Macey

    return m_x * _v.m_x + m_y * _v.m_y + m_z * _v.m_z;
}

void Vector::operator+=(const Vector &_v)
{
    // source Jon Macey
    m_x+=_v.m_x;
    m_y+=_v.m_y;
    m_z+=_v.m_z;
    m_w=0.0;
}

Vector Vector::operator+(const Vector &_v)
{
    // source Jon Macey
    return Vector(m_x+_v.m_x, m_y+_v.m_y, m_z+_v.m_z, 0.0f);
    //m_x-=_v.m_x;
   // m_y-=_v.m_y;
   // m_z-=_v.m_z;
    //m_w=0.0;
}


void Vector::operator-=(const Vector &_v)
{
    // source Jon Macey
    m_x-=_v.m_x;
    m_y-=_v.m_y;
    m_z-=_v.m_z;
    m_w=0.0;
}

Vector Vector::operator-()
{
    return Vector(-m_x, -m_y, -m_z, m_z);
}

Vector Vector::operator-(const Vector &_v)
{
    // source Jon Macey
    return Vector(m_x-_v.m_x, m_y-_v.m_y, m_z-_v.m_z, 0.0f);
    //m_x-=_v.m_x;
   // m_y-=_v.m_y;
   // m_z-=_v.m_z;
    //m_w=0.0;
}



Vector Vector::operator *(const float _m)
{
    return Vector(
            m_x*_m,
            m_y*_m,
            m_z*_m,
            m_w
            );
}

Vector Vector::cross(const Vector &_v1, const Vector &_v2)
{
    float v_x = _v1.m_y*_v2.m_z-_v1.m_z*_v2.m_y;
    float v_y = _v1.m_z*_v2.m_x-_v1.m_x*_v2.m_z;
    float v_z = _v1.m_x*_v2.m_y-_v1.m_y*_v2.m_x;
    return Vector(v_x, v_y, v_z);
}
