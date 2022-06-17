//
// Created by vesko on 15.06.22.
//

#ifndef JSON_PARSER_JSON_H
#define JSON_PARSER_JSON_H


#include <istream>
#include "json-types/JSONBase.h"

class JSON
{
private:
    std::string fileName;  // TODO maybe remove
    JSONBase* json;

private:
    void parseJSON(std::istream &in);

public:
    explicit JSON(std::string &fileName);

};


#endif //JSON_PARSER_JSON_H
