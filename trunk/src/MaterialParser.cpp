#include <fstream>
#include <iostream>

// Boost
#include "boost/random.hpp"
#include "boost/lexical_cast.hpp"

#include "MaterialParser.h"
#include "Material.h"
#include "Util.h"

boost::char_separator<char> sep(" \t\r\n");
boost::mt19937 Generator;


boost::uniform_real<float> distributionPos(0.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

boost::uniform_real<float> distribution(-1.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);

MaterialParser::MaterialParser()
{

}

MaterialParser::MaterialParser(char* _fileName)
{


    MaterialParser::ParseFile(_fileName);
}

void MaterialParser::ParseFile(char* _filename)
{
    std::vector<Material> materials;
    std::ifstream materialsFile;
    materialsFile.open(_filename);


    // get the string delimited by " "
    std::string materialName;
    Colour diffuseColour;
    Colour specularColour;
    float specularIntensity;
    float specularExponent;
    float materialReflectivity;

    if (materialsFile.is_open())
    {
        // loop through the file
        while(!materialsFile.eof())
        {
            std::string line;

            // grab a line from the input
            getline(materialsFile, line, '\n');
            // make sure it's not an empty line
            if(line.size() !=0)
            {
                // now tokenize the line
                tokenizer tokens(line, sep);

                // and get the first token
                tokenizer::iterator tokenIterator = tokens.begin();

                // save the first token
                std::string typeName = *tokenIterator;

                // increment iterator so that we can pass the first useful token to methods
                tokenIterator++;

                // now see if it's a valid one and call the correct function
                if(typeName == "Material")
                {
                    materialName = *tokenIterator;
                    std::cout << "New Material set: " << materialName << std::endl;
                }
                else if(typeName == "DiffuseColour")
                {
                    diffuseColour = MaterialParser::ParseColour(tokenIterator);
                    std::cout << "Diffuse Colour: " << diffuseColour.GetDebugInformation() << std::endl;
                }
                else if(typeName == "SpecularColour")
                {
                    specularColour = MaterialParser::ParseColour(tokenIterator);
                    std::cout << "Specular Colour: " << specularColour.GetDebugInformation() << std::endl;
                }
                else if(typeName == "SpecularIntensity")
                {
                    specularIntensity = MaterialParser::ParseFloat(*tokenIterator);
                    std::cout << "Specular Intensity: " << specularIntensity << std::endl;
                }
                else if(typeName == "SpecularExponent")
                {
                    specularExponent = MaterialParser::ParseFloat(*tokenIterator);
                    std::cout << "SpecularExponent: " << specularExponent << std::endl;
                }
                else if(typeName == "Reflectivity")
                {
                    materialReflectivity = MaterialParser::ParseFloat(*tokenIterator);
                    std::cout << "Reflectivity: " << materialReflectivity << std::endl;
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
        }

        materialsFile.close();
        std::cout << std::endl << "End of materials file (" << _filename << ")" <<std::endl;
    }
    else
    {
        std::cout << "Failed to read materials file" << std::endl;
    }
}

Colour MaterialParser::ParseColour(tokenizer::iterator &_iterator)
{
    // source jmacey
    // use lexical cast to convert to float then increment the itor
    float r = ParseFloat(*_iterator++);
    float g = ParseFloat(*_iterator++);
    float b = ParseFloat(*_iterator);
    // now print out values to prove it works

    Colour inputColour = Colour(r, g, b);
    return inputColour;
}

float MaterialParser::ParseFloat(std::string token)
{
    Util util;
    if(token == "rand") {
        return RandPosFloat();
    }
    return boost::lexical_cast<float>(token);
}
