#ifndef RIBPARSER_H
#define RIBPARSER_H

#include <string>
#include <vector>
#include <fstream>

#include "boost/tokenizer.hpp"

#include "Parser.h"
#include "Material.h"
#include "Scene.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class RIBParser : public Parser
{
public:
    /// \brief the default constructor
    RIBParser();

    static Scene ParseFile(std::string _fileName, std::vector<Material>& _materials);

private:
    static std::vector<Material> m_materials;

    static Material& GetMaterialByName(std::string _materialName);

    static Scene ParseHeader(std::ifstream &_ribFileStream);

    static void ParseWorld(std::ifstream &_ribFileStream, Scene& _scene);

    static void GetMaterial(std::string _materialName);

};

#endif // RIBPARSER_H
