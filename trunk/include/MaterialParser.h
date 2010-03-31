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

    /// \brief parses the input materials file and returns an std::vector storing the materials which were specified by the input file
    /// @param[in] _fileName        the location of the file
    /// \returns an std::vector storing the materials which were specified by the input file
    static std::vector<Material> ParseFile(const std::string& _fileName);
private:

};

#endif // MATERIALPARSER_H
