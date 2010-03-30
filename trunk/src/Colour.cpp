#ifdef WINDOWS

#include <cstdio>

#endif

#include <assert.h>

#include "Colour.h"

Colour::Colour()
{
    m_r = 0.0f;
    m_g = 0.0f;
    m_b = 0.0f;
    m_a = 1.0f;
}

Colour::Colour(const float _r, const float _g, const float _b)
{
    m_r = _r;
    m_g = _g;
    m_b = _b;
    m_a = 0.0f;
}

Colour::Colour(const float _r, const float _g, const float _b, const float _a)
{
    m_r = _r;
    m_g = _g;
    m_b = _b;
    m_a = _a;
}

void Colour::GetColour(float *_colour)
{
    _colour[0] = m_r;
    _colour[1] = m_g;
    _colour[2] = m_b;
    _colour[3] = m_a;
}

void Colour::Floor()
{
    m_r = std::max(0.0f, m_r);
    m_g = std::max(0.0f, m_g);
    m_b = std::max(0.0f, m_b);
    m_a = std::max(0.0f, m_a);
}

void Colour::Ceil()
{
    m_r = std::min(1.0f, m_r);
    m_g = std::min(1.0f, m_g);
    m_b = std::min(1.0f, m_b);
    m_a = std::min(1.0f, m_a);
}

void Colour::GetColour256(unsigned int *_colour)
{
    assert(
            m_r >= 0.0f && m_r <= 1.0f &&
            m_g >= 0.0f && m_g <= 1.0f &&
            m_b >= 0.0f && m_b <= 1.0f &&
            m_a >= 0.0f && m_a <= 1.0f
           );
    _colour[0] = 255*m_r;
    _colour[1] = 255*m_g;
    _colour[2] = 255*m_b;
    _colour[3] = 255*m_a;
}

Colour Colour::operator+(const Colour &_colour)
{
    float r = m_r+_colour.m_r;
    float g = m_g+_colour.m_g;
    float b = m_b+_colour.m_b;
    float a = m_a+_colour.m_a;

    return Colour(r,g,b,a);
}

void Colour::operator+=(const Colour &_colour)
{
    m_r += _colour.m_r;
    m_g += _colour.m_g;
    m_b += _colour.m_b;
    m_a += _colour.m_a;
}

void Colour::operator*=(const Colour &_colour)
{
    m_r *= _colour.m_r;
    m_g *= _colour.m_g;
    m_b *= _colour.m_b;
    m_a *= _colour.m_a;
}

void Colour::operator*=(const float _multiplier)
{
    m_r *= _multiplier;
    m_g *= _multiplier;
    m_b *= _multiplier;
    m_a *= _multiplier;
}

void Colour::operator/=(const float _multiplier)
{
    m_r /= _multiplier;
    m_g /= _multiplier;
    m_b /= _multiplier;
    m_a /= _multiplier;
}


Colour Colour::Average(const Colour &_colour1, const Colour &_colour2)
{
    float r = (_colour1.m_r+_colour2.m_r)/2;
    float g = (_colour1.m_g+_colour2.m_g)/2;
    float b = (_colour1.m_b+_colour2.m_b)/2;
    float a = (_colour1.m_a+_colour2.m_a)/2;
    return Colour(r, g, b, a);
}

void Colour::operator&=(const Colour &_colour)
{
    m_r = (m_r+_colour.m_r)/2;
    m_g = (m_g+_colour.m_g)/2;
    m_b = (m_b+_colour.m_b)/2;
    m_a = (m_a+_colour.m_a)/2;
}

std::string Colour::GetDebugInformation()
{
    char tmp[256];
    sprintf(tmp, "Red: %f, Green: %f, Blue: %f, Alpha: %f", m_r, m_g, m_b, m_a);
    return std::string(tmp);
}
