//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSON_H
#define JSON_PARSER_JSON_H


#include <istream>
#include <iostream>
#include <fstream>
#include <exception>
#include "json-types/JSONBase.h"
#include "json-types/JSONArray.h"
#include "json-types/JSONObject.h"


class JSON
{
private:
    std::string fileName;
    JSONBase* json;

private:
    void parseJSON(std::istream &in);

public:
    explicit JSON(const std::string &fileName);
    virtual ~JSON();

public:
    void print() const;
    JSONArray search(const std::string &key) const;
    void edit(std::vector<std::string> &elements, JSONBase* value);
    void create(std::vector<std::string> &elements, JSONBase* value);
    void remove(std::vector<std::string> &elements);
    void move(std::vector<std::string> &from, std::vector<std::string> &to);
    void save(bool isCompact, const std::string &fileName = "") const;
    const JSONBase* const findElement(std::vector<std::string> &elements) const;

    void test()
    {
        for (auto i = json->begin(); i < json->end(); i++)
        {
            std::cout << i << std::endl;
//            (*(*i))->output(std::cout, 1, false);
        }
    }
};


#endif //JSON_PARSER_JSON_H
