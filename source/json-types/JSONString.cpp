//
// Created by vesko on 12.06.22.
//

#include "../../headers/json-types/JSONString.h"
#include "../../headers/JSONParser.h"

JSONString::JSONString(const std::string &value) : value(value)
{}

JSONBase* JSONString::clone() const
{
    return new JSONString(*this);
}

JSONStringCreator::JSONStringCreator() : JSONBaseCreator("\"")
{}

JSONBase* JSONStringCreator::createJSONBase(std::istream &in) const
{
    return new JSONString(JSONParser::parseString(in));
}

static JSONStringCreator __;
