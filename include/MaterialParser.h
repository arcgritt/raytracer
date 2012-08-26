#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include "Colour.h"
#include "Material.h"
#include "Parser.h"

/// \file MaterialParser.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class MaterialParser
/// \brief Parses a materials file and generates Material objects. Inherits from Parser.
/// \todo

class MaterialParser: public Parser {
    public:
        /// \brief The default constructor
        MaterialParser();
        
        /// \brief Parses the input materials file and returns an std::vector storing the materials which were specified by the input file
        /// @param[in] _fileName        the location of the file
        /// \returns an std::vector storing the materials which were specified by the input file
        static std::vector<Material> ParseFile(
            const std::string& _fileName
        );
        
};

#endif // MATERIALPARSER_H
