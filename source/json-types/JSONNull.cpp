//
// Created by vesko on 15.06.22.
//

#include "../../headers/json-types/JSONNull.h"

const char* JSONNull::value = "null";

JSONBase* JSONNull::clone() const
{
    return new JSONNull();
}

void JSONNull::output(std::ostream &out, size_t level, bool isCompact) const
{
    out << value;
}

JSONNullCreator::JSONNullCreator() : JSONBaseCreator("n")
{}

JSONBase* JSONNullCreator::createJSONBase(std::istream &in) const
{
    return new JSONNull();
}

static JSONNullCreator __;
