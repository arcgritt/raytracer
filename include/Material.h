#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"

/// \file Material.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Material
/// \brief Material which can be assigned to an object and contains parameters which affect colour calcuations
/// \todo

class Material {
    public:
        /// \brief The default constructor
        Material();
        
        /// \brief A simple constructor for lights
        /// @param[in] _diffuseColour           the diffuse colour of the object
        /// @param[in] _reflectivity            the contribution of reflected object's colour to the surface colour of this object
        Material(
            const Colour& _diffuseColour,
            const float _reflectivity
        );
        
        /// \brief A constructor for object materials
        /// @param[in] _materialName            the name of this material, to allow specification and retrieval when parsing a rib file
        /// @param[in] _diffuseColour           the diffuse colour of the object
        /// @param[in] _specularColour          the base colour of specular highlights
        /// @param[in] _specularIntensity       the intensity or multiplier used in specular lighting calculations
        /// @param[in] _specularExponent        the exponent used in specular lighting calculations
        /// @param[in] _reflectivity            the contribution of reflected object's colour to the surface colour of this object
        Material(
            const std::string& _materialName,
            const Colour& _diffuseColour,
            const Colour& _specularColour,
            const float _specularIntensity,
            const float _specularExponent,
            const float _reflectivity
        );
        
        /// \brief Returns the name of the material
        /// \returns the name of the material
        std::string GetName() const {
            return c_materialName;
        }
        
        /// \brief Returns the base colour to be used in diffuse lighting calcuations
        /// \returns the base colour to be used in diffuse lighting calcuations
        Colour GetDiffuseColour() const {
            return c_diffuseColour;
        }
        
        /// \brief Returns the base colour to be used in specular lighting calculations
        /// \returns the base colour to be used in specular lighting calculations
        Colour GetSpecularColour() const {
            return c_specularColour;
        }
        
        /// \brief Returns the intensity multiplier to be used in specular lighting calcuations
        /// \returns the intensity multiplier to be used in specular lighting calcuations
        float GetSpecularIntensity() const {
            return c_specularIntensity;
        }
        
        /// \brief Returns the exponent to be used in specular lighting calcuations
        /// \returns the exponent to be used in specular lighting calcuations
        float GetSpecularExponent() const {
            return c_specularExponent;
        }
        
        /// \brief Returns the contribution of reflected object's colour to the surface colour of this object
        /// \returns the contribution of reflected object's colour to the surface colour of this object
        float GetReflectivity() const {
            return c_reflectivity;
        }
        
        /// \brief Returns debug information about the material
        /// \returns debug information about the material
        std::string const GetDebugInformation();
        
    private:
        /// Name of the material, for reference in the RIB file
        std::string c_materialName;
        
        /// Diffuse colour of the material
        Colour c_diffuseColour;
        
        /// Specular colour of the material
        Colour c_specularColour;
        
        /// Intensity of the specular contribution to colour
        float c_specularIntensity;
        
        /// Exponent of the specular contribution to colour
        float c_specularExponent;
        
        /// Reflectivity of the object
        float c_reflectivity;
};

#endif // MATERIAL_H
