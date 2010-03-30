#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "Parser.h"
#include "Material.h"
#include "Colour.h"


class MaterialParser: public Parser
{
public:
    MaterialParser();

    //MaterialParser(std::string _filename);

    static std::vector<Material> ParseFile(std::string _fileName);

    //void ParseFile(std::string _filename);

    //std::vector<Material> GetMaterials() const { return materials; }

private:

};

#endif // MATERIALPARSER_H
