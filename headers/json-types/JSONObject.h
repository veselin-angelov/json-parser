//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSONOBJECT_H
#define JSON_PARSER_JSONOBJECT_H


#include "JSONBase.h"
#include "JSONPair.h"
#include <iostream>


// Класът, който съхранява обелкти в себе си
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

//    class JSONObjectIterator : public Iterator
//    {
//        friend class JSONObject;
//
//    public:
//        Iterator *operator++() override;
//        Iterator *operator++(int i) override;
//
//        bool operator==(const Iterator* &other) const override;
//        bool operator!=(const Iterator* &other) const override;
//
//        JSONBase *operator*() const override;
//        JSONBase *operator*() override;
//
//    private:
//        explicit JSONObjectIterator(JSONBase* data) : Iterator(data) {
//            std::cout << "twa";
//        }
//    };
//
//    Iterator *begin() override;
//    Iterator *end() override;
};


class JSONObjectCreator : public JSONBaseCreator
{
public:
    JSONObjectCreator();
    JSONBase* createJSONBase(std::istream &in) const override;
};


#endif //JSON_PARSER_JSONOBJECT_H
