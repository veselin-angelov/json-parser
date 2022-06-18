//
// Created by vesko on 17.06.22.
//

#ifndef JSON_PARSER_UTILITIES_H
#define JSON_PARSER_UTILITIES_H


#include <istream>

class Utilities
{
public:
    static void clearWhiteSpaces(std::istream &in);
    static bool isObjectEmpty(std::istream &in);
    static bool isArrayEmpty(std::istream &in);
};


#endif //JSON_PARSER_UTILITIES_H
