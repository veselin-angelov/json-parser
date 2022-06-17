//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONOBJECT_H
#define JSON_PARSER_JSONOBJECT_H


#include "JSONBase.h"
#include "JSONPair.h"

class JSONObject : public JSONBase  // TODO HOW TO GET KEY AND KNOW ITS AN OBJECT NOT STRING
{
private:
    std::vector<JSONPair> values;

public:
//    JSONObject() = default;
    explicit JSONObject(const std::vector<JSONPair> &values);
    JSONBase* clone() const override;
};


class JSONObjectCreator : public JSONBaseCreator
{
public:
    JSONObjectCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONOBJECT_H
