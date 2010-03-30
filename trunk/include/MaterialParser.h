#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "Parser.h"
#include "Material.h"
#include "Colour.h"


class MaterialParser: public Parser
{
public:
    /// \brief the default constructor
    MaterialParser();

    static std::vector<Material> ParseFile(const std::string& _fileName);
private:

};

#endif // MATERIALPARSER_H
