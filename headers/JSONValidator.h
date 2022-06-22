//
// Created by vesko on 07.06.22.
//

#ifndef JSON_PARSER_JSONVALIDATOR_H
#define JSON_PARSER_JSONVALIDATOR_H


#include <string>
#include <stdexcept>
#include "JSONExceptions.h"
#include <istream>
#include <iostream> // TODO remove

// TODO validate unique and remove const static chars

class JSONValidator
{
private:
    const static char BEGIN_OBJECT = '{';
    const static char END_OBJECT = '}';
    const static char BEGIN_ARRAY = '[';
    const static char END_ARRAY = ']';

    const static char NAME_SEPARATOR = ':';
    const static char VALUES_SEPARATOR = ',';

    const static char STRING_QUOTE = '"';

private:
    static void validateEscapeChar(std::istream &in);

    static void validateType(std::istream &in);

    static void validateNumber(std::istream &in);
    static void validateBool(std::istream &in);
    static void validateNull(std::istream &in);
    static void validateString(std::istream &in);
    static void validateObject(std::istream &in);
    static void validateArray(std::istream &in);

public:
    static void validate(std::istream &in);
};


#endif //JSON_PARSER_JSONVALIDATOR_H
