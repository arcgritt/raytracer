#ifndef RIBPARSER_H
#define RIBPARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "boost/tokenizer.hpp"

#include "Material.h"
#include "Parser.h"
#include "Scene.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class RIBParser : public Parser
{
public:
    /// \brief the default constructor
    RIBParser();
    
    /// \brief parses the input RIB file and returns a scene object encapsulating the objects created from it.
    /// @param[in] _fileName        the location of the file
    /// @param[in] _materials       the materials which are referred to by the RIB file
    /// \returns a scene object encapsulating the objects created from the RIB file
    static Scene ParseFile(const std::string& _fileName, const std::vector<Material>& _materials);
private:
    /// \brief retrieves the material associated with the input name
    /// @param[in] _materialName    the name of the material
    /// \returns the material associated with the input name
    static Material& GetMaterialByName(const std::string& _materialName);

    /// \brief processes the header of a RIB file and returns a scene object with global parameters set, but with no objects or lights
    /// @param[in] _ribFileStream   the io stream of the RIB file to be processed
    /// \returns a scene object with global parameters set, but with no objects or lights
    static Scene ParseHeader(std::ifstream& _ribFileStream);

    /// \brief processes the body of a RIB file and adds the objects and lights which were created into the scene object
    /// @param[in] _ribFileStream   the io stream of the RIB file to be processed
    /// @param[in] _scene           the scene to add objects and lights to
    static void ParseWorld(std::ifstream& _ribFileStream, Scene& _scene);

    
    static std::vector<Material> m_materials;

};

#endif // RIBPARSER_H
