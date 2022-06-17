//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONARRAY_H
#define JSON_PARSER_JSONARRAY_H


#include <vector>
#include "JSONBase.h"

class JSONArray : public JSONBase
{
private:
    std::vector<JSONBase*> values;
};


#endif //JSON_PARSER_JSONARRAY_H
