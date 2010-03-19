#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

class Material
{
public:
    Material();
    Material(Colour _colour);
    Colour getColour() const { return m_colour; }
    void setColour(const Colour &_colour) { m_colour = _colour; }
private:
    Colour m_colour;
};

#endif // MATERIAL_H
