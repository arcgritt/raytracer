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

    static Scene ParseFile(const std::string& _fileName, const std::vector<Material>& _materials);

private:
    static std::vector<Material> m_materials;

    static Material& GetMaterialByName(const std::string& _materialName);

    static Scene ParseHeader(std::ifstream& _ribFileStream);

    static void ParseWorld(std::ifstream& _ribFileStream, Scene& _scene);

    static void GetMaterial(const std::string& _materialName);

};

#endif // RIBPARSER_H
