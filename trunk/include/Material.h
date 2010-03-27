#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

class Material
{
public:
    Material();
    Material(const Colour& _colour, const float _reflectivity);
    Material(const Colour& _diffuseColour, const Colour& _specularColour, const float _specularIntensity, const float _specularExponent, const float _reflectivity);
    Colour GetDiffuseColour() const { return c_diffuseColour; }
    Colour GetSpecularColour() const { return c_specularColour; }
    float GetSpecularIntensity() const { return c_specularIntensity; }
    float GetSpecularExponent() const { return c_specularExponent; }
    float GetReflectivity() { return c_reflectivity; }

   // void setReflectivity()
private:
    Colour c_diffuseColour;
    Colour c_specularColour;
    float c_specularIntensity;
    float c_specularExponent;
    float c_reflectivity;
};

#endif // MATERIAL_H
