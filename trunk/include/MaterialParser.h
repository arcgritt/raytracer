#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "Colour.h"
#include "Material.h"
#include "Parser.h"


class MaterialParser: public Parser
{
public:
    /// \brief the default constructor
    MaterialParser();

    static std::vector<Material> ParseFile(const std::string& _fileName);
private:

};

#endif // MATERIALPARSER_H
