//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONBOOL_H
#define JSON_PARSER_JSONBOOL_H


#include "JSONBase.h"

class JSONBool : public JSONBase
{
private:
    bool value;

public:
    explicit JSONBool(bool value);
    JSONBase* clone() const override;

public:
    void output(std::ostream &out, size_t level, bool isCompact) const override;
};


class JSONBoolCreator : public JSONBaseCreator
{
public:
    JSONBoolCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};

#endif //JSON_PARSER_JSONBOOL_H
