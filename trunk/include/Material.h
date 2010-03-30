#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

class Material
{
public:
    /// \brief the default constructor
    Material();


    Material(const Colour& _colour, const float _reflectivity);


    Material(const std::string& _materialName, const Colour& _diffuseColour, const Colour& _specularColour, const float _specularIntensity, const float _specularExponent, const float _reflectivity);

    std::string GetName() const { return c_materialName; }


    Colour GetDiffuseColour() const { return c_diffuseColour; }


    Colour GetSpecularColour() const { return c_specularColour; }


    float GetSpecularIntensity() const { return c_specularIntensity; }




    float GetSpecularExponent() const { return c_specularExponent; }


    float GetReflectivity() const { return c_reflectivity; }

    std::string const GetDebugInformation();

   // void setReflectivity()
private:
    std::string c_materialName;
    Colour c_diffuseColour;
    Colour c_specularColour;
    float c_specularIntensity;
    float c_specularExponent;
    float c_reflectivity;
};

#endif // MATERIAL_H
