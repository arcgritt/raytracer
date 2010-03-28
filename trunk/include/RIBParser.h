#ifndef RIBPARSER_H
#define RIBPARSER_H

#include <string>
#include <fstream>

#include "boost/tokenizer.hpp"

#include "Parser.h"
#include "Material.h"
#include "Scene.h"

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class RIBParser : public Parser
{
public:
    RIBParser();

    static Scene ParseFile(std::string _fileName);

private:
    static Scene ParseHeader(std::ifstream &_ribFileStream);

    static void ParseWorld(std::ifstream &_ribFileStream, Scene& _scene);

};

#endif // RIBPARSER_H
