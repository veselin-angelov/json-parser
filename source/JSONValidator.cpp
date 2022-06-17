//
// Created by vesko on 07.06.22.
//

#include "../headers/JSONValidator.h"

void JSONValidator::clearWhiteSpaces(std::istream &in)
{
    char c;

    do
    {
        in.get(c);
    }
    while(isspace(c));

    in.seekg(-1, std::ios_base::cur);
}

void JSONValidator::validateEscapeChar(std::istream &in)
{
    char c;

    in.get(c);

    if (c != '"' && c != '\\' && c != '/' && c != 'b' && c != 'f' && c != 'n' && c != 'r' && c != 't' && c != 'u')
    {
        throw InvalidTypeException("Invalid escaped char.", in.tellg());
    }
    if (c == 'u')
    {
        for (int i = 0; i < 4; ++i)
        {
            in.get(c);
            if (!isalnum(c))
            {
                throw InvalidTypeException("Invalid escaped hex.", in.tellg());
            }
        }
    }
}

bool JSONValidator::isObjectEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == END_OBJECT) return true;

    in.seekg(-1, std::ios_base::cur);

    return false;
}

bool JSONValidator::isArrayEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == END_ARRAY) return true;

    in.seekg(-1, std::ios_base::cur);

    return false;
}

void JSONValidator::validateType(std::istream& in)
{
    char c;
    in >> c;

    in.seekg(-1, std::ios_base::cur); // Move the cursor back because we need the data for further validating

    if (c == '-' || (c >= '0' && c <= '9')) validateNumber(in);
    else if (c == 't' || c == 'f') validateBool(in);
    else if (c == 'n') validateNull(in);
    else if (c == '"') validateString(in);
    else if (c == '{') validateObject(in);
    else if (c == '[') validateArray(in);
    else throw InvalidTypeException("Expected correct JSON value.", in.tellg());
}

void JSONValidator::validateNumber(std::istream &in)
{
    long double number;
    in >> number;

    if (in.fail())
    {
        in.clear();
        throw InvalidTypeException("Invalid number format.", in.tellg());
    }
}

void JSONValidator::validateBool(std::istream &in)
{
    bool b;
    in >> std::boolalpha >> b;

    if (in.fail())
    {
        in.clear();
        throw InvalidTypeException("Invalid value.", in.tellg());
    }
}

void JSONValidator::validateNull(std::istream &in)
{
    std::string null;
    char c;

    for (int i = 0; i < 4; ++i)
    {
        in.get(c);
        null += c;
    }

    if (null != "null")
    {
        throw InvalidTypeException("Invalid value.", in.tellg());
    }
}

void JSONValidator::validateString(std::istream &in)
{
    char c;
    unsigned int quotesCount = 0;

    clearWhiteSpaces(in);

    while (in.get(c))
    {
        if (c == '\\') validateEscapeChar(in);

        if (c == '"') quotesCount++;

        if (quotesCount == 2 || c == '\n') break;
    }

    if (quotesCount != 2)
    {
        throw InvalidTypeException("String value not correct.", in.tellg());
    }
}

void JSONValidator::validateObject(std::istream &in)
{
    char c;
    in >> c;

    if (c != BEGIN_OBJECT)
    {
        throw InvalidTypeException("Object must start with a {.");
    }

    if (isObjectEmpty(in)) return;

    while (in.good())
    {
        validateString(in);

        in >> c;

        if (c != NAME_SEPARATOR)
        {
            throw InvalidTypeException("Key-value pair should be separated with colon. ", in.tellg());
        }

        validateType(in);

        in >> c;

        if (c == VALUES_SEPARATOR)
        {
            in >> c;

            if (c != STRING_QUOTE)
            {
                throw InvalidTypeException("A valid key is expected after a comma.", in.tellg());
            }

            in.seekg(-1, std::ios_base::cur);
        }
        else
        {
            break;
        }
    }

    if (c != END_OBJECT)
    {
        throw InvalidTypeException("Object must end with a }.", in.tellg());
    }
}

void JSONValidator::validateArray(std::istream &in)
{
    char c;
    in >> c;

    if (c != BEGIN_ARRAY)
    {
        throw InvalidTypeException("Array must start with a [.", in.tellg());
    }

    if (isArrayEmpty(in)) return;

    while (in.good())
    {
        validateType(in);

        in >> c;

        if (c == NAME_SEPARATOR)
        {
            throw InvalidTypeException("Expected comma or ], not colon.", in.tellg());
        }

        if (c != VALUES_SEPARATOR)
        {
            break;
        }
    }

    if (c != END_ARRAY)
    {
        throw InvalidTypeException("Array must end with a ].", in.tellg());
    }
}

void JSONValidator::validate(std::istream& in)
{
    char c;

    validateType(in);

    while (in.get(c))
    {
        if (!isspace(c))
        {
            throw MultipleJSONRootElementsException();
        }
    }
}
