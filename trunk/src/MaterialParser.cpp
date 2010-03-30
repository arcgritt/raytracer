#include <fstream>
#include <iostream>


#include "MaterialParser.h"


MaterialParser::MaterialParser()
{

}

/*
std::vector<Material> MaterialParser::MaterialParser(std::string _filename)
{
    return MaterialParser::ParseFile(_filename);
}
*/
std::vector<Material> MaterialParser::ParseFile(const std::string &_filename)
{
    std::vector<Material> materials;

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
        std::cout << "### START: Parsing materials" << std::endl;
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
                        material = Material(materialName, diffuseColour, specularColour, specularIntensity, specularExponent, materialReflectivity);
                        materials.push_back(material);
                    }

                    materialName = *tokenIterator;
                    materialsCount++;
                }
                else if(typeName == "DiffuseColour")
                {
                    diffuseColour = MaterialParser::ParseColour(tokenIterator);
                }
                else if(typeName == "SpecularColour")
                {
                    specularColour = MaterialParser::ParseColour(tokenIterator);
                }
                else if(typeName == "SpecularIntensity")
                {
                    specularIntensity = MaterialParser::ParseFloat(*tokenIterator);
                }
                else if(typeName == "SpecularExponent")
                {
                    specularExponent = MaterialParser::ParseFloat(*tokenIterator);
                }
                else if(typeName == "Reflectivity")
                {
                    materialReflectivity = MaterialParser::ParseFloat(*tokenIterator);
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
        material = Material(materialName, diffuseColour, specularColour, specularIntensity, specularExponent, materialReflectivity);
        materials.push_back(material);

        // close the file
        materialsFile.close();
        std::cout << "### " << materials.size() << " materials parsed" << std::endl;
        std::cout << "### FINISH: Parsing materials" << std::endl;
    } // if (file is open) loop
    else
    {
        std::cout << "Failed to read materials file" << std::endl;
    }

    return materials;
}
