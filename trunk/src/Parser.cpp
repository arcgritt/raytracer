#include "Parser.h"


// Boost
#include "boost/random.hpp"
#include "boost/lexical_cast.hpp"

boost::char_separator<char> sep(" \t\r\n");

boost::mt19937 Generator;

boost::uniform_real<float> distributionPos(0.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

boost::uniform_real<float> distribution(-1.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);


Parser::Parser()
{
}

tokenizer::iterator Parser::GetTokenIterator(std::string _line)
{
    // now tokenize the line
    tokenizer tokens(_line, sep);

    // and get the first token
    tokenizer::iterator tokenIterator = tokens.begin();
    return tokenIterator;
}

float Parser::ParseFloat(std::string _token)
{
    //Util util;
    //if()
    if(_token.find("rand") != _token.npos)
    {
        if(_token.npos == 4)
        {
            return RandPosFloat();
        }
        return Parser::ParseRand(_token);//RandPosFloat();
    }
    return boost::lexical_cast<float>(_token);
}

float Parser::ParseRand(std::string _token)
{
    bool positive = false;
    unsigned int splitPos = _token.find("*-");
    if(splitPos == _token.npos)
    {
        splitPos = _token.find("*");
        if(splitPos == _token.npos)
        {
            return RandPosFloat();
        }
        positive = true;
    }

    std::string substr = _token.substr(splitPos+1, _token.npos);
    float multiplier = boost::lexical_cast<float>(substr);
    if(positive)
    {
        return RandPosFloat() * multiplier;
    }
    else
    {
        return RandFloat() * multiplier;
    }
}
