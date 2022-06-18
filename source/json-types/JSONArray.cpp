//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONArray.h"
#include "../../headers/JSONFactory.h"
#include "../../headers/Utilities.h"

void JSONArray::destroy()
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        delete values[i];
    }
}

JSONArray::JSONArray(const std::vector<JSONBase*> &values) : values(values)
{}

JSONArray::~JSONArray()
{
    destroy();
}

JSONArray::JSONArray(const JSONArray &other)
{
    this->values.resize(other.values.size());

    for (size_t i = 0; i < other.values.size(); ++i)
    {
        this->values.push_back(other.values[i]->clone());
    }
}

JSONArray &JSONArray::operator=(const JSONArray &other)
{
    if (this != &other)
    {
        destroy(); // does that make size = 0

//        TODO check size

        this->values.resize(other.values.size());

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

std::vector<JSONBase *> &JSONArray::getValues()
{
    return values;
}

JSONArrayCreator::JSONArrayCreator() : JSONBaseCreator("[")
{}

JSONBase* JSONArrayCreator::createJSONBase(std::istream &in) const
{
//    std::vector<JSONBase*> values;
    JSONArray* jsonArray = new JSONArray();

    char c;
    in >> c; // get the [

    if (!Utilities::isArrayEmpty(in))
    {
        while (in.good())
        {
            JSONBase *jsonBase = JSONFactory::getFactory().createJSONBase(in);
//            values.push_back(jsonBase);
            jsonArray->getValues().push_back(jsonBase);

            in >> c;

            if (c != ',') break;
        }
    }

//    return new JSONArray(values);
    return jsonArray;
}

static JSONArrayCreator __;
