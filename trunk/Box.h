#ifndef BOX_H
#define BOX_H

#include "Vector.h"

class Box
{
public:
    Box();
private:
    Vector center;
    float x_magnitude;
    float y_magnitude;
    float z_magnitude;
};

#endif // BOX_H
