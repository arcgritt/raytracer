#include <fstream>
#include <iostream>


#include "MaterialParser.h"


MaterialParser::MaterialParser()
{

}

MaterialParser::MaterialParser(std::string _fileName)
{
    MaterialParser::ParseFile(_fileName);
}

void MaterialParser::ParseFile(std::string _filename)
{
    std::ifstream materialsFile;
    materialsFile.open(_filename.data());

    unsigned int materialsCount = 0;

    std::string materialName;
    Colour diffuseColour;
    Colour specularColour;
    float specularIntensity;
    float specularExponent;
    float materialReflectivity;

    if (materialsFile.is_open())
    {
        std::string line;
        Material material;

        // loop through the file
        while(!materialsFile.eof())
        {
            // grab a line from the input
            getline(materialsFile, line, '\n');

            // make sure it's not an empty line
            if(line.size() !=0)
            {
                // get a token iterator positioned at the first token
                tokenizer::iterator tokenIterator = GetTokenIterator(line); //tokens.begin();

                // save the first token, and increment the iterator (so that we can pass the first useful token to methods)
                std::string typeName = *tokenIterator++;

                // now see if it's a valid one and call the correct function
                if(typeName == "Material")
                {
                    // if not the first material being parsed, save the previous material
                    if(materialsCount != 0)
                    {
                        material = Material(diffuseColour, specularColour, specularIntensity, specularExponent, materialReflectivity);
                        std::cout << "New Material set: " << materialName << std::endl << material.GetDebugInformation() << std::endl;
                        materials.push_back(material);
                    }

                    materialName = *tokenIterator;
                    materialsCount++;
                }
                else if(typeName == "DiffuseColour")
                {
                    diffuseColour = MaterialParser::ParseColour(tokenIterator);
                    // std::cout << "Diffuse Colour: " << diffuseColour.GetDebugInformation() << std::endl;
                }
                else if(typeName == "SpecularColour")
                {
                    specularColour = MaterialParser::ParseColour(tokenIterator);
                    // std::cout << "Specular Colour: " << specularColour.GetDebugInformation() << std::endl;
                }
                else if(typeName == "SpecularIntensity")
                {
                    specularIntensity = MaterialParser::ParseFloat(*tokenIterator);
                    //std::cout << "Specular Intensity: " << specularIntensity << std::endl;
                }
                else if(typeName == "SpecularExponent")
                {
                    specularExponent = MaterialParser::ParseFloat(*tokenIterator);
                    // std::cout << "SpecularExponent: " << specularExponent << std::endl;
                }
                else if(typeName == "Reflectivity")
                {
                    materialReflectivity = MaterialParser::ParseFloat(*tokenIterator);
                    // std::cout << "Reflectivity: " << materialReflectivity << std::endl;
                }
                else if(typeName == "#")
                {
                    // is a comment
                }
                else
                {
                    std::cerr << "Unkown Token " << typeName << std::endl;
                }
            }
        } // while (not end of file) loop

        // add the last material
        material = Material(diffuseColour, specularColour, specularIntensity, specularExponent, materialReflectivity);
        std::cout << "New Material set: " << materialName << std::endl << material.GetDebugInformation() << std::endl;
        materials.push_back(material);

        // close the file
        materialsFile.close();
        std::cout << std::endl << "End of materials file (" << _filename << ")" << std::endl << materials.size() << " materials parsed";
    } // if (file is open) loop
    else
    {
        std::cout << "Failed to read materials file" << std::endl;
    }
}

Colour MaterialParser::ParseColour(tokenizer::iterator &_iterator)
{
    // use lexical cast to convert to float then increment the itor
    float r = ParseFloat(*_iterator++);
    float g = ParseFloat(*_iterator++);
    float b = ParseFloat(*_iterator);

    return Colour(r, g, b);
}
