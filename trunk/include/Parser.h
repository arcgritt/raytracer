#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "boost/tokenizer.hpp"

#include "Colour.h"
#include "Vector.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class Parser
{
public:
    Parser();
protected:
    static tokenizer::iterator GetTokenIterator(std::string _line);

    //virtual void ParseFile(std::string _fileName) =0; // can't set this as return type is different for each inherited class

    static float ParseFloat(std::string _token);
    static float ParseRand(std::string _token);


    static std::string StripBrackets(std::string _string);
    static unsigned int ParseUnsignedInt(std::string _token);
    static Vector ParseVector(tokenizer::iterator& _iterator);
    static Colour ParseColour(tokenizer::iterator& _iterator);
};

#endif // PARSER_H
