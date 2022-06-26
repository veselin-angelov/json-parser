//
// Created by vesko on 07.06.22.
//

#ifndef JSON_PARSER_JSONVALIDATOR_H
#define JSON_PARSER_JSONVALIDATOR_H


#include <string>
#include <stdexcept>
#include "JSONExceptions.h"
#include <istream>


// Класът отговарящ за валидиране на данните
class JSONValidator
{
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
