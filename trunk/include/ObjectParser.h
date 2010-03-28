#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H

#include "Parser.h"

class ObjectParser : public Parser
{
public:
    ObjectParser();
    ObjectParser(std::string _filename);
private:
    void ParseFile(std::string _fileName);
};

#endif // OBJECTPARSER_H
