//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONNULL_H
#define JSON_PARSER_JSONNULL_H


#include "JSONBase.h"

class JSONNull : public JSONBase
{
private:
    static const char* value;

public:
    JSONNull() = default;
    JSONBase* clone() const override;

public:
    void output(std::ostream &out, size_t level, bool isCompact) const override;
};


class JSONNullCreator : public JSONBaseCreator
{
public:
    JSONNullCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONNULL_H
