//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONARRAY_H
#define JSON_PARSER_JSONARRAY_H


#include <vector>
#include "JSONBase.h"


// JSON масив, наследяващ базовия клас
class JSONArray : public JSONBase
{
private:
    std::vector<JSONBase*> values;

private:
    void destroy();

public:
    JSONArray() = default;
    ~JSONArray() override;
    JSONArray(const JSONArray &other);
    JSONArray& operator=(const JSONArray &other);
    JSONBase* clone() const override;

public:
    void output(std::ostream &out, size_t level, bool isCompact) const override;
    void search(const std::string &key, std::vector<JSONBase*> &jsonArray) const override;
    void edit(std::vector<std::string> &elements, JSONBase *value, size_t level) override;
    void create(std::vector<std::string> &elements, JSONBase *value, size_t level) override;
    void remove(std::vector<std::string> &elements, size_t level, bool toDelete) override;
    const JSONBase* const findElement(std::vector<std::string> &elements, size_t level) const override;

public:
    const JSONBase* const operator[](size_t index) const;

public:
    std::vector<JSONBase*> &getValues();
    const std::vector<JSONBase*> &getValues() const;
};


class JSONArrayCreator : public JSONBaseCreator
{
public:
    JSONArrayCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONARRAY_H
