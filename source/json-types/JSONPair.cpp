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

void JSONPair::output(std::ostream &out, size_t level, bool isCompact) const
{
    out << '"' << key << '"' << (isCompact ? ":": ": ");
    value->output(out, level, isCompact);
}

void JSONPair::search(const std::string &key, std::vector<JSONBase*> &jsonArray) const
{
    value->search(key, jsonArray);
}


void JSONPair::edit(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    if (elements.size() == level)
    {
        delete this->value;
        this->value = value;
        return;
    }

    this->value->edit(elements, value, level);
}

void JSONPair::create(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    this->value->create(elements, value, level);
}

void JSONPair::remove(std::vector<std::string> &elements, size_t level, bool toDelete)
{
    this->value->remove(elements, level, toDelete);
}

const JSONBase *const JSONPair::findElement(std::vector<std::string> &elements, size_t level) const
{
    return this->value->findElement(elements, level);
}

const std::string &JSONPair::getKey() const
{
    return key;
}

const JSONBase* const JSONPair::getValue() const
{
    return value;
}

JSONPair* JSONPairCreator::createJSONPair(std::istream &in)
{
    char c;
    std::string key = JSONParser::parseString(in);
    in >> c; // get the :
    JSONBase* jsonBase = JSONFactory::getFactory().createJSONBase(in);

    return new JSONPair(key, jsonBase);
}
