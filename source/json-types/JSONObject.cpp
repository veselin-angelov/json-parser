//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONObject.h"

JSONObject::JSONObject(const std::vector<JSONPair> &values) : values(values)
{}

JSONBase* JSONObject::clone() const
{
    return new JSONObject(*this);
}

JSONObjectCreator::JSONObjectCreator() : JSONBaseCreator("{")
{}

JSONBase* JSONObjectCreator::createJSONBase(std::istream &in) const
{
    std::vector<JSONPair> values;

//    TODO detect {
    JSONPairCreator jsonPairCreator;
    JSONPair jsonPair = jsonPairCreator.createJSONPair(in);

    values.push_back(jsonPair);

    return new JSONObject(values);
}

static JSONObjectCreator __;
