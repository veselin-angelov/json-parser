//
// Created by vesko on 17.06.22.
//

#include "../../headers/json-types/JSONPair.h"
#include "../../headers/JSONParser.h"
#include "../../headers/JSONFactory.h"

JSONPair::JSONPair(const std::string &key, JSONBase *value) : key(key), value(value->clone())
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

//JSONBase* JSONPair::clone() const
//{
//    return new JSONPair(*this);
//}

JSONPairCreator::JSONPairCreator()  // pair starts with " like a string and can only exist inside an object, so it shouldn't be in the factory
{}

JSONPair JSONPairCreator::createJSONPair(std::istream &in) const
{
    std::string key = JSONParser::parseString(in);
    JSONBase* jsonBase = JSONFactory::getFactory().createJSONBase(in);

    return JSONPair(key, jsonBase);
}
