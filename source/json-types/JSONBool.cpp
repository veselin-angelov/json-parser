//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONBool.h"
#include "../../headers/JSONParser.h"

JSONBool::JSONBool(bool value) : value(value)
{}

JSONBase* JSONBool::clone() const
{
    return new JSONBool(*this);
}

JSONBoolCreator::JSONBoolCreator() : JSONBaseCreator("tf")
{}

JSONBase* JSONBoolCreator::createJSONBase(std::istream &in) const
{
    return new JSONBool(JSONParser::parseBool(in));
}

static JSONBoolCreator __;
