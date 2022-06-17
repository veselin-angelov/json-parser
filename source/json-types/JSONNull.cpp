//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONNull.h"

JSONBase* JSONNull::clone() const
{
    return new JSONNull();
}

const char* JSONNull::value = "null";

JSONNullCreator::JSONNullCreator() : JSONBaseCreator("n")
{}

JSONBase* JSONNullCreator::createJSONBase(std::istream &in) const
{
    return new JSONNull();
}

static JSONNullCreator __;
