//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONOBJECT_H
#define JSON_PARSER_JSONOBJECT_H


#include "JSONBase.h"
#include "JSONPair.h"

class JSONObject : public JSONBase
{
private:
    std::vector<JSONPair*> values;

private:
    void destroy();

public:
    JSONObject() = default;
    explicit JSONObject(const std::vector<JSONPair*> &values);
    ~JSONObject() override;
    JSONObject(const JSONObject &other);
    JSONObject& operator=(const JSONObject &other);

    JSONBase* clone() const override;

public:
    std::vector<JSONPair*> &getValues();
};


class JSONObjectCreator : public JSONBaseCreator
{
public:
    JSONObjectCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONOBJECT_H
