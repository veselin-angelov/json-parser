#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include "headers/JSONValidator.h"
#include "headers/json-types/JSONNull.h"
#include "headers/json-types/JSONPair.h"
#include "headers/json-types/JSONString.h"
//#include "TypeUtilities.h"

int main()
{
//    std::string json = R"("username": "password")";
//
//    size_t colonPos = json.find(':');
//
//    std::string key = json.substr(0,colonPos);
//    std::string value = json.substr(colonPos + 1);
//
//    removeChar(key, ' ');
//    removeChar(value, ' ');
//
//    removeChar(key, '\"'); // wtf
//    removeChar(value, '\"');
//
//    std::cout << key << std::endl;
//    std::cout << value << std::endl;

//    std::cout << isdigit('1');
//    std::cout << isalpha('a');
//    std::cout << isalnum(1);

    try
    {
        std::ifstream jsonFile("test.json");

        JSONValidator::validate(jsonFile);

        JSONBase* jsonBase = new JSONString("test");
        JSONPair jsonPair("t", jsonBase);

        JSONString jsonString("test");
        JSONPair jsonPair1("asd", &jsonString);
//        jsonPair1 = jsonPair;

//        JSONPair jsonPair1 = jsonPair;
        delete jsonBase;

    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

//    int a;
//    std::cout << a << std::endl;

    return 0;
}
