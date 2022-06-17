//
// Created by vesko on 16.06.22.
//

#ifndef JSON_PARSER_JSONFACTORY_H
#define JSON_PARSER_JSONFACTORY_H


#include "json-types/JSONBase.h"

class JSONFactory
{
private:
    size_t count{};
    const JSONBaseCreator* creators[10];

private:
    const JSONBaseCreator* getCreator(const char c) const;

private:
    JSONFactory() = default;
    ~JSONFactory() = default;

public:
    JSONFactory(const JSONFactory&) = delete;
    JSONFactory& operator=(const JSONFactory&) = delete;

public:
    static JSONFactory& getFactory();
    void registerJSONBase(const JSONBaseCreator* creator);
    JSONBase* createJSONBase(std::istream &in);
};


#endif //JSON_PARSER_JSONFACTORY_H
