//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONObject.h"
#include "../../headers/Utilities.h"

void JSONObject::destroy()
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        delete values[i];
    }
}

JSONObject::JSONObject(const std::vector<JSONPair*> &values) : values(values)
{}

JSONObject::~JSONObject()
{
    destroy();
}

JSONObject::JSONObject(const JSONObject &other)
{
    this->values.resize(other.values.size());

    for (size_t i = 0; i < other.values.size(); ++i)
    {
        this->values.push_back(other.values[i]->clone());
    }
}

JSONObject &JSONObject::operator=(const JSONObject &other)
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

JSONBase* JSONObject::clone() const
{
    return new JSONObject(*this);
}

std::vector<JSONPair*> &JSONObject::getValues()
{
    return values;
}

JSONObjectCreator::JSONObjectCreator() : JSONBaseCreator("{")
{}

JSONBase* JSONObjectCreator::createJSONBase(std::istream &in) const
{
//    std::vector<JSONPair> values;
    JSONObject* jsonObject = new JSONObject();

    char c;
    in >> c; // get the {

    if (!Utilities::isObjectEmpty(in))
    {
        while (in.good())
        {
            JSONPair* jsonPair = JSONPairCreator::createJSONPair(in);
//        values.push_back(jsonPair);
            jsonObject->getValues().push_back(jsonPair);

            in >> c;

            if (c != ',') break;
        }
    }

//    return new JSONObject(values);
    return jsonObject;
}

static JSONObjectCreator __;
