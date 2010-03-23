#include "Colour.h"

Colour::Colour()
{
   c_r = 1.0f;
   c_g = 1.0f;
   c_b = 1.0f;
   c_a = 0.0f;
}

Colour::Colour(float _r, float _g, float _b)
{
    c_r = _r;
    c_g = _g;
    c_b = _b;
    c_a = 0.0f;
}

Colour::Colour(float _r, float _g, float _b, float _a)
{
    c_r = _r;
    c_g = _g;
    c_b = _b;
    c_a = _a;
}

void  Colour::GetColour(float* _colour)
{
    _colour[0] = c_r;
    _colour[1] = c_g;
    _colour[2] = c_b;
    _colour[3] = c_a;
}

void Colour::GetColour256(float* _colour)
{
    _colour[0] = 255*c_r;
    _colour[1] = 255*c_g;
    _colour[2] = 255*c_b;
    _colour[3] = 255*c_a;
}

void Colour::operator+=(Colour &_colour)
{
    c_r += _colour.c_r;
    c_g += _colour.c_g;
    c_b += _colour.c_b;
    c_a += _colour.c_a;
}

void Colour::operator*=(Colour &_colour)
{
    c_r *= _colour.c_r;
    c_g *= _colour.c_g;
    c_b *= _colour.c_b;
    c_a *= _colour.c_a;
}

void Colour::operator*=(float _multiplier)
{
    c_r *= _multiplier;
    c_g *= _multiplier;
    c_b *= _multiplier;
    c_a *= _multiplier;
}

Colour Colour::Average(Colour &_colour1, Colour &_colour2)
{
    float r = (_colour1.c_r+_colour2.c_r)/2;
    float g = (_colour1.c_g+_colour2.c_g)/2;
    float b = (_colour1.c_b+_colour2.c_b)/2;
    float a = (_colour1.c_a+_colour2.c_a)/2;
    return Colour(r, g, b, a);
}

void Colour::operator&=(Colour &_colour)
{
    c_r = (c_r+_colour.c_r)/2;
    c_g = (c_g+_colour.c_g)/2;
    c_b = (c_b+_colour.c_b)/2;
    c_a = (c_a+_colour.c_a)/2;
}

std::string Colour::GetDebugInformation()
{
    char tmp[256];
    sprintf(tmp, "Red: %f, Green: %f, Blue: %f, Alpha: %f", c_r, c_g, c_b, c_a);
    return std::string(tmp);
}
