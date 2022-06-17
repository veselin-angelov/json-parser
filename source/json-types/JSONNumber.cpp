//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONNumber.h"
#include "../../headers/JSONParser.h"

JSONNumber::JSONNumber(long double value) : value(value)
{}

JSONBase* JSONNumber::clone() const
{
    return new JSONNumber(*this);
}

JSONNumberCreator::JSONNumberCreator() : JSONBaseCreator("-0123456789")
{}

JSONBase* JSONNumberCreator::createJSONBase(std::istream &in) const
{
    return new JSONNumber(JSONParser::parseNumber(in));
}

static JSONNumberCreator __;
