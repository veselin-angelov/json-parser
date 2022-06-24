//
// Created by vesko on 17.06.22.
//

#include <iostream>
#include "../headers/JSONParser.h"
#include "../headers/Utilities.h"
#include "../headers/JSONFactory.h"

std::string JSONParser::parseString(std::istream &in)
{
    std::string input;
    char c;
    unsigned int quotesCount = 0;

    Utilities::clearWhiteSpaces(in);

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

void JSONParser::parseObject(std::istream &in, JSONObject *jsonObject)
{
    bool isDuplicate = false;
    char c;
    in >> c; // get the {

    if (!Utilities::isObjectEmpty(in))
    {
        while (in.good())
        {
            isDuplicate = false;
            JSONPair* jsonPair = JSONPairCreator::createJSONPair(in);

            for (JSONPair* &value : jsonObject->getValues())
            {
                if (value->getKey() == jsonPair->getKey())
                {
                    std::cout << "WARNING Duplicate key found: " << jsonPair->getKey() << std::endl;
                    delete value;
                    value = jsonPair;
                    isDuplicate = true;
                }
            }

            if (!isDuplicate) jsonObject->getValues().push_back(jsonPair);

            in >> c;

            if (c != ',') break;
        }
    }
}

void JSONParser::parseArray(std::istream &in, JSONArray *jsonArray)
{
    char c;
    in >> c; // get the [

    if (!Utilities::isArrayEmpty(in))
    {
        while (in.good())
        {
            JSONBase *jsonBase = JSONFactory::getFactory().createJSONBase(in);
            jsonArray->getValues().push_back(jsonBase);

            in >> c;

            if (c != ',') break;
        }
    }
}

std::vector<std::string> JSONParser::parseLineToStrings(const std::string &path, const std::string &key)
{
    std::vector<std::string> elements;

    size_t last = 0;
    size_t next = 0;

    while ((next = path.find_first_of(key, last)) != std::string::npos)
    {
        if (next - last > 0) elements.push_back(path.substr(last, next - last));
        last = next + 1;
    }

    // this is needed because in the while loop the last option after the last delimiter isn't set
    if (path.length() - last > 0) elements.push_back(path.substr(last));

    return elements;
}
