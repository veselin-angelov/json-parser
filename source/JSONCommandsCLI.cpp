//
// Created by vesko on 20.06.22.
//

#include "../headers/JSONCommandsCLI.h"
#include "../headers/JSONValidator.h"
#include "../headers/JSONFactory.h"
#include "../headers/JSONParser.h"

JSONCommandsCLI::JSONCommandsCLI(JSON &json) : json(json)
{}

void JSONCommandsCLI::run()
{
    std::string command;

    while (true)
    {
        std::cin >> command;

        if (command == "end")
        {
            break;
        }
        else if (command == "print")
        {
            this->print();
            std::cout << std::endl;
        }
        else if (command == "search")
        {
            this->search(std::cin);
        }
        else if (command == "edit")
        {
            this->edit(std::cin);
        }
        else if (command == "create")
        {
            this->create(std::cin);
        }
        else if (command == "remove")
        {
            this->remove(std::cin);
        }
        else if (command == "move")
        {
            this->move(std::cin);
        }
//        TODO add save and search result manipulation
        else
        {
            std::cout << "Command not recognized!" << std::endl;
        }
    }
}

JSONBase *JSONCommandsCLI::createElement(std::istream &in)
{
    std::fstream commands;

    try
    {
        commands.open("command.txt", std::fstream::trunc | std::fstream::out | std::fstream::in);

        std::string command;
        getline(std::cin, command);
        commands << command;

        commands.flush();
        commands.seekg(0);

        JSONValidator::validate(commands);

        if (!commands.good()) commands.clear();

        commands.seekg(0);

        JSONBase* jsonBase = JSONFactory::getFactory().createJSONBase(commands);

        commands.close();

        return jsonBase;
    }
    catch (...)
    {
        commands.close();
        throw;
    }
}

void JSONCommandsCLI::print() const
{
    json.print();
}

void JSONCommandsCLI::search(std::istream &in)
{
    std::string key;
    in >> key;
    searchResults = json.search(key);
}

void JSONCommandsCLI::edit(std::istream &in)
{
    std::string elementPath;
    in >> elementPath;

    std::vector<std::string> elements = JSONParser::parseElementPathToElements(elementPath);
    if (elements.empty()) throw ElementNotFound("No element");

    json.edit(elements, createElement(in));
}

void JSONCommandsCLI::create(std::istream &in)
{
    std::string elementPath;
    in >> elementPath;

    std::vector<std::string> elements = JSONParser::parseElementPathToElements(elementPath);
    if (elements.empty()) throw ElementNotFound("No element");

    json.create(elements, createElement(in));
}

void JSONCommandsCLI::remove(std::istream &in)
{
    std::string elementPath;
    in >> elementPath;

    std::vector<std::string> elements = JSONParser::parseElementPathToElements(elementPath);
    if (elements.empty()) throw ElementNotFound("No element");

    json.remove(elements);
}

void JSONCommandsCLI::move(std::istream &in)
{
    std::string fromPath;
    in >> fromPath;

    std::string toPath;
    in >> toPath;

    std::vector<std::string> from = JSONParser::parseElementPathToElements(fromPath);
    std::vector<std::string> to = JSONParser::parseElementPathToElements(toPath);

    if (from.empty() || to.empty()) throw ElementNotFound("No element");

    json.move(from, to);
}
