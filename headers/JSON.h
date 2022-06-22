//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSON_H
#define JSON_PARSER_JSON_H


#include <istream>
#include <fstream>
#include <exception>
#include "json-types/JSONBase.h"
#include "json-types/JSONArray.h"

class JSON
{
private:
    std::string fileName;  // TODO maybe remove
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
};


#endif //JSON_PARSER_JSON_H
