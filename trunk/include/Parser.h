#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "boost/tokenizer.hpp"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class Parser
{
public:
    Parser();
protected:
    static tokenizer::iterator GetTokenIterator(std::string _line);
    virtual void ParseFile(std::string _fileName) =0;
    static float ParseFloat(std::string _token);
    static float ParseRand(std::string _token);
};

#endif // PARSER_H
