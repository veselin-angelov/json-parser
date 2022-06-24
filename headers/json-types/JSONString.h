//
// Created by vesko on 12.06.22.
//

#ifndef JSON_PARSER_JSONSTRING_H
#define JSON_PARSER_JSONSTRING_H


#include "JSONBase.h"

class JSONString : public JSONBase
{
private:
    std::string value;

public:
    explicit JSONString(const std::string &value);
    JSONBase* clone() const override;

public:
    void output(std::ostream &out, size_t level, bool isCompact) const override;
};


class JSONStringCreator : public JSONBaseCreator
{
public:
    JSONStringCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONSTRING_H
