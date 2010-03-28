#ifndef RIBPARSER_H
#define RIBPARSER_H

#include <string>
#include <fstream>

#include "boost/tokenizer.hpp"

#include "Material.h"
#include "Colour.h"
#include "Scene.h"
#include "Vector.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class RIBParser
{
public:
    RIBParser();
    static Scene ParseFile(std::string _fileName);
private:
    static Scene ParseHeader(std::ifstream &_ribFileStream);

    static void ParseWorld(std::ifstream &_ribFileStream, Scene& _scene);

    static tokenizer::iterator GetTokenIterator(std::string _line);

    static std::string StripBrackets(std::string _string);

    static unsigned int ParseUnsignedInt(std::string _token);
    static float ParseFloat(std::string _token);
    static float ParseRand(std::string _token);


    static Vector ParseVector(tokenizer::iterator& _iterator);
    static Colour ParseColour(tokenizer::iterator& _iterator);
};

#endif // RIBPARSER_H
