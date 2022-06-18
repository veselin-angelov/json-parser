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

private:
    void destroy();

public:
    JSONArray() = default;
    explicit JSONArray(const std::vector<JSONBase*> &values);
    ~JSONArray() override;
    JSONArray(const JSONArray &other);
    JSONArray& operator=(const JSONArray &other);

    JSONBase* clone() const override;

public:
    std::vector<JSONBase*> &getValues();
};


class JSONArrayCreator : public JSONBaseCreator
{
public:
    JSONArrayCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONARRAY_H
