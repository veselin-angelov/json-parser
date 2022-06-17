//
// Created by vesko on 17.06.22.
//

#ifndef JSON_PARSER_JSONPARSER_H
#define JSON_PARSER_JSONPARSER_H


#include <istream>
#include <string>

class JSONParser
{
public:
    static std::string parseString(std::istream &in);
    static bool parseBool(std::istream &in);
    static long double parseNumber(std::istream &in);
};


#endif //JSON_PARSER_JSONPARSER_H
