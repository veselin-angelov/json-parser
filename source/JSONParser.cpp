//
// Created by vesko on 17.06.22.
//

#include "../headers/JSONParser.h"

std::string JSONParser::parseString(std::istream &in)
{
    std::string input;
    char c;
    unsigned int quotesCount = 0;

    while (in.get(c))
    {
        if (c == '"')
        {
            quotesCount++;
        }
        else
        {
            input += c;
        }

        if (quotesCount == 2) break;

        if (c == '\\')
        {
            in.get(c);
            input += c;
        }
    }

    return input;
}

bool JSONParser::parseBool(std::istream &in)
{
    bool input;
    in >> std::boolalpha >> input;
    return input;
}

long double JSONParser::parseNumber(std::istream &in)
{
    long double number;
    in >> number;
    return number;
}
