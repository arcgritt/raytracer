#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "Parser.h"
#include "Material.h"
#include "Colour.h"


class MaterialParser: public Parser
{
public:
    MaterialParser();

    MaterialParser(std::string _filename);

    void ParseFile(std::string _filename);

    std::vector<Material> GetMaterials() const { return materials; }

private:

    std::vector<Material> materials;

    static Colour ParseColour(tokenizer::iterator& _iterator);
};

#endif // MATERIALPARSER_H
