#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

class Material
{
public:
    /// \brief the default constructor
    Material();

    /// \brief a simple constructor for lights
    /// @param[in] _diffuseColour           the diffuse colour of the object
    /// @param[in] _reflectivity            the contribution of reflected object's colour to the surface colour of this object
    Material(const Colour& _diffuseColour, const float _reflectivity);

    /// \brief a constructor for object materials
    /// @param[in] _materialName            the name of this material, to allow specification and retrieval when parsing a rib file
    /// @param[in] _diffuseColour           the diffuse colour of the object
    /// @param[in] _specularColour          the base colour of specular highlights
    /// @param[in] _specularIntensity       the intensity or multiplier used in specular lighting calculations
    /// @param[in] _specularExponent        the exponent used in specular lighting calculations
    /// @param[in] _reflectivity            the contribution of reflected object's colour to the surface colour of this object

    Material(const std::string& _materialName, const Colour& _diffuseColour, const Colour& _specularColour, const float _specularIntensity, const float _specularExponent, const float _reflectivity);

    /// \brief returns the name of the material
    /// \returns the name of the material
    std::string GetName() const { return c_materialName; }

    /// \brief returns the base colour to be used in diffuse lighting calcuations
    /// \returns the base colour to be used in diffuse lighting calcuations
    Colour GetDiffuseColour() const { return c_diffuseColour; }

    /// \brief returns the base colour to be used in specular lighting calculations
    /// \returns the base colour to be used in specular lighting calculations
    Colour GetSpecularColour() const { return c_specularColour; }

    /// \brief returns the intensity multiplier to be used in specular lighting calcuations
    /// \returns the intensity multiplier to be used in specular lighting calcuations
    float GetSpecularIntensity() const { return c_specularIntensity; }

    /// \brief returns the exponent to be used in specular lighting calcuations
    /// \returns the exponent to be used in specular lighting calcuations
    float GetSpecularExponent() const { return c_specularExponent; }

    /// \brief returns the contribution of reflected object's colour to the surface colour of this object
    /// \returns the contribution of reflected object's colour to the surface colour of this object
    float GetReflectivity() const { return c_reflectivity; }

    /// \brief returns debug information about the material
    /// \returns debug information about the material
    std::string const GetDebugInformation();

private:
    std::string c_materialName;
    Colour c_diffuseColour;
    Colour c_specularColour;
    float c_specularIntensity;
    float c_specularExponent;
    float c_reflectivity;
};

#endif // MATERIAL_H
