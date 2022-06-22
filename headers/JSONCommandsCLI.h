//
// Created by vesko on 20.06.22.
//

#ifndef JSON_PARSER_JSONCOMMANDSCLI_H
#define JSON_PARSER_JSONCOMMANDSCLI_H


#include "JSON.h"

class JSONCommandsCLI
{
private:
    JSON &json;
    JSONArray searchResults;

public:
    explicit JSONCommandsCLI(JSON &json);
    void run();

private:
    static JSONBase* createElement(std::istream &in);

    void print() const;
    void search(std::istream &in);
    void edit(std::istream &in);
    void create(std::istream &in);
    void remove(std::istream &in);
    void move(std::istream &in);
};


#endif //JSON_PARSER_JSONCOMMANDSCLI_H
