//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONNUMBER_H
#define JSON_PARSER_JSONNUMBER_H


#include "JSONBase.h"

class JSONNumber : public JSONBase
{
private:
    long double value;

public:
    explicit JSONNumber(long double value);

    JSONBase* clone() const override;
    void output(std::ostream &out, size_t level, bool isCompact) const override;
};


class JSONNumberCreator : public JSONBaseCreator
{
public:
    JSONNumberCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONNUMBER_H
