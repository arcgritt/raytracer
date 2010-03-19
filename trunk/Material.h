#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

class Material
{
public:
    Material();
    Material(const Colour& _colour);
    Material(const Colour& _colour, const float _reflectivity );
    Colour GetColour() const { return c_colour; }
    //void setColour(const Colour &_colour) { m_colour = _colour; }
    float GetReflectivity() { return c_reflectivity; }
   // void setReflectivity()
private:
    Colour c_colour;
    float c_reflectivity;
};

#endif // MATERIAL_H
