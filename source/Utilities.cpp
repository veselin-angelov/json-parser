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

    in.seekg(-1, std::ios_base::cur);
}

bool Utilities::isObjectEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == '}') return true;

    in.seekg(-1, std::ios_base::cur);

    return false;
}

bool Utilities::isArrayEmpty(std::istream &in)
{
    char c;
    in >> c;

    if (c == ']') return true;

    in.seekg(-1, std::ios_base::cur);

    return false;
}