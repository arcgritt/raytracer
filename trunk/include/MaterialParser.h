#ifndef MATERIALPARSER_H
#define MATERIALPARSER_H

#include <string>

#include "boost/tokenizer.hpp"

#include "Colour.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class MaterialParser
{
public:
    MaterialParser();

    MaterialParser(char* _filename);

    static void ParseFile(char* _filename);

private:
    static Colour ParseColour(tokenizer::iterator& _iterator);
    static float ParseFloat(std::string _token);
};

#endif // MATERIALPARSER_H
