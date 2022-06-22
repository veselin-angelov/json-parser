//
// Created by vesko on 15.06.22.
//

#include <cassert>
#include "../../headers/json-types/JSONArray.h"
#include "../../headers/Utilities.h"
#include "../../headers/JSONExceptions.h"
#include "../../headers/JSONParser.h"

void JSONArray::destroy()
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        delete values[i];
    }
}

//JSONArray::JSONArray(const std::vector<JSONBase*> &values) : values(values)
//{}

JSONArray::~JSONArray()
{
    destroy();
}

JSONArray::JSONArray(const JSONArray &other)
{
    this->values.reserve(other.values.size());

    for (size_t i = 0; i < other.values.size(); ++i)
    {
        this->values.push_back(other.values[i]->clone());
    }
}

JSONArray &JSONArray::operator=(const JSONArray &other)
{
    if (this != &other)
    {
        destroy();
        this->values = std::vector<JSONBase*>();
        this->values.reserve(other.values.size());

        for (size_t i = 0; i < other.values.size(); ++i)
        {
            this->values.push_back(other.values[i]->clone());
        }
    }

    return *this;
}

JSONBase *JSONArray::clone() const
{
    return new JSONArray(*this);
}

void JSONArray::output(std::ostream &out, size_t level, bool isCompact) const
{
    assert(level > 0);

    out << "[";

    for (size_t i = 0; i < values.size(); ++i)
    {
        if (!isCompact) out << '\n' << std::string(level, '\t');
        values[i]->output(out, level + 1, isCompact);
        if (i == values.size() - 1) out << (!isCompact ? "\n": "");
        else out << ",";
    }

    if (!isCompact && !values.empty()) out << std::string(level - 1, '\t');
    out << "]";
}

void JSONArray::search(const std::string &key, std::vector<JSONBase*> &jsonArray) const
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        values[i]->search(key, jsonArray);
    }
}

void JSONArray::edit(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    size_t index = std::stoi(elements[level]);

    if (values.at(index))
    {
        if (elements.size() - 1 == level)
        {
            delete values[index];
            values[index] = value;
            return;
        }

        values[index]->edit(elements, value, level + 1);
        return;
    }

    throw ElementNotFound(elements[level]);
}

void JSONArray::create(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    size_t index = std::stoi(elements[level]);

    if (index >= values.size() && elements.size() - 1 == level)
    {
        values.push_back(value);
        return;
    }
    else if (index < values.size() && elements.size() - 1 != level)
    {
        values[index]->create(elements, value, level + 1);
        return;
    }

    throw ElementAlreadyExists(elements[level]);
}

void JSONArray::remove(std::vector<std::string> &elements, size_t level)
{
    size_t index = std::stoi(elements[level]);

    if (index < values.size() && elements.size() - 1 == level)
    {
        delete values[index];
        values.erase(values.begin() + index);
        return;
    }
    else if (index < values.size() && elements.size() - 1 != level)
    {
        values[index]->remove(elements, level + 1);
        return;
    }

    throw ElementNotFound(elements[level]);
}

const JSONBase* const JSONArray::findElement(std::vector<std::string> &elements, size_t level) const
{
    size_t index = std::stoi(elements[level]);

    if (index < values.size() && elements.size() - 1 == level)
    {
        return values[index];
    }
    else if (index < values.size() && elements.size() - 1 != level)
    {
        return values[index]->findElement(elements, level + 1);
    }

    return nullptr;
}

const JSONBase* const JSONArray::operator[](size_t index) const
{
    if (index >= values.size())
    {
        throw std::out_of_range("Index out of range!");
    }

    return values[index];
}

std::vector<JSONBase *> &JSONArray::getValues()
{
    return values;
}

JSONArrayCreator::JSONArrayCreator() : JSONBaseCreator("[")
{}

JSONBase* JSONArrayCreator::createJSONBase(std::istream &in) const
{
    JSONArray* jsonArray = new JSONArray();
    JSONParser::parseArray(in, jsonArray);
    return jsonArray;
}

static JSONArrayCreator __;
