#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
public:
    Colour();
    Colour(float, float, float);
    Colour(float, float, float, float);
    //float getColourScalar();
    void getColour256 (unsigned char *_colour);
    void getColour (float *_colour);
private:
    float c_r;
    float c_g;
    float c_b;
    float c_a;
};

#endif // COLOUR_H
