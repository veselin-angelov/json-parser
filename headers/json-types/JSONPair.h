//
// Created by vesko on 17.06.22.
//

#ifndef JSON_PARSER_JSONPAIR_H
#define JSON_PARSER_JSONPAIR_H


#include "JSONBase.h"

class JSONPair
{
private:
    std::string key;
    JSONBase* value;

public:
    JSONPair(const std::string &key, JSONBase *value);
    virtual ~JSONPair();
    JSONPair(const JSONPair& other);
    JSONPair& operator=(const JSONPair& other);

    JSONPair* clone() const;
};


class JSONPairCreator
{
public:
    static JSONPair* createJSONPair(std::istream &in);
};


#endif //JSON_PARSER_JSONPAIR_H
