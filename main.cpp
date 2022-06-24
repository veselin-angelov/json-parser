#include <iostream>
#include "headers/JSON.h"
#include "headers/JSONCommandsCLI.h"

int main()
{
    try
    {
        JSON json("test.json");

        json.test();

//        JSONCommandsCLI jsonCommands(json);
//        jsonCommands.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
