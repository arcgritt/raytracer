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

protected:
    /// \brief returns a token iterator positioned at the first token
    /// @param[in] _line       the string to tokenise and return as an iterator
    /// \returns a token iterator positioned at the first token
    static tokenizer::iterator GetTokenIterator(const std::string& _string);

    /// \brief returns a new string with the first and last characters removed
    /// @param[in] _string      the string to remove the characters from
    /// \returns a new string with the first and last characters removed
    static std::string StripBrackets(const std::string& _string);

    /// \brief parses a token which represents a random number
    /**
      Parses a token which represents a random number. Examples:
      "rand" - returns a random number between 0.0f and 1.0f
      "rand*-10" - returns a random number between -10.0f and 10.0f
      "rand*10" - returns a random number between 0.0f and 10.0f
      */
    /// @param[in] _token       the token the parse
    /// \returns a random float as specified by the token
    static float ParseRand(const std::string& _token);

    /// \brief converts a string to a float
    /// @param[in] _token       the string to be converted to a float
    /// \returns a float equal to the value represented by the string
    static float ParseFloat(const std::string& _token);

    /// \brief converts a string to an unsigned integer
    /// @param[in] _token       the string to be converted to an unsigned integer
    /// \returns an unsigned integer equal to the value represented by the string
    static unsigned int ParseUnsignedInt(const std::string& _token);

    /// \brief converts a sequence of strings, stored in a token iterator, to a Vector
    /// @param[in] _iterator    the iterator containing the strings
    /// \returns a Vector equal to the value represented by strings stored in the token iterator
    static Vector ParseVector(tokenizer::iterator& _iterator);

    /// \brief converts a sequence of strings, stored in a token iterator, to a Colour
    /// @param[in] _iterator    the iterator containing the strings
    /// \returns a Colour equal to the value represented by strings stored in the token iterator
    static Colour ParseColour(tokenizer::iterator& _iterator);
};

#endif // PARSER_H
