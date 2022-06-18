#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include "headers/JSONValidator.h"
#include "headers/json-types/JSONNull.h"
#include "headers/json-types/JSONPair.h"
#include "headers/json-types/JSONString.h"
#include "headers/JSON.h"
//#include "TypeUtilities.h"

int main()
{
    try
    {
        JSON json("test.json");
        std::cout << "yes";
//        std::ifstream jsonFile("test.json");
//
//        JSONValidator::validate(jsonFile);
//
//        JSONBase* jsonBase = new JSONString("test");
//        JSONPair jsonPair("t", jsonBase);
//
//        JSONPair jsonPair1 = jsonPair;
//
//        jsonPair = jsonPair1;
//
//        JSONString jsonString("test");
//        JSONPair jsonPair1("asd", jsonString.clone());
//        delete jsonBase;

//        JSONPairCreator jsonPairCreator;
//        JSONPair jsonPair = jsonPairCreator.createJSONPair(jsonFile);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
