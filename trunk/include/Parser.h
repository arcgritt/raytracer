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
    /// \brief the default constructor
    Parser();
protected:
    static tokenizer::iterator GetTokenIterator(const std::string& _line);



    static float ParseFloat(const std::string& _token);


    static float ParseRand(const std::string& _token);


    static std::string StripBrackets(const std::string& _string);



    static unsigned int ParseUnsignedInt(const std::string& _token);



    static Vector ParseVector(tokenizer::iterator& _iterator);



    static Colour ParseColour(tokenizer::iterator& _iterator);


};

#endif // PARSER_H
