#include "Box.h"

Box::Box(Vector &_center, float _size)
{
    m_center = _center;
    m_x_size = _size;
    m_y_size = _size;
    m_z_size = _size;
}

Box::Box(Vector &_center, float _x_size, float _y_size, float _z_size)
{
    m_center = _center;
    m_x_size = _x_size;
    m_y_size = _y_size;
    m_z_size = _z_size;
}
