#ifndef BOX_H
#define BOX_H

#include "Vector.h"

class Box
{
public:
    Box(Vector &_center, float _size);
    Box(Vector &_center, float _x_size, float _y_size, float _z_size);
private:
    Vector m_center;
    float m_x_size;
    float m_y_size;
    float m_z_size;
};

#endif // BOX_H
