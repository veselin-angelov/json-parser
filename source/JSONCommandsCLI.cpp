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
        try
        {
            getline(std::cin, command);
            std::vector<std::string> commands = JSONParser::parseLineToStrings(command, " ");

            if (commands[0] == "end")
            {
                break;
            }
            else if (commands[0] == "print")
            {
                if (commands.size() == 1)
                {
                    this->print();
                }
                else if (commands.size() == 2)
                {
                    this->print(commands[1]);
                }
                else if (commands.size() == 3 && commands[2][0] != '-')
                {
                    this->print(commands[1], std::stoi(commands[2]));
                }
                else
                {
                    std::cout << "Command: print (search_result) (<index>)" << std::endl;
                }
            }
            else if (commands[0] == "search")
            {
                if (commands.size() >= 2) this->search(commands[1]);
                else std::cout << "Command: search <key>" << std::endl;
            }
            else if (commands[0] == "edit")
            {
                if (commands.size() > 3)
                {
                    for (int i = 3; i < commands.size(); ++i)
                    {
                        commands[2] += commands[i];
                    }
                }

                if (commands.size() >= 3) this->edit(commands[1], commands[2]);
                else std::cout << "Command: edit <element> <value>" << std::endl;
            }
            else if (commands[0] == "create")
            {
                if (commands.size() > 3)
                {
                    for (int i = 3; i < commands.size(); ++i)
                    {
                        commands[2] += commands[i];
                    }
                }

                if (commands.size() >= 3) this->create(commands[1], commands[2]);
                else std::cout << "Command: create <element> <value>" << std::endl;
            }
            else if (commands[0] == "remove")
            {
                if (commands.size() >= 2) this->remove(commands[1]);
                else std::cout << "Command: remove <element>" << std::endl;
            }
            else if (commands[0] == "move")
            {
                if (commands.size() >= 3) this->move(commands[1], commands[2]);
                else std::cout << "Command: move <from> <to>" << std::endl;
            }
            else if (commands[0] == "alignment")
            {
                if (commands.size() >= 2) this->alignment(commands[1]);
                else std::cout << "Command: alignment (tabbed/compact)" << std::endl;
            }
            else if (commands[0] == "save")
            {
                if (commands.size() == 1)
                {
                    this->save();
                }
                else if (commands.size() == 2)
                {
                    this->save(commands[1]);
                }
                else if (commands.size() == 3)
                {
                    this->save(commands[1], commands[2]);
                }
                else if (commands.size() == 4)
                {
                    try
                    {
                        int index = std::stoi(commands[3]);
                        if (commands[3][0] != '-') this->save(commands[1], commands[2], "", index);
                    }
                    catch (const std::invalid_argument&)
                    {
                        this->save(commands[1], commands[2], commands[3]);
                    }
                }
                else
                {
                    std::cout << "Command: save (<fileName>) (path/key/search_result) (<path>/<key>/(<index>))" << std::endl;
                }
            }
            else
            {
                std::cout << "Command not recognized!" << std::endl;
            }
        }
        catch (const std::invalid_argument &)
        {
            std::cout << "Expected number index!" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

JSONBase *JSONCommandsCLI::createElement(const std::string &value)
{
    std::fstream jsonValue;

    try
    {
        jsonValue.open("temp.json", std::fstream::trunc | std::fstream::out | std::fstream::in);

        jsonValue << value;

        jsonValue.flush();
        jsonValue.seekg(0);

        JSONValidator::validate(jsonValue);

        if (!jsonValue.good()) jsonValue.clear();

        jsonValue.seekg(0);

        JSONBase* jsonBase = JSONFactory::getFactory().createJSONBase(jsonValue);

        jsonValue.close();

        return jsonBase;
    }
    catch (...)
    {
        jsonValue.close();
        throw;
    }
}

void JSONCommandsCLI::print(const std::string &option, int index) const
{
    if (option.empty())
    {
        json.print();
    }
    else
    {
        if (searchResults.getValues().empty())
        {
            throw std::runtime_error("Search result is empty!");
        }

        if (index >= 0)
        {
            searchResults[index]->output(std::cout, 1, false);
        }
        else
        {
            searchResults.output(std::cout, 1, false);
        }
    }

    std::cout << std::endl;
}

void JSONCommandsCLI::search(const std::string &key)
{
    searchResults = json.search(key);
    std::cout << "Found" << std::endl;
}

void JSONCommandsCLI::edit(const std::string &elementPath, const std::string &value)
{
    std::vector<std::string> elements = JSONParser::parseLineToStrings(elementPath, ".[]");
    if (elements.empty()) throw ElementNotFound("No element");

    json.edit(elements, createElement(value));
    std::cout << "Edited" << std::endl;
}

void JSONCommandsCLI::create(const std::string &elementPath, const std::string &value)
{
    std::vector<std::string> elements = JSONParser::parseLineToStrings(elementPath, ".[]");
    if (elements.empty()) throw ElementNotFound("No element");

    json.create(elements, createElement(value));
    std::cout << "Created" << std::endl;
}

void JSONCommandsCLI::remove(const std::string &elementPath)
{
    std::vector<std::string> elements = JSONParser::parseLineToStrings(elementPath, ".[]");
    if (elements.empty()) throw ElementNotFound("No element");

    json.remove(elements);
    std::cout << "Removed" << std::endl;
}

void JSONCommandsCLI::move(const std::string &fromPath, const std::string &toPath)
{
    std::vector<std::string> from = JSONParser::parseLineToStrings(fromPath, ".[]");
    std::vector<std::string> to = JSONParser::parseLineToStrings(toPath, ".[]");

    if (from.empty() || to.empty()) throw ElementNotFound("No element");

    json.move(from, to);
    std::cout << "Moved" << std::endl;
}

void JSONCommandsCLI::alignment(const std::string &option)
{
    if (option == "tabbed")
    {
        isCompact = false;
    }
    else if (option == "compact")
    {
        isCompact = true;
    }
    else
    {
        throw std::runtime_error("Wrong option!");
    }
}

void JSONCommandsCLI::save(const std::string &fileName, const std::string &option, const std::string &optionValue, int index)
{
    if (option.empty() && optionValue.empty() && index == -1)
    {
        json.save(isCompact, fileName);  // save && save <fileName>
    }
    else if (!fileName.empty() && !option.empty() && option == "search_result" && optionValue.empty())
    {
        if (searchResults.getValues().empty())
        {
            throw std::runtime_error("Search result is empty!");
        }

        std::ofstream file(fileName);

        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        try
        {
            index >= 0 ? searchResults[index]->output(file, 1, isCompact) :
                         searchResults.output(file, 1, isCompact);
            file.close();
        }
        catch (...)
        {
            file.close();
            throw;
        }
    }
    else if (!fileName.empty() && !option.empty() && !optionValue.empty() && index == -1)
    {
        std::ofstream file(fileName);

        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        try
        {
            if (option == "path")
            {
                std::vector<std::string> elements = JSONParser::parseLineToStrings(optionValue, ".[]");
                json.findElement(elements)->output(file, 1, isCompact);
            }
            else if (option == "key")
            {
                json.search(optionValue).output(file, 1, isCompact);
            }

            file.close();
        }
        catch (...)
        {
            file.close();
            throw;
        }
    }
    else
    {
        throw std::runtime_error("Could not save! Check command correctness!");
    }

    std::cout << "Saved" << std::endl;
}

