//
// Created by vesko on 13.06.22.
//

#ifndef JSON_PARSER_JSONEXCEPTIONS_H
#define JSON_PARSER_JSONEXCEPTIONS_H

#include <exception>

class InvalidTypeException : public std::exception
{
private:
    std::string message;

public:
    explicit InvalidTypeException(const std::string &message, long long int pos = -1)
    {
        this->message = message;

        if (pos != -1)
        {
            this->message += " Error at position: ";
            this->message += std::to_string(pos);
        }
    }

    const char * what() const noexcept override
    {
        return message.c_str();
    }
};


class MultipleJSONRootElementsException : public std::exception
{
    const char * what() const noexcept override
    {
        return "Cannot have more than one root element! Check at the end of the file!";
    }
};

#endif //JSON_PARSER_JSONEXCEPTIONS_H
