#include "Box.h"

Box::Box(Vector &_center, float _size)
{
    m_center = _center;
    m_xSize = _size;
    m_ySize = _size;
    m_zSize = _size;
}

Box::Box(Vector &_center, float _xSize, float _ySize, float _zSize)
{
    m_center = _center;
    m_xSize = _xSize;
    m_ySize = _ySize;
    m_zSize = _zSize;
}
