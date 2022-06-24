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
    ~JSONObject() override;
    JSONObject(const JSONObject &other);
    JSONObject& operator=(const JSONObject &other);
    JSONBase* clone() const override;

public:
    void output(std::ostream &out, size_t level, bool isCompact) const override;
    void search(const std::string &key, std::vector<JSONBase *> &jsonArray) const override;
    void edit(std::vector<std::string> &elements, JSONBase *value, size_t level) override;
    void create(std::vector<std::string> &elements, JSONBase *value, size_t level) override;
    void remove(std::vector<std::string> &elements, size_t level, bool toDelete) override;
    const JSONBase* const findElement(std::vector<std::string> &elements, size_t level) const override;

public:
    JSONPair* operator[](const std::string &key);
    const JSONPair* const operator[](const std::string &key) const;

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
