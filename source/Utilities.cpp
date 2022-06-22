//
// Created by vesko on 17.06.22.
//

#include "../headers/Utilities.h"

void Utilities::clearWhiteSpaces(std::istream &in)
{
    char c;

    do
    {
        in.get(c);
    }
    while(isspace(c));

    in.unget();
}

bool Utilities::isObjectEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == '}') return true;

    in.unget();

    return false;
}

bool Utilities::isArrayEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == ']') return true;

    in.unget();

    return false;
}