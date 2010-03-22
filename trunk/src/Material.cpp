#include "Material.h"

#include "Colour.h"

Material::Material()
{

}

Material::Material(const Colour& _colour)
{
    c_colour = _colour;
    c_reflectivity = 0.0f;
}


Material::Material(const Colour& _colour, const float _reflectivity)
{
    c_colour = _colour;
    c_reflectivity = _reflectivity;
}
