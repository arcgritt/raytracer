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

Vector::Vector(const float _x, const float _y, const float _z)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_w = 1.0f;
}

Vector::Vector(const float _x, const float _y, const float _z, const float _w)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_w = _w;
}

void Vector::Normalise()
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
}



Vector Vector::operator*(const float _multiplier)
{
    return Vector(
            m_x * _multiplier,
            m_y * _multiplier,
            m_z * _multiplier,
            m_w
            );
}

Vector Vector::operator/(const float _divisor)
{
    return Vector(
            m_x * _divisor,
            m_y * _divisor,
            m_z * _divisor,
            m_w
            );
}

Vector Vector::Cross(const Vector &_v1, const Vector &_v2)
{
    const float v_x = (_v1.m_y * _v2.m_z) - (_v1.m_z * _v2.m_y);
    const float v_y = (_v1.m_z * _v2.m_x) - (_v1.m_x * _v2.m_z);
    const float v_z = (_v1.m_x * _v2.m_y) - (_v1.m_y * _v2.m_x);
    return Vector(v_x, v_y, v_z);
}

float Vector::Dot(const Vector &_v1, const Vector &_v2)
{
    return (_v1.m_x * _v2.m_x) + (_v1.m_y * _v2.m_y) + (_v1.m_z * _v2.m_z);
}

const std::string Vector::GetDebugInformation()
{
    char tmp[256];
    sprintf(tmp, "X: %f, Y: %f, Z: %f, W: %f", m_x, m_y, m_z, m_w);
    return std::string(tmp);
}
