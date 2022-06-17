//
// Created by vesko on 12.06.22.
//

#ifndef JSON_PARSER_JSONBASE_H
#define JSON_PARSER_JSONBASE_H


#include <string>
#include <vector>
#include <istream>
#include <cstring>

class JSONBase
{
public:
    virtual ~JSONBase() = default;
    virtual JSONBase* clone() const = 0;
};

class JSONBaseCreator
{
private:
    const char* const keyChars;

public:
    explicit JSONBaseCreator(const char* keyChars);
    virtual ~JSONBaseCreator() = default;

    JSONBaseCreator(const JSONBaseCreator&) = delete;
    JSONBaseCreator& operator=(const JSONBaseCreator&) = delete;

    const char* getKeyChars() const;

    virtual JSONBase* createJSONBase(std::istream &in) const = 0;
};


#endif //JSON_PARSER_JSONBASE_H
