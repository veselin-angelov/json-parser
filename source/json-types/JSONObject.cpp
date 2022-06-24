//
// Created by vesko on 15.06.22.
//

#include <cassert>
#include <iostream>
#include "../../headers/json-types/JSONObject.h"
#include "../../headers/Utilities.h"
#include "../../headers/JSONExceptions.h"
#include "../../headers/JSONParser.h"

void JSONObject::destroy()
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        delete values[i];
    }
}

JSONObject::~JSONObject()
{
    destroy();
}

JSONObject::JSONObject(const JSONObject &other)
{
    this->values.reserve(other.values.size());

    for (size_t i = 0; i < other.values.size(); ++i)
    {
        this->values.push_back(other.values[i]->clone());
    }
}

JSONObject &JSONObject::operator=(const JSONObject &other)
{
    if (this != &other)
    {
        destroy();
        this->values = std::vector<JSONPair*>();
        this->values.reserve(other.values.size());

        for (size_t i = 0; i < other.values.size(); ++i)
        {
            this->values.push_back(other.values[i]->clone());
        }
    }

    return *this;
}

JSONBase* JSONObject::clone() const
{
    return new JSONObject(*this);
}

void JSONObject::output(std::ostream &out, size_t level, bool isCompact) const
{
    assert(level > 0);

    out << "{";

    for (size_t i = 0; i < values.size(); ++i)
    {
        if (!isCompact) out << '\n' << std::string(level, '\t');
        values[i]->output(out, level + 1, isCompact);
        if (i == values.size() - 1) out << (!isCompact ? "\n": "");
        else out << ",";
    }

    if (!isCompact && !values.empty()) out << std::string(level - 1, '\t');
    out << "}";
}

void JSONObject::search(const std::string &key, std::vector<JSONBase*> &jsonArray) const
{
    for (JSONPair* const &value : values)
    {
        if (value->getKey() == key)
        {
            jsonArray.push_back(value->getValue()->clone());
        }

        value->search(key, jsonArray);
    }
}

void JSONObject::edit(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    JSONPair* jsonPair = this->operator[](elements[level]);

    if (jsonPair)
    {
        jsonPair->edit(elements, value, level + 1);
        return;
    }

    throw ElementNotFound(elements[level]);
}

void JSONObject::create(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    JSONPair* jsonPair = this->operator[](elements[level]);

    if (elements.size() - 1 == level)
    {
        if (!jsonPair)
        {
            JSONPair* newJsonPair = new JSONPair(elements[level], value);
            values.push_back(newJsonPair);
            return;
        }

        throw ElementAlreadyExists(elements[level]);
    }
    else if (jsonPair)
    {
        jsonPair->create(elements, value, level + 1);
        return;
    }

    throw ElementNotFound(elements[level]);
}

void JSONObject::remove(std::vector<std::string> &elements, size_t level, bool toDelete)
{
    JSONPair* jsonPair = this->operator[](elements[level]);

    if (elements.size() - 1 == level)
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (values[i]->getKey() == elements[level])
            {
                if (toDelete) delete values[i];
                values.erase(values.begin() + i);
                return;
            }
        }
    }
    else if (jsonPair)
    {
        jsonPair->remove(elements, level + 1, toDelete);
        return;
    }

    throw ElementNotFound(elements[level]);
}

const JSONBase* const JSONObject::findElement(std::vector<std::string> &elements, size_t level) const
{
    const JSONPair* jsonPair = this->operator[](elements[level]);

    if (jsonPair)
    {
        if (elements.size() - 1 == level)
        {
            return jsonPair->getValue();
        }
        jsonPair->findElement(elements, level + 1);
    }

    return nullptr;
}

JSONPair* JSONObject::operator[](const std::string &key)
{
    for (JSONPair* const &value : values)
    {
        if (value->getKey() == key)
        {
            return value;
        }
    }

    return nullptr;
}

const JSONPair * const JSONObject::operator[](const std::string &key) const
{
    for (JSONPair* const &value : values)
    {
        if (value->getKey() == key)
        {
            return value;
        }
    }

    return nullptr;
}

std::vector<JSONPair*> &JSONObject::getValues()
{
    return values;
}

JSONBase::Iterator *JSONObject::begin()
{
    return new JSONObjectIterator(values[0]->getValue());
}

JSONBase::Iterator *JSONObject::end()
{
    return new JSONObjectIterator(values[values.size() - 1]->getValue());
}

JSONObjectCreator::JSONObjectCreator() : JSONBaseCreator("{")
{}

JSONBase* JSONObjectCreator::createJSONBase(std::istream &in) const
{
    JSONObject* jsonObject = new JSONObject();
    JSONParser::parseObject(in, jsonObject);
    return jsonObject;
}

static JSONObjectCreator __;

JSONBase::Iterator *JSONObject::JSONObjectIterator::operator++()
{
    std::cout << ptr;
    ++ptr;
    return this;
}

JSONBase::Iterator *JSONObject::JSONObjectIterator::operator++(int i)
{
    std::cout << ptr;
    Iterator* current = this;
    ++(*this);
    return current;
}

bool JSONObject::JSONObjectIterator::operator==(const JSONBase::Iterator* &other) const
{
    const JSONObjectIterator* jsonObjectIterator = dynamic_cast<const JSONObjectIterator*>(other);

    if (jsonObjectIterator)
    {
        return ptr == jsonObjectIterator->ptr;
    }
    return false;
}

bool JSONObject::JSONObjectIterator::operator!=(const JSONBase::Iterator* &other) const
{
    return !(*this == other);
}

JSONBase *JSONObject::JSONObjectIterator::operator*() const
{
    return ptr;
}

JSONBase *JSONObject::JSONObjectIterator::operator*()
{
    return ptr;
}
