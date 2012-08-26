#include <iostream>

// Boost
#include "boost/random.hpp"
#include "boost/lexical_cast.hpp"


#include "RIBParser.h"
#include "RenderableObject.h"

std::vector<Material> RIBParser::m_materials;

//----------------------------------------------------------------------------------------------------------------------
RIBParser::RIBParser() {

}

//----------------------------------------------------------------------------------------------------------------------
Material& RIBParser::GetMaterialByName(const std::string& _materialName) {
    for(unsigned int i = 0; i < m_materials.size(); i++) {
        Material& material = m_materials[i];//.GetDebugInformation;
        
        if(!material.GetName().compare(_materialName)) {
            return material;
        }
    }
    
    return m_materials[0]; // return first material, for safety
}


//----------------------------------------------------------------------------------------------------------------------
Scene RIBParser::ParseFile(const std::string& _fileName, const std::vector<Material>& _materials) {
    m_materials  = _materials;
    
    std::ifstream ribFileStream;
    ribFileStream.open(_fileName.data());
    
    Scene scene;
    if (ribFileStream.is_open()) {
        std::cout << "### START: Parsing global parameters" << std::endl;
        scene = ParseHeader(ribFileStream);
        std::cout << "### FINISH: Parsing global parameters" << std::endl;
        std::cout << "### START: Parsing world parameters" << std::endl;
        ParseWorld(ribFileStream, scene);
        std::cout << "### FINISH: Parsing world parameters" << std::endl;
        
        // close the file
        ribFileStream.close();
        std::cout << std::endl << "End of RIB file (" << _fileName << ")" << std::endl << std::endl << std::endl;
    } // if (file is open) loop
    else {
        std::cout << "Failed to read materials file" << std::endl;
    }
    
    return scene;
}

//----------------------------------------------------------------------------------------------------------------------
Scene RIBParser::ParseHeader(std::ifstream& _ribFileStream) {
    unsigned int displayWidth;
    unsigned int displayHeight;
    float pixelAspectRatio;
    float fieldOfView;
    
    std::string cameraType;
    
    std::string line;
    bool loopContinue = true;
    // loop through the file
    while(!_ribFileStream.eof() && loopContinue) {
        // grab a line from the input
        getline(_ribFileStream, line, '\n');
        
        // make sure it's not an empty line
        if(line.size() !=0) {
            // get a token iterator positioned at the first token
            tokenizer::const_iterator tokenIterator = GetTokenIterator(line); //tokens.begin();
            
            // save the first token, and increment the iterator (so that we can pass the first useful token to methods)
            std::string typeName = *tokenIterator++;
            
            // now see if it's a valid one and call the correct function
            if(typeName == "Display") {
                // stuff to do with screen vs writing to file
            } else if(typeName == "Format") {
                displayWidth = ParseUnsignedInt(*tokenIterator++);
                displayHeight = ParseUnsignedInt(*tokenIterator++);
                pixelAspectRatio = ParseFloat(*tokenIterator);
            } else if(typeName == "Projection") {
                cameraType = *tokenIterator++;//.substr(1, tokenIterator.npos-1);
                std::string token = StripBrackets(*tokenIterator++);
                if(token == "fov") {
                    fieldOfView = ParseFloat(StripBrackets(*tokenIterator++));
                }
                
                // projection vs ortho
            } else if(typeName == "#") {
                // is a comment
                // std::cout << line << std::endl;
            } else if(typeName == "WorldBegin") {
                loopContinue = false;
            } else {
                std::cerr << "Unknown Token " << typeName << std::endl;
            }
        }
    } // while (not end of file) loop
    
    return Scene(displayWidth, displayHeight, pixelAspectRatio, fieldOfView);
}

//----------------------------------------------------------------------------------------------------------------------
void RIBParser::ParseWorld(std::ifstream& _ribFileStream, Scene& _scene) {
    std::string materialName;
    Colour colour;
    Material material;
    Vector translate;
    
    std::string line;
    bool loopContinue = true;
    // loop through the file
    while(!_ribFileStream.eof() && loopContinue) {
        // grab a line from the input
        getline(_ribFileStream, line, '\n');
        // make sure it's not an empty line
        if(line.size() !=0) {
            // get a token iterator positioned at the first token
            tokenizer::const_iterator tokenIterator = GetTokenIterator(line); //tokens.begin();
            
            // save the first token, and increment the iterator (so that we can pass the first useful token to methods)
            std::string typeName = tokenIterator++.current_token();
            
            // now see if it's a valid one and call the correct function
            if(typeName == "Color") {
                colour = ParseColour(tokenIterator);
            } else if(typeName == "Surface") {
                materialName = StripBrackets(*tokenIterator);
            } else if(typeName == "Translate") {
                translate = ParseVector(tokenIterator);
            }
            /* FINAL TYPES - OBJECTS OR LIGHTS */
            else if(typeName == "Sphere") {
                float radius = ParseFloat(*tokenIterator++);
                _scene.AddObject(new Sphere(translate, radius, colour, GetMaterialByName(materialName)));
            } else if(typeName == "LightSource") {
                std::string lightType = StripBrackets(*tokenIterator++);
                if(lightType == "pointlight") {
                    _scene.AddLight(ParsePointLight(tokenIterator));
                } else if(lightType == "ambientlight") {
                    _scene.SetAmbient(ParseAmbientLight(tokenIterator));
                } else {
                    std::cout << "Error: unrecognised light type: " << lightType << std::endl;
                }
            }
            /* Comments or termination string */
            else if(typeName == "#") {
                // is a comment
                //std::cout << line << std::endl;
            } else if(typeName == "WorldEnd") {
                loopContinue = false;
            } else {
                std::cerr << "Unknown Token " << typeName << std::endl;
            }
        }
    } // while (not end of file) loop
}

Light RIBParser::ParsePointLight(tokenizer::const_iterator& _iterator) {
    const float radius = ParseFloat(*_iterator++);
    
    _iterator++; // "intensity"
    const unsigned int intensity = ParseFloat(*_iterator++);
    
    _iterator++; // "from"
    const Vector position = ParseVector(_iterator);
    
    const Material lightMaterial = Material("pointlight", Colour(1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f), 50, 50, 0.0f);
    return Light(position, radius, lightMaterial, intensity);
}

float RIBParser::ParseAmbientLight(tokenizer::const_iterator& _iterator) {
    //const float radius = ParseFloat(*_iterator++);
    _iterator++; // radius
    
    _iterator++; // "intensity"
    const float intensity = ParseFloat(StripBrackets(*_iterator));
    return intensity;
}
