#ifndef RIBPARSER_H
#define RIBPARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "boost/tokenizer.hpp"

#include "Material.h"
#include "Parser.h"
#include "Scene.h"

/// \file RIBParser.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class RIBParser
/// \brief Parses an input RIB file and generates RenderableObject objects. Assigns the appropriate materials to these objects. Inherits from Parser.
/// \todo

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class RIBParser : public Parser {
    public:
        /// \brief The default constructor
        RIBParser();
        
        /// \brief Parses the input RIB file and returns a scene object encapsulating the objects created from it.
        /// @param[in] _fileName        the location of the file
        /// @param[in] _materials       the materials which are referred to by the RIB file
        /// \returns a scene object encapsulating the objects created from the RIB file
        static Scene ParseFile(
            const std::string& _fileName,
            const std::vector<Material>& _materials
        );
    private:
        /// Materials which may or may not be used by the RIB file
        static std::vector<Material> m_materials;
    private:
        /// \brief Retrieves the material associated with the input name
        /// @param[in] _materialName    the name of the material
        /// \returns the material associated with the input name
        static Material& GetMaterialByName(
            const std::string& _materialName
        );
        
        /// \brief Processes the header of a RIB file and returns a scene object with global parameters set, but with no objects or lights
        /// @param[in] _ribFileStream   the io stream of the RIB file to be processed
        /// \returns a scene object with global parameters set, but with no objects or lights
        static Scene ParseHeader(
            std::ifstream& _ribFileStream
        );
        
        /// \brief Processes the body of a RIB file and adds the objects and lights which were created into the scene object
        /// @param[in] _ribFileStream   the io stream of the RIB file to be processed
        /// @param[in] _scene           the scene to add objects and lights to
        static void ParseWorld(
            std::ifstream& _ribFileStream,
            Scene& _scene
        );
        
        /// \brief Processes a the information specified along with a point light
        /// @param[in] _iterator        the iterator containing the strings
        /// \returns a light at the specified position and intensity
        static Light ParsePointLight(
            tokenizer::const_iterator& _iterator
        );
        
        /// \brief Processes a the information specified along with an ambient light
        /// @param[in] _iterator        the iterator containing the strings
        /// \returns the intensity of the ambient light source
        static float ParseAmbientLight(
            tokenizer::const_iterator& _iterator
        );
};

#endif // RIBPARSER_H
