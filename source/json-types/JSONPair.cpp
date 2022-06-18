//
// Created by vesko on 17.06.22.
//

#include "../../headers/json-types/JSONPair.h"
#include "../../headers/JSONParser.h"
#include "../../headers/JSONFactory.h"

JSONPair::JSONPair(const std::string &key, JSONBase *value) : key(key), value(value)
{}

JSONPair::~JSONPair()
{
    delete value;
}

JSONPair::JSONPair(const JSONPair &other)
{
    this->key = other.key;
    this->value = other.value->clone();
}

JSONPair& JSONPair::operator=(const JSONPair &other)
{
    if (this != &other)
    {
        delete this->value;
        this->key = other.key;
        this->value = other.value->clone();
    }

    return *this;
}

JSONPair* JSONPair::clone() const
{
    return new JSONPair(*this);
}

JSONPair* JSONPairCreator::createJSONPair(std::istream &in)
{
    char c;
    std::string key = JSONParser::parseString(in);
    in >> c; // get the :
    JSONBase* jsonBase = JSONFactory::getFactory().createJSONBase(in);

    return new JSONPair(key, jsonBase);
}
