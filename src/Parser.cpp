// Boost
#include "boost/random.hpp"
#include "boost/lexical_cast.hpp"

#include "Parser.h"

boost::char_separator<char> sep(" \t\r\n");

boost::mt19937 Generator;

boost::uniform_real<float> distributionPos(0.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

boost::uniform_real<float> distribution(-1.0f, 1.0f);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);

//----------------------------------------------------------------------------------------------------------------------
tokenizer::const_iterator Parser::GetTokenIterator(const std::string& _string) {
    // now tokenize the line
    tokenizer tokens(_string, sep);
    
    // and get the first token
    tokenizer::const_iterator tokenIterator = tokens.begin();
    return tokenIterator;
}

//----------------------------------------------------------------------------------------------------------------------
float Parser::ParseFloat(const std::string& _token) {
    if(_token.find("rand") < _token.length()) {
        if(_token.length() == 4) {
            return RandPosFloat();
        }
        return Parser::ParseRand(_token);//RandPosFloat();
    }
    return boost::lexical_cast<float>(_token);
}

//----------------------------------------------------------------------------------------------------------------------
float Parser::ParseRand(const std::string& _token) {
    bool positive = false;
    unsigned int splitPos = _token.find("*-");
    // if it doesn't have "*-" in it
    if(splitPos > _token.length()) {
        splitPos = _token.find("*");
        // if it doesn't have "*" in it
        if(splitPos > _token.length()) {
            return RandPosFloat();
        }
        positive = true;
    }
    std::string substr = _token.substr(splitPos+1, _token.length());
    float multiplier = boost::lexical_cast<float>(substr);
    // must have just "*" in it
    if(positive) {
        return RandPosFloat() * multiplier;
    }
    // must have "*-" in it
    else {
        return RandFloat() * multiplier;
    }
}

//----------------------------------------------------------------------------------------------------------------------
std::string Parser::StripBrackets(const std::string& _string) {
    return _string.substr(1, _string.size()-2);
}

//----------------------------------------------------------------------------------------------------------------------
unsigned int Parser::ParseUnsignedInt(const std::string& _token) {
    return boost::lexical_cast<unsigned int>(_token);
}

//----------------------------------------------------------------------------------------------------------------------
Vector Parser::ParseVector(tokenizer::const_iterator& _iterator) {
    // use lexical cast to convert to float then increment the itor
    float x = ParseFloat(*_iterator++);
    float y = ParseFloat(*_iterator++);
    float z = ParseFloat(*_iterator++);
    
    return Vector(x, y, z);
}

//----------------------------------------------------------------------------------------------------------------------
Colour Parser::ParseColour(tokenizer::const_iterator& _iterator) {
    // use lexical cast to convert to float then increment the itor
    float r = ParseFloat(_iterator++.current_token());
    float g = ParseFloat(_iterator++.current_token());
    float b = ParseFloat(_iterator++.current_token());
    
    return Colour(r, g, b);
}
