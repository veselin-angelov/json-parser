//
// Created by vesko on 17.06.22.
//

#ifndef JSON_PARSER_JSONPARSER_H
#define JSON_PARSER_JSONPARSER_H


#include <istream>
#include <string>
#include <vector>
#include "json-types/JSONObject.h"
#include "json-types/JSONArray.h"


// Класът, в който са методите, използвани от всеки клас, за да създаде обект от файл
class JSONParser
{
public:
    static std::string parseString(std::istream &in);
    static bool parseBool(std::istream &in);
    static long double parseNumber(std::istream &in);
    static void parseObject(std::istream &in, JSONObject *jsonObject);
    static void parseArray(std::istream &in, JSONArray *jsonArray);

    static std::vector<std::string> parseLineToStrings(const std::string &path, const std::string &key);
};


#endif //JSON_PARSER_JSONPARSER_H
