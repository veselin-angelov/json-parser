//
// Created by vesko on 17.06.22.
//

#ifndef JSON_PARSER_JSONPAIR_H
#define JSON_PARSER_JSONPAIR_H


#include "JSONBase.h"


// Класът, който съхранвя двойките ключ и стойност
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

public:
    void output(std::ostream &out, size_t level, bool isCompact) const;
    void search(const std::string &key, std::vector<JSONBase *> &jsonArray) const;
    void edit(std::vector<std::string> &elements, JSONBase* value, size_t level);
    void create(std::vector<std::string> &elements, JSONBase* value, size_t level);
    void remove(std::vector<std::string> &elements, size_t level, bool toDelete);
    void findElement(std::vector<std::string> &elements, size_t level) const;

public:
    const std::string &getKey() const;
    const JSONBase* const getValue() const;
    JSONBase* getValue(){
        return value;
    }
};


class JSONPairCreator
{
public:
    static JSONPair* createJSONPair(std::istream &in);
};


#endif //JSON_PARSER_JSONPAIR_H
