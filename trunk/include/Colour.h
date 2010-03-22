#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
public:
    Colour();
    Colour(float, float, float);
    Colour(float, float, float, float);
    void GetColour(float* _colour);
    void GetColour256(float* _colour);
    void operator+=(Colour& _colour);
    void operator*=(Colour& _colour);
    void operator*=(float _multiplier);
private:
    float c_r;
    float c_g;
    float c_b;
    float c_a;
};

#endif // COLOUR_H
