#include "Material.h"

#include "Colour.h"

Material::Material()
{

}

/*Material::Material(const Colour& _colour)
{
    c_colour = _colour;
    c_reflectivity = 0.0f;
}*/


Material::Material(const Colour& _colour, const float _reflectivity)
{
    c_diffuseColour = _colour;
    c_reflectivity = _reflectivity;
}

Material::Material(const Colour &_diffuseColour, const Colour &_specularColour, float _specularIntensity, float _specularExponent, float _reflectivity)
{
    c_diffuseColour = _diffuseColour;
    c_specularColour = _specularColour;
    c_specularIntensity = _specularIntensity;
    c_specularExponent = _specularExponent;
    c_reflectivity = _reflectivity;
}

std::string Material::GetDebugInformation()
{
    char* temp = new char[32];

    std::string debugInfo;
    debugInfo += "Diffuse Colour: " + c_diffuseColour.GetDebugInformation() + "\n";
    debugInfo += "Specular Colour: " + c_specularColour.GetDebugInformation() + "\n";

    sprintf(temp, "Specular Intensity: %f \n", c_specularIntensity);
    debugInfo += temp;

    sprintf(temp, "Specular Exponent: %f \n", c_specularExponent);
    debugInfo += temp;

    sprintf(temp, "Reflectivity: %f \n", c_reflectivity);
    debugInfo += temp;
    return debugInfo;
}
