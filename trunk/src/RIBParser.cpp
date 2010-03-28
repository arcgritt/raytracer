#include "include/RIBParser.h"


#include <iostream>

// Boost
#include "boost/random.hpp"
#include "boost/lexical_cast.hpp"

/*boost::char_separator<char> sep(" \t\r\n");

boost::mt19937 Generator;

boost::uniform_real<float> distributionPos(0.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

boost::uniform_real<float> distribution(-1.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);*/


RIBParser::RIBParser()
{

}


Scene RIBParser::ParseFile(std::string _filename)
{
    std::ifstream ribFileStream;
    //(_filename.data(), std::ifstream::in);
    ribFileStream.open(_filename.data());

    //std::ifstream ribFileStream = new std::ifstream(_filename.data());
    //ribFileStream.open(_filename.data());

    /*unsigned int materialsCount = 0;

    std::string materialName;
    Colour diffuseColour;
    Colour specularColour;
    float specularIntensity;
    float specularExponent;
    float materialReflectivity;*/


    Scene scene;
    if (ribFileStream.is_open())
    {
        std::cout << "### START: Parsing global parameters" << std::endl;
        scene = ParseHeader(ribFileStream);
        std::cout << "### FINISH: Parsing global parameters" << std::endl;
        std::cout << "### START: Parsing world parameters" << std::endl;
        ParseWorld(ribFileStream, scene);
        std::cout << "### FINISH: Parsing world parameters" << std::endl;

        // close the file
        ribFileStream.close();
        std::cout << std::endl << "End of RIB file (" << _filename << ")" << std::endl << std::endl << std::endl;
    } // if (file is open) loop
    else
    {
        std::cout << "Failed to read materials file" << std::endl;
    }

    return scene;
}

Scene RIBParser::ParseHeader(std::ifstream &_ribFileStream)
{
    unsigned int displayWidth;
    unsigned int displayHeight;
    float pixelAspectRatio;
    float fieldOfView;

    std::string cameraType;

    std::string line;
    bool loopContinue = true;
    // loop through the file
    while(!_ribFileStream.eof() && loopContinue)
    {
        // grab a line from the input
        getline(_ribFileStream, line, '\n');

        // make sure it's not an empty line
        if(line.size() !=0)
        {
            // get a token iterator positioned at the first token
            tokenizer::iterator tokenIterator = GetTokenIterator(line); //tokens.begin();

            // save the first token, and increment the iterator (so that we can pass the first useful token to methods)
            std::string typeName = *tokenIterator++;

            // now see if it's a valid one and call the correct function
            if(typeName == "Display")
            {
                // stuff to do with screen vs writing to file
            }
            else if(typeName == "Format")
            {
                displayWidth = ParseUnsignedInt(*tokenIterator++);
                displayHeight = ParseUnsignedInt(*tokenIterator++);
                pixelAspectRatio = ParseFloat(*tokenIterator);
            }
            else if(typeName == "Projection")
            {
                cameraType = *tokenIterator++;//.substr(1, tokenIterator.npos-1);
                std::string token = StripBrackets(*tokenIterator++);
                if(token == "fov")
                {
                    fieldOfView = ParseFloat(StripBrackets(*tokenIterator++));
                }

                //std::cout << cameraType;
                // projection vs ortho
            }
            else if(typeName == "#")
            {
                std::cout << line << std::endl;
                // is a comment
            }
            else if(typeName == "WorldBegin")
            {
                loopContinue = false;
            }
            else
            {
                std::cerr << "Unkown Token " << typeName << std::endl;
            }
        }
    } // while (not end of file) loop

    return Scene(displayWidth, displayHeight, pixelAspectRatio, fieldOfView);
}

void RIBParser::ParseWorld(std::ifstream &_ribFileStream, Scene& _scene)
{    
    std::vector<RenderableObject*> objects;

    Colour colour;
    Material material;
    Vector translate;

    std::string line;
    bool loopContinue = true;
    // loop through the file
    while(!_ribFileStream.eof() && loopContinue)
    {
        // grab a line from the input
        getline(_ribFileStream, line, '\n');

        // make sure it's not an empty line
        if(line.size() !=0)
        {
            // get a token iterator positioned at the first token
            tokenizer::iterator tokenIterator = GetTokenIterator(line); //tokens.begin();

            // save the first token, and increment the iterator (so that we can pass the first useful token to methods)
            std::string typeName = *tokenIterator++;

            // now see if it's a valid one and call the correct function
            if(typeName == "Colour")
            {
                colour = ParseColour(tokenIterator);
            }
            else if(typeName == "Material")
            {

            }
            else if(typeName == "Translate")
            {
                translate = ParseVector(tokenIterator);
            }
            else if(typeName == "Sphere")
            {
                float radius = ParseFloat(*tokenIterator++);
                Sphere sphere = Sphere(translate, radius, material);
                objects.push_back(&sphere);
            }
            else if(typeName == "#")
            {
                std::cout << line; // << std::endl;
                // is a comment
            }
            else if(typeName == "WorldEnd")
            {
                loopContinue = false;
            }
            else
            {
                std::cerr << "Unkown Token " << typeName << std::endl;
            }
        }
    } // while (not end of file) loop

    _scene.SetObjects(objects);
}

