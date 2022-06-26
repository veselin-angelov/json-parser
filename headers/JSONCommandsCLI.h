//
// Created by vesko on 20.06.22.
//

#ifndef JSON_PARSER_JSONCOMMANDSCLI_H
#define JSON_PARSER_JSONCOMMANDSCLI_H


#include "JSON.h"


// Класът, от който се извикват командите въведени от конзолата
class JSONCommandsCLI
{
private:
    JSON &json;
    JSONArray searchResults;
    bool isCompact{false};

public:
    explicit JSONCommandsCLI(JSON &json);
    void run();

private:
    static JSONBase* createElement(const std::string &value);

    void print(const std::string &option = "", int index = -1) const;
    void search(const std::string &key);
    void edit(const std::string &elementPath, const std::string &value);
    void create(const std::string &elementPath, const std::string &value);
    void remove(const std::string &elementPath);
    void move(const std::string &fromPath, const std::string &toPath);
    void alignment(const std::string &option);
    void save(const std::string &fileName = "", const std::string &option = "", const std::string &optionValue = "", int index = -1);
};


#endif //JSON_PARSER_JSONCOMMANDSCLI_H
