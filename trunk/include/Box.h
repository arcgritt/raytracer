#ifndef BOX_H
#define BOX_H

#include "Vector.h"

class Box
{
public:
    Box(Vector &_center, float _size);
    Box(Vector &_center, float _xSize, float _ySize, float _zSize);
private:
    Vector m_center;
    float m_xSize;
    float m_ySize;
    float m_zSize;
};

#endif // BOX_H
