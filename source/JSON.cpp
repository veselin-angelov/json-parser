//
// Created by vesko on 15.06.22.
//

#include "../headers/JSON.h"
#include "../headers/JSONValidator.h"
#include "../headers/JSONFactory.h"

JSON::JSON(const std::string &fileName) : fileName(fileName)
{
//    1. OPEN file
    std::ifstream file(this->fileName);
    if (!file.is_open()) throw std::runtime_error("File failed");
//    2. Validate json
    JSONValidator::validate(file);
//    3. Move cursor to the beginning of file
    file.clear();
    file.seekg(0);
//    4. Parse json
    parseJSON(file);
//    5. Close file
    file.close();
//    TODO CHECK FOR FILE STATE
}

JSON::~JSON()
{
    delete json;
}

void JSON::parseJSON(std::istream &in)
{
    this->json = JSONFactory::getFactory().createJSONBase(in);
}
