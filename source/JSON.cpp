//
// Created by vesko on 15.06.22.
//

#include "../headers/JSON.h"
#include "../headers/JSONValidator.h"
#include "../headers/JSONFactory.h"
#include "../headers/JSONParser.h"

JSON::JSON(const std::string &fileName) : fileName(fileName)
{
    std::ifstream file;

    try
    {
//    1. OPEN file
        file.open(this->fileName);
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
    }
    catch (...)
    {
        delete json;
        file.close();
        throw;
    }
}

JSON::~JSON()
{
    delete json;
}

void JSON::parseJSON(std::istream &in)
{
    this->json = JSONFactory::getFactory().createJSONBase(in);
}

void JSON::print() const
{
    json->output(std::cout, 1, false);
}

JSONArray JSON::search(const std::string &key) const
{
    JSONArray jsonArray;
    json->search(key, jsonArray.getValues());

    if (jsonArray.getValues().empty())
    {
        throw ElementNotFound(key);
    }

    return jsonArray;
}

void JSON::edit(std::vector<std::string> &elements, JSONBase *value)
{
    try
    {
        json->edit(elements, value, 0);
    }
    catch (...)
    {
        delete value;
        throw;
    }
}

void JSON::create(std::vector<std::string> &elements, JSONBase *value)
{
    try
    {
        json->create(elements, value, 0);
    }
    catch (...)
    {
        delete value;
        throw;
    }
}

void JSON::remove(std::vector<std::string> &elements)
{
    json->remove(elements, 0, true);
}

void JSON::move(std::vector<std::string> &from, std::vector<std::string> &to)
{
    JSONBase* element = const_cast<JSONBase*>(json->findElement(from, 0));

    if (element == nullptr)
    {
        throw ElementNotFound(from.back());
    }

    try
    {
        json->create(to, element, 0);
        json->remove(from, 0, false);
    }
    catch (const ElementAlreadyExists&)
    {
        json->edit(to, element, 0);
        json->remove(from, 0, false);
    }
}

void JSON::save(bool isCompact, const std::string &fileName) const
{
    std::ofstream file;

    if (fileName.empty())
    {
        file.open(this->fileName);
    }
    else
    {
        file.open(fileName);
    }

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    try
    {
        json->output(file, 1, isCompact);
        file.close();
    }
    catch (...)
    {
        file.close();
        throw;
    }
}

const JSONBase *const JSON::findElement(std::vector<std::string> &elements) const
{
    return json->findElement(elements, 0);
}
