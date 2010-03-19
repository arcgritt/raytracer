#include "Colour.h"

Colour::Colour()
{
   c_r = 1.0f;
   c_g = 1.0f;
   c_b = 1.0f;
}

Colour::Colour(float _r, float _g, float _b)
{
    c_r = _r;
    c_g = _g;
    c_b = _b;
}

Colour::Colour(float _r, float _g, float _b, float _a)
{
    c_r = _r;
    c_g = _g;
    c_b = _b;
    c_a = _a;
}

void Colour::getColour256(unsigned char* _colour)
{
    _colour[0] = 255*c_r;
    _colour[1] = 255*c_g;
    _colour[2] = 255*c_b;
    _colour[3] = 255*c_a;
}

void Colour::getColour(float* _colour) {
    _colour[0] = c_r;
    _colour[1] = c_g;
    _colour[2] = c_b;
    _colour[3] = c_a;
}
